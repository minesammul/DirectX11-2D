#include "stdafx.h"
#include "MonsterWalk.h"


MonsterWalk::MonsterWalk()
{
	nowWalkDistance = 0;
}


MonsterWalk::~MonsterWalk()
{
}

void MonsterWalk::Move(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();

	Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

	Vec3 monsterDirection = monster->GetMonsterDirection();

	monsterPosition.x += monsterDirection.x*WALK_SPEED*DT;

	monster->Object()->Transform()->SetLocalPos(monsterPosition);

	float moveDistance = monsterDirection.x*WALK_SPEED*DT;
	if (moveDistance < 0)
	{
		moveDistance *= -1;
	}

	nowWalkDistance += moveDistance;
	if (nowWalkDistance > WALK_DISTANCE)
	{
		nowWalkDistance = 0.f;
		SetIsMove(false);
	}
}
