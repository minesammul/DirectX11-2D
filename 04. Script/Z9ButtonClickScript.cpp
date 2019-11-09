#include "stdafx.h"
#include "Z9ButtonClickScript.h"

#include "SaveLoadMgr.h"

CZ9ButtonClickScript::CZ9ButtonClickScript() : 
	CScript((UINT)SCRIPT_TYPE::Z9BUTTONCLICKSCRIPT)
{
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
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
	{
		vector<CGameObject*> player;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", player);
		player[0]->Active(true);

		vector<CGameObject*> cameraFrame;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"CameraFrame", cameraFrame);
		cameraFrame[0]->Active(true);

		vector<CGameObject*> fadeInOutObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"FadeInOutObject", fadeInOutObject);
		fadeInOutObject[0]->Active(true);

		vector<CGameObject*> playerHpBar;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"PlayerHpBar", playerHpBar);
		playerHpBar[0]->Active(true);

		vector<CGameObject*> mouseTraceObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"MouseTraceObject", mouseTraceObject);
		mouseTraceObject[0]->Active(false);
	}
}

void CZ9ButtonClickScript::OnCollisionExit(CCollider2D * _pOther)
{
	Object()->Animator2D()->SetCurAnim(offAnimation);
}
