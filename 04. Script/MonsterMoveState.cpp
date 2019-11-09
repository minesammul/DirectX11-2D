#include "stdafx.h"
#include "MonsterMoveState.h"
#include "MonsterAttackState.h"
#include "MonsterIdleState.h"

#include "MonsterMove.h"

#include "MonsterMoveStrategy.h"
#include "MonsterDash.h"


MonsterMoveState::MonsterMoveState()
{
}


MonsterMoveState::~MonsterMoveState()
{
}

void MonsterMoveState::Init(CMonsterScript * monster)
{
	map<wstring, CAnimation2D*> monsterAnimationList = monster->Object()->Animator2D()->GetAnimList();
	map<wstring, CAnimation2D*>::const_iterator curMonsterAnimation = monsterAnimationList.begin();

	monsterAnimation = nullptr;
	int animationKeyIndex = 0;
	while (curMonsterAnimation != monsterAnimationList.end())
	{
		const wchar_t* animationName = curMonsterAnimation->first.c_str();
		const wchar_t* subStr = L"Move";
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

		monster->GetMonsterMove()->Init();
		monster->GetMonsterMove()->GetMoveStrategy()->SetIsMove(true);
	}

}

void MonsterMoveState::Update(CMonsterScript * monster)
{
	if (monsterAnimation == nullptr)
	{
		monster->GetMonsterIdleState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterIdleState());
		return;
	}

	if (monsterAnimation->IsFinish() &&
		monster->GetMonsterMove()->GetMoveStrategy()->GetIsMove() == false)
	{
		monster->GetMonsterAttackState()->Init(monster);
		monster->SetMonsterState(monster->GetMonsterAttackState());
		return;
	}


	if (monsterAnimation->GetNowFrameCount() >= monsterAnimation->GetRepeatStartFrame())
	{
		monster->GetMonsterMove()->Update(monster);
	}


	if (monster->GetMonsterMove()->GetMoveStrategy()->GetIsMove() == true)
	{
		if (monsterAnimation->GetNowFrameCount() >= monsterAnimation->GetRepeatEndFrame())
		{
			monsterAnimation->SetFrm(monsterAnimation->GetRepeatStartFrame());
		}
	}

}
