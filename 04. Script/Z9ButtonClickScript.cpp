#include "stdafx.h"
#include "Z9ButtonClickScript.h"

#include <Core.h>
#include <EventMgr.h>

#include "SaveLoadMgr.h"

CZ9ButtonClickScript::CZ9ButtonClickScript() : 
	CScript((UINT)SCRIPT_TYPE::Z9BUTTONCLICKSCRIPT)
{
	isLoadScene = false;
}


CZ9ButtonClickScript::~CZ9ButtonClickScript()
{
}

void CZ9ButtonClickScript::start()
{
	offAnimation = Object()->Animator2D()->GetAnimList().find(L"Off")->second;
	onAnimation = Object()->Animator2D()->GetAnimList().find(L"On")->second;
}

void CZ9ButtonClickScript::OnCollisionEnter(CCollider2D * _pOther)
{
	Object()->Animator2D()->SetCurAnim(onAnimation);
}

void CZ9ButtonClickScript::OnCollision(CCollider2D * _pOther)
{
	if (isLoadScene == false)
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
		{
			isLoadScene = true;
			//CCore::GetInst()->SetState(SCENE_STATE::LOAD);
			//CSaveLoadMgr::LoadScene(L"D:\\GitHub Project\\DirectX11 2D Portfolio\\Project\\bin\\content\\Scene\\FinalStage2.scene");

			CCore::GetInst()->SetState(SCENE_STATE::LOAD);
			tEvent packet;
			packet.eType = EVENT_TYPE::CHANGE_SCENE;
			
			CScene* nextScene = CSaveLoadMgr::GetScene(L"D:\\GitHub Project\\DirectX11 2D Portfolio\\Project\\bin\\content\\Scene\\FinalStage8.scene");
			packet.lParam = (DWORD_PTR)nextScene;

			vector<bool> layerCollisions = CSaveLoadMgr::GetLayerCollisions();
			packet.boolVector = layerCollisions;

			CEventMgr::GetInst()->AddEvent(packet);

			//vector<CGameObject*> player;
			//CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", player);
			//player[0]->Active(true);

			//vector<CGameObject*> cameraFrame;
			//CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"CameraFrame", cameraFrame);
			//cameraFrame[0]->Active(true);

			//vector<CGameObject*> fadeInOutObject;
			//CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"FadeInOutObject", fadeInOutObject);
			//fadeInOutObject[0]->Active(true);

			//vector<CGameObject*> playerHpBar;
			//CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerHpBar", playerHpBar);
			//playerHpBar[0]->Active(true);

			//vector<CGameObject*> mouseTraceObject;
			//CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MouseTraceObject", mouseTraceObject);
			//mouseTraceObject[0]->Active(false);
		}
	}
}

void CZ9ButtonClickScript::OnCollisionExit(CCollider2D * _pOther)
{
	Object()->Animator2D()->SetCurAnim(offAnimation);
}
