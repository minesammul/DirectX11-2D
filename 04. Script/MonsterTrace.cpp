#include "stdafx.h"
#include "MonsterTrace.h"


MonsterTrace::MonsterTrace()
{
	nowTraceDistance = 0.f;
}


MonsterTrace::~MonsterTrace()
{
}

void MonsterTrace::Attack(CMonsterScript * monster)
{
	if (GetIsAttack() == true)
	{
		monster->SetMonsterDirectionImage();

		if (monster->Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
		{
			monster->Object()->Animator2D()->GetCurAnim()->Play();
		}

		Vec3 monsterTraceDirection = monster->GetMonsterDirection();
		Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

		monsterPosition.x += monsterTraceDirection.x * TRACE_SPEED * DT;
		monsterPosition.y += monsterTraceDirection.y * TRACE_SPEED * DT;

		monster->Object()->Transform()->SetLocalPos(monsterPosition);


		Vec3 nowMoveDistance = Vec3(
			monsterTraceDirection.x*TRACE_SPEED*DT,
			monsterTraceDirection.y*TRACE_SPEED*DT,
			0.f
		);

		nowMoveDistance = XMVector2Length(nowMoveDistance);
		nowTraceDistance += nowMoveDistance.x;

		if (nowTraceDistance > MAX_TRACE_DISTANCE)
		{
			nowTraceDistance = 0.f;
			SetIsAttack(false);
		}
	}
}
