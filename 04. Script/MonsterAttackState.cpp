#include "stdafx.h"
#include "MonsterAttackState.h"

#include "MonsterIdleState.h"

#include "MonsterAttack.h"

#include "MonsterAttackStrategy.h"
#include "MonsterCircleWaveBullet.h"

#include "AttackBoxScript.h"

MonsterAttackState::MonsterAttackState()
{
}


MonsterAttackState::~MonsterAttackState()
{
}

void MonsterAttackState::Init(CMonsterScript * monster)
{
	map<wstring, CAnimation2D*> monsterAnimationList = monster->Object()->Animator2D()->GetAnimList();
	map<wstring, CAnimation2D*>::const_iterator curMonsterAnimation = monsterAnimationList.begin();

	monsterAnimation = nullptr;
	int animationKeyIndex = 0;
	while (curMonsterAnimation != monsterAnimationList.end())
	{
		const wchar_t* animationName = curMonsterAnimation->first.c_str();
		const wchar_t* subStr = L"Attack";
		const wchar_t* tokStr = wcsstr(animationName, subStr);

		if (tokStr != nullptr)
		{
			monsterAnimation = curMonsterAnimation->second;
			monster->Object()->Animator2D()->SetCurAnim(monsterAnimation);
			break;
		}

		curMonsterAnimation++;
	}

	if (monsterAnimation != nullptr)
	{
		if (monsterAnimation->IsPlay() == false)
		{
			monsterAnimation->Play();
		}

		monster->GetMonsterAttack()->Init();
		monster->GetMonsterAttack()->GetAttackStrategy()->SetIsAttack(true);
	}

	vector<CScript*> childScript;
	vector<CGameObject*> childObject = monster->Object()->GetChild();
	if (childObject.empty() == false)
	{
		for (int index = 0; index < childObject.size(); index++)
		{
			wstring attackBoxName = monster->Object()->GetName();
			attackBoxName += L"AttackBox";
			if (childObject[index]->GetName().compare(attackBoxName) == 0)
			{
				childScript = childObject[index]->GetScripts();
				break;
			}
		}
	}

	if (childScript.empty() == false)
	{
		for (int index = 0; index < childObject.size(); index++)
		{
			if (childScript[index]->GetScriptType() == (UINT)SCRIPT_TYPE::ATTACKBOXSCRIPT)
			{
				CAttackBoxScript* attackboxScript = dynamic_cast<CAttackBoxScript*>(childScript[index]);
				attackboxScript->SetIsAttack(true);
				break;
			}
		}
	}
}

void MonsterAttackState::Update(CMonsterScript * monster)
{
	if (monsterAnimation == nullptr)
	{
		monster->GetMonsterIdleState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterIdleState());
		return;
	}

	if (monster->GetMonsterAttack()->GetAttackStrategy()->GetIsAttack() == true)
	{
		monster->GetMonsterAttack()->Update(monster);
	}
	
	if(monster->GetMonsterAttack()->GetAttackStrategy()->GetIsAttack() == false &&
		monsterAnimation->IsFinish() == true)
	{
		monster->GetMonsterIdleState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterIdleState());
		return;
	}
}
