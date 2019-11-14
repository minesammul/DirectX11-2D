#include "stdafx.h"
#include "PlayerScript.h"
#include <Camera.h>

#include "PlayerActionState.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateMove.h"
#include "PlayerActionStateJump.h"
#include "PlayerActionStateDash.h"
#include "PlayerActionStateSit.h"

#include "PlatformRightCollisionScript.h"
#include "PlatformLeftCollisionScript.h"

#include "EventQueueScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	actionState = PlayerActionStateIdle::GetInstance();
	moveSpeed = 200.f;
	moveDirection = Vector3(1.f, 0.f, 0.f);

	playerData.maxHp = 100;
	playerData.nowHp = 100;

	isHited = false;
	isCameraFocusPositionFind = false;
	beforeCameraFocusObjectID = 0;
}

CPlayerScript::~CPlayerScript()
{
	if (actionState != nullptr)
	{
		actionState = nullptr;
		delete actionState;
	}

	//if (PlayerActionStateIdle::GetInstance() != nullptr)
	//{
	//	//actionState = PlayerActionStateIdle::GetInstance();
	//	//if (actionState != nullptr)
	//	//{
	//	//	delete actionState;
	//	//	actionState = nullptr;
	//	//}
	//}

	//if (PlayerActionStateJump::GetInstance() != nullptr)
	//{
	///*	actionState = PlayerActionStateJump::GetInstance();
	//	if (actionState != nullptr)
	//	{
	//		delete actionState;
	//		actionState = nullptr;
	//	}*/
	//}

	//if (PlayerActionStateMove::GetInstance() != nullptr)
	//{
	///*	actionState = PlayerActionStateMove::GetInstance();
	//	if (actionState != nullptr)
	//	{
	//		delete actionState;
	//		actionState = nullptr;
	//	}*/
	//}

	//if (PlayerActionStateDash::GetInstance() != nullptr)
	//{
	//	//actionState = PlayerActionStateDash::GetInstance();
	//	//if (actionState != nullptr)
	//	//{
	//	//	delete actionState;
	//	//	actionState = nullptr;
	//	//}
	//}

	//if (PlayerActionStateSit::GetInstance() != nullptr)
	//{
	//	//actionState = PlayerActionStateSit::GetInstance();
	//	//if (actionState != nullptr)
	//	//{
	//	//	delete actionState;
	//	//	actionState = nullptr;
	//	//}
	//}

}

void CPlayerScript::CalculationMoveDirection()
{
	moveDirection = Vector3(1.f, 0.f, 0.f);
}

void CPlayerScript::CalculationMouseDirection()
{
	Vector3 playerPosition = Object()->Transform()->GetLocalPos();

	POINT mousePosition = CKeyMgr::GetInst()->GetMousePos();

	Vector3 sceneMousePosition = CSceneMgr::GetInst()->CalculationSceneMousePosition(
		mousePosition,
		mainCamera
	);

	mouseDirection = sceneMousePosition - playerPosition;
	mouseDirection = XMVector3Normalize(mouseDirection);
}

void CPlayerScript::ChangeImageInverse()
{
	if (mouseDirection.x > 0)
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		int inversOff = 0;
		cloneMtrl->SetData(SHADER_PARAM::INT_0, &inversOff);
	}
	else
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		int inversON = 1;
		cloneMtrl->SetData(SHADER_PARAM::INT_0, &inversON);
	}
}

void CPlayerScript::CheckHited()
{
	if (isHited == true)
	{
		isHited = false;
		SendPlayerDataToEventQueue();
	}
}

void CPlayerScript::start()
{
	CLayer* findLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"CameraFocus");
	cameraFocusLayerIndex = findLayer->GetLayerIdx();


	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerHpBar", findObject);
	if (findObject.empty() == false)
	{
		playerHPBar = findObject[0];
	}


	vector<CCamera*> curSceneCameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	for (int cameraIndex = 0; cameraIndex < curSceneCameras.size(); cameraIndex++)
	{
		CCamera* curCamera = curSceneCameras[cameraIndex];
		if (curCamera->IsValiedLayer(Object()->GetLayerIdx()) == true)
		{
			mainCamera = curCamera;
			break;
		}
	}


	vector<CGameObject*> childObject = Object()->GetChild();
	for (int childIndex = 0; childIndex < childObject.size(); childIndex++)
	{
		vector<CScript*> childScripts = childObject[childIndex]->GetScripts();
		for (int scriptIndex = 0; scriptIndex < childScripts.size(); scriptIndex++)
		{
			if (childScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLATFORMRIGHTCOLLISIONSCRIPT)
			{
				platformRightCollisionScript = dynamic_cast<CPlatformRightCollisionScript*>(childScripts[scriptIndex]);
			}
			if (childScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLATFORMLEFTCOLLISIONSCRIPT)
			{
				platformLeftCollisionScript = dynamic_cast<CPlatformLeftCollisionScript*>(childScripts[scriptIndex]);
			}
		}
	}


	SendPlayerDataToEventQueue();


	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\PlayerDashAfterImage.pref", L"Prefab\\PlayerDashAfterImage.pref");
	dashAfterImage = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\PlayerDashAfterImage.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\PlayerMoveEffect.pref", L"Prefab\\PlayerMoveEffect.pref");
	moveEffect = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\PlayerMoveEffect.pref");

}

void CPlayerScript::update()
{
	actionState->Update(this);


	CalculationMoveDirection();
	CalculationMouseDirection();


	ChangeImageInverse();


	CheckHited();
}

void CPlayerScript::OnCollisionEnter(CCollider2D * _pOther)
{
	int collisionObjectLayerIndex = _pOther->Object()->GetLayerIdx();
	if (cameraFocusLayerIndex == collisionObjectLayerIndex)
	{
		if (beforeCameraFocusObjectID != _pOther->GetID())
		{
			beforeCameraFocusObjectID = _pOther->GetID();
			isCameraFocusPositionFind = true;
			cameraFocusPosition = _pOther->Object()->Transform()->GetLocalPos();
		}
	}
}

void CPlayerScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCameraFocusPositionFind = false;
}

void CPlayerScript::SendPlayerDataToEventQueue(void)
{
	EVENT_PACKET packet;
	packet.eventType = EVENTQUEUE_TYPE::PLAYER_DATA;
	packet.value.push_back(this->playerData.maxHp);
	packet.value.push_back(this->playerData.nowHp);
	packet.eventSendTargetID = playerHPBar->GetID();

	CEventQueueScript::GetInstance()->EnqueueEvent(packet);
}

void CPlayerScript::PlayerHited(void)
{
	playerData.nowHp -= 1;
	isHited = true;
}
