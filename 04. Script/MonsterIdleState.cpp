#include "stdafx.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterMoveState.h"

MonsterIdleState::MonsterIdleState()
{
}


MonsterIdleState::~MonsterIdleState()
{
}


void MonsterIdleState::Init(CMonsterScript * monster)
{
	map<wstring, CAnimation2D*> monsterAnimationList = monster->Object()->Animator2D()->GetAnimList();
	map<wstring, CAnimation2D*>::const_iterator curMonsterAnimation = monsterAnimationList.begin();
	
	monsterAnimation = nullptr;
	int animationKeyIndex = 0;
	while (curMonsterAnimation != monsterAnimationList.end())
	{
		const wchar_t* animationName = curMonsterAnimation->first.c_str();
		const wchar_t* subStr = L"Idle";
		const wchar_t* tokStr = wcsstr(animationName, subStr);

		if (tokStr != nullptr)
		{
			monsterAnimation = curMonsterAnimation->second;
			monster->Object()->Animator2D()->SetCurAnim(monsterAnimation);
			break;
		}

		curMonsterAnimation++;
	}

	stateTime = 0.0f;
}


void MonsterIdleState::Update(CMonsterScript * monster)
{
	stateTime += DT;

	if (monsterAnimation->IsPlay() == false)
	{
		monsterAnimation->Play();
	}

	if (stateTime > 2.f)
	{
		vector<CGameObject*> player;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", player);

		Vector3 playerPosition = player[0]->Transform()->GetLocalPos();

		Vector3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

		Vector3 distance = XMVector2Length(playerPosition - monsterPosition);

		if (200.f < distance.x && distance.x < 400.f)
		{
			monster->GetMonsterMoveState()->Init(monster);
			monster->SetMonsterState(monster->GetMonsterMoveState());
			stateTime = 0.f;
			return;
		}
		else if (distance.x <= 200.f)
		{
			monster->GetMonsterAttackState()->Init(monster);
			monster->SetMonsterState(monster->GetMonsterAttackState());
			stateTime = 0.f;
			return;
		}
	}

	
}

