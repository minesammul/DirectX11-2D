#pragma once
#include "MonsterMoveStrategy.h"

class MonsterWalk : public MonsterMoveStrategy
{
private:
	const float WALK_SPEED = 100.f;
	const float WALK_DISTANCE = 200.f;
	float nowWalkDistance;

public:
	MonsterWalk();
	~MonsterWalk();

public:
	// MonsterMoveStrategy을(를) 통해 상속됨
	virtual void Move(CMonsterScript * monster) override;

};

