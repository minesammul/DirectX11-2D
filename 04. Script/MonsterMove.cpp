#include "stdafx.h"
#include "MonsterMove.h"
#include "MonsterMoveStrategy.h"
#include "MonsterDash.h"
#include "MonsterWalk.h"
#include "MonsterFly.h"

MonsterMove::MonsterMove()
{
	moveDash = new MonsterDash;
	moveWalk = new MonsterWalk;
	moveFly = new MonsterFly;

	moveStrategy = nullptr;
}


MonsterMove::~MonsterMove()
{
	if (moveDash != nullptr)
	{
		delete moveDash;
	}

	if (moveWalk != nullptr)
	{
		delete moveWalk;
	}

	delete moveFly;
}


void MonsterMove::Init()
{
	if (GetMonster()->Object()->GetName().compare(L"BigWhiteSkel") == 0 ||
		GetMonster()->Object()->GetName().compare(L"SkelDog") == 0)
	{
		moveStrategy = moveWalk;
	}
	else if(GetMonster()->Object()->GetName().compare(L"Minotaurs") == 0)
	{
		moveStrategy = moveDash;
	}
	//else
	//{
	//	moveStrategy = moveDash;
	//}
}


void MonsterMove::Update(CMonsterScript * monster)
{
	moveStrategy->Move(monster);
}


