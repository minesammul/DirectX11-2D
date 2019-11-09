#include "stdafx.h"
#include "ObjectEditScript.h"
#include <Camera.h>


CObjectEditScript::CObjectEditScript() : 
	CScript((UINT)SCRIPT_TYPE::OBJECTEDITSCRIPT)
{
}


CObjectEditScript::~CObjectEditScript()
{
}

void CObjectEditScript::update()
{
	CGameObject* editObject = CSceneMgr::GetInst()->GetMousePickingObject();
	if (editObject == nullptr)
	{
		return;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_HOLD)
	{
		CGameObject* clickObject = CSceneMgr::GetInst()->GetMousePickingObject();

		if (editObject->GetID() == clickObject->GetID())
		{
			Vec3 editObjectPosition = editObject->Transform()->GetLocalPos();

			POINT mousePosition = CKeyMgr::GetInst()->GetMousePos();

			vector<CCamera*> curSceneCameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
			CCamera* camera = nullptr;
			for (int cameraIndex = 0; cameraIndex < curSceneCameras.size(); cameraIndex++)
			{
				CCamera* curCamera = curSceneCameras[cameraIndex];
				if (curCamera->IsValiedLayer(Object()->GetLayerIdx()) == true)
				{
					camera = curCamera;
					break;
				}
			}

			Vec3 sceneMousePosition = CSceneMgr::GetInst()->CalculationSceneMousePosition(
				mousePosition,
				camera
			);

			editObjectPosition.x = sceneMousePosition.x;
			editObjectPosition.y = sceneMousePosition.y;
			
			editObject->Transform()->SetLocalPos(editObjectPosition);
		}
	}

	//Move
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectPosition = editObject->Transform()->GetLocalPos();
		editObjectPosition.x -= 0.1f;
		editObject->Transform()->SetLocalPos(editObjectPosition);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectPosition = editObject->Transform()->GetLocalPos();
		editObjectPosition.x += 0.1f;
		editObject->Transform()->SetLocalPos(editObjectPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectPosition = editObject->Transform()->GetLocalPos();
		editObjectPosition.y += 0.1f;
		editObject->Transform()->SetLocalPos(editObjectPosition);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectPosition = editObject->Transform()->GetLocalPos();
		editObjectPosition.y -= 0.1f;
		editObject->Transform()->SetLocalPos(editObjectPosition);
	}

	//Scale
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectScale = editObject->Transform()->GetLocalScale();
		editObjectScale.x += 1.f;
		editObject->Transform()->SetLocalScale(editObjectScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_X) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectScale = editObject->Transform()->GetLocalScale();
		editObjectScale.x -= 1.f;
		editObject->Transform()->SetLocalScale(editObjectScale);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_C) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectScale = editObject->Transform()->GetLocalScale();
		editObjectScale.y += 1.f;
		editObject->Transform()->SetLocalScale(editObjectScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_V) == KEY_STATE::STATE_HOLD)
	{
		Vec3 editObjectScale = editObject->Transform()->GetLocalScale();
		editObjectScale.y -= 1.f;
		editObject->Transform()->SetLocalScale(editObjectScale);
	}
}
