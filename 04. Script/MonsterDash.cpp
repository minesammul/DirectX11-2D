#include "stdafx.h"
#include "MonsterDash.h"


MonsterDash::MonsterDash()
{
	nowMoveDistance = 0.f;
	dashStart = false;
	nowDashPower = DASH_POWER;
}


MonsterDash::~MonsterDash()
{
}

void MonsterDash::Move(CMonsterScript * monster)
{
	if (GetIsMove() == true)
	{
		if (dashStart == false)
		{
			monster->SetMonsterDirectionImage();
			monsterDashDirection = monster->GetMonsterDirection();
			dashStart = true;
		}

		Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

		monsterPosition.x += monsterDashDirection.x*nowDashPower*DT;

		monster->Object()->Transform()->SetLocalPos(monsterPosition);

		float nowDashDistance = monsterDashDirection.x*nowDashPower*DT;

		if (nowDashDistance < 0)
		{
			nowMoveDistance += nowDashDistance * (-1);
		}
		else
		{
			nowMoveDistance += nowDashDistance;
		}


		if (nowDashPower > MIN_DASH_POWER)
		{
			nowDashPower -= DECREASE_DASH_POWER;
		}

		if (nowMoveDistance > MOVE_DISTACNE)
		{
			nowMoveDistance = 0.f;
			nowDashPower = DASH_POWER;
			dashStart = false;
			SetIsMove(false);
		}
	}
}
