#include "stdafx.h"
#include "MonsterAttack.h"

#include "MonsterAttackStrategy.h"
#include "MonsterCircleWaveBullet.h"
#include "MonsterOneShotBullet.h"
#include "MonsterSwing.h"
#include "MonsterThreeShotBullet.h"
#include "MonsterTrace.h"
#include "MonsterCircleShotBullet.h"
#include "MonsterJumpTackle.h"

MonsterAttack::MonsterAttack()
{
	circleWaveBullet = new MonsterCircleWaveBullet;
	oneShotBullet = new MonsterOneShotBullet;
	swing = new MonsterSwing;
	threeShotBullet = new MonsterThreeShotBullet;
	trace = new MonsterTrace;
	circleShotBullet = new MonsterCircleShotBullet;
	jumpTackle = new MonsterJumpTackle;

	attackStrategy = nullptr;
}


MonsterAttack::~MonsterAttack()
{
	if (circleWaveBullet != nullptr)
	{
		delete circleWaveBullet;
	}

	if (oneShotBullet != nullptr)
	{
		delete oneShotBullet;
	}

	if (swing != nullptr)
	{
		delete swing;
	}

	if (threeShotBullet != nullptr)
	{
		delete threeShotBullet;
	}

	if (trace != nullptr)
	{
		delete trace;
	}

	if (circleShotBullet != nullptr)
	{
		delete circleShotBullet;
	}

	if (jumpTackle != nullptr)
	{
		delete jumpTackle;
	}
}

void MonsterAttack::Init()
{
	if (GetMonster()->Object()->GetName().compare(L"Banshee") == 0)
	{
		attackStrategy = circleWaveBullet;
	}
	else if (GetMonster()->Object()->GetName().compare(L"Bat_Red") == 0)
	{
		attackStrategy = oneShotBullet;
	}
	else if (GetMonster()->Object()->GetName().compare(L"BigWhiteSkel") == 0 ||
		GetMonster()->Object()->GetName().compare(L"Minotaurs") == 0)
	{
		attackStrategy = swing;
	}
	else if (GetMonster()->Object()->GetName().compare(L"GiantBat") == 0)
	{
		attackStrategy = threeShotBullet;
	}
	else if (GetMonster()->Object()->GetName().compare(L"LittleGhost") == 0)
	{
		attackStrategy = trace;
	}
	else if (GetMonster()->Object()->GetName().compare(L"RedGiantBat") == 0)
	{
		attackStrategy = circleShotBullet;
	}
	else if (GetMonster()->Object()->GetName().compare(L"SkelDog") == 0)
	{
		attackStrategy = jumpTackle;
		attackStrategy->Init();
	}
}

void MonsterAttack::Update(CMonsterScript * monster)
{
	attackStrategy->Attack(monster);
}
