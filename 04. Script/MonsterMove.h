#pragma once
#include "MonsterComponent.h"

class MonsterMoveStrategy;
class MonsterDash;
class MonsterWalk;
class MonsterFly;

class MonsterMove : public MonsterComponent
{
private:
	MonsterMoveStrategy* moveStrategy;
	MonsterDash* moveDash;
	MonsterWalk* moveWalk;
	MonsterFly* moveFly;

public:
	MonsterMove();
	~MonsterMove();

public:
	// MonsterComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(CMonsterScript * monster) override;

	MonsterMoveStrategy* GetMoveStrategy(void) { return moveStrategy; }
	void SetMoveStrategy(MonsterMoveStrategy* moveStrategy) { this->moveStrategy = moveStrategy; }


};

