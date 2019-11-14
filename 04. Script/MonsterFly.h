#pragma once
#include "MonsterMoveStrategy.h"

class MonsterFly : public MonsterMoveStrategy
{
private:
	const float FLY_SPEED = 200.f;
	const float MAX_FLY_DISTACNE = 200.f;
	Vector3 nowFlyDistance;

public:
	MonsterFly();
	~MonsterFly();

public:
	// MonsterMoveStrategy을(를) 통해 상속됨
	virtual void Move(CMonsterScript * monster) override;

};

