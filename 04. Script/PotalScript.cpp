#include "stdafx.h"
#include "PotalScript.h"

#include "Z2FadeScript.h"
#include "Z4CameraFrameScript.h"

CPotalScript::CPotalScript() :
	CScript((UINT)SCRIPT_TYPE::POTALSCRIPT)
{
}


CPotalScript::~CPotalScript()
{
}

void CPotalScript::start()
{
	vector<CGameObject*> findObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"CameraFrame", findObject);
	if (findObject.empty() == false)
	{
		vector<CScript*> findObjectScript = findObject[0]->GetScripts();
		if (findObjectScript.empty() == false)
		{
			for (int index = 0; index < findObjectScript.size(); index++)
			{
				if (findObjectScript[index]->GetScriptType() == (UINT)SCRIPT_TYPE::Z4CAMERAFRAMESCRIPT)
				{
					cameraFrameScript = dynamic_cast<CZ4CameraFrameScript*>(findObjectScript[index]);
				}
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		assert(false);
	}


	vector<CGameObject*> fadeInOutObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"FadeInOutObject", fadeInOutObject);
	if (fadeInOutObject.empty() == false)
	{
		vector<CScript*> fadeInOutScript = fadeInOutObject[0]->GetScripts();
		if (fadeInOutScript.empty() == false)
		{
			if (fadeInOutScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z2FADESCRIPT)
			{
				fadeScript = dynamic_cast<CZ2FadeScript*>(fadeInOutScript[0]);
			}
		}
	}
}

void CPotalScript::OnCollisionEnter(CCollider2D * _pOther)
{
	wstring objectName = _pOther->Object()->GetName();

	if (objectName.compare(L"Player") == 0)
	{
		Vec3 playerPosition = _pOther->GetFinalPositon();
		Vec3 potalPosition = Object()->Transform()->GetLocalPos();
		if (playerPosition.x < potalPosition.x)
		{
			//Left to Right
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.x += Object()->Transform()->GetLocalScale().x / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.x += _pOther->GetFinalScale().x;

			_pOther->Object()->Transform()->SetLocalPos(playerPotalPosition);
		}
		else
		{
			//Right to Left
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.x -= Object()->Transform()->GetLocalScale().x / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.x -= _pOther->GetFinalScale().x;

			_pOther->Object()->Transform()->SetLocalPos(playerPotalPosition);
		}

		fadeScript->SetIsStart(true);

		cameraFrameScript->SetIsPotalUse(true);
	}
}