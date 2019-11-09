#include "stdafx.h"
#include "Z1MonsterExistFindScript.h"


CZ1MonsterExistFindScript::CZ1MonsterExistFindScript() : 
	CScript((UINT)SCRIPT_TYPE::Z1MONSTEREXISTFINDSCRIPT)
{
}


CZ1MonsterExistFindScript::~CZ1MonsterExistFindScript()
{
}

void CZ1MonsterExistFindScript::start()
{
	enemyLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Enemy");
}

void CZ1MonsterExistFindScript::update()
{
	bool isExist = false;
	vector<CGameObject*> enemyObject = enemyLayer->GetParentObject();
	if (enemyObject.empty() == false)
	{
		for (int index = 0; index < enemyObject.size(); index++)
		{
			if (enemyObject[index]->IsActive() == true)
			{
				isExist = true;
				break;
			}
		}
	}

	if (isExist == false)
	{
		CAnimator2D* objectAnimator = Object()->Animator2D();
		if (objectAnimator != nullptr)
		{
			if (objectAnimator->GetCurAnim()->IsFinish() == true)
			{
				Object()->Active(false);
			}
		}
		else
		{
			Object()->Active(false);
		}
	}
	else
	{
		CAnimator2D* objectAnimator = Object()->Animator2D();
		if (objectAnimator != nullptr)
		{
			if (objectAnimator->GetCurAnim()->IsPlay()==false)
			{
				objectAnimator->GetCurAnim()->Play();
			}

			if (objectAnimator->GetCurAnim()->GetNowFrameCount() >= objectAnimator->GetCurAnim()->GetRepeatEndFrame())
			{
				objectAnimator->GetCurAnim()->SetFrm(objectAnimator->GetCurAnim()->GetRepeatStartFrame());
			}
		}
	}
}
