#pragma once
#include "MonsterMoveStrategy.h"

class MonsterDash : public MonsterMoveStrategy
{
private:
	const float MOVE_DISTACNE = 500.f;
	const float DASH_POWER = 700.f;
	const float MIN_DASH_POWER = 300.f;
	const float DECREASE_DASH_POWER = 9.8f;
	float nowDashPower;
	float nowMoveDistance;
	bool dashStart;
	Vec3 monsterDashDirection;

public:
	MonsterDash();
	~MonsterDash();

public:
	// MonsterMoveStrategy을(를) 통해 상속됨
	virtual void Move(CMonsterScript * monster) override;

};

