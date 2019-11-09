#pragma once
#include "MonsterComponent.h"

class MonsterAttackStrategy;
class MonsterCircleWaveBullet;
class MonsterOneShotBullet;
class MonsterSwing;
class MonsterThreeShotBullet;
class MonsterTrace;
class MonsterCircleShotBullet;
class MonsterJumpTackle;

class MonsterAttack : public MonsterComponent
{
private:
	MonsterAttackStrategy* attackStrategy;
	MonsterCircleWaveBullet* circleWaveBullet;
	MonsterOneShotBullet* oneShotBullet;
	MonsterSwing* swing;
	MonsterThreeShotBullet* threeShotBullet;
	MonsterTrace* trace;
	MonsterCircleShotBullet* circleShotBullet;
	MonsterJumpTackle* jumpTackle;

public:
	MonsterAttack();
	~MonsterAttack();

public:
	// MonsterComponent을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update(CMonsterScript * monster) override;

	MonsterAttackStrategy* GetAttackStrategy(void) { return attackStrategy; }
	void SetAttackStrategy(MonsterAttackStrategy* attackStrategy) { this->attackStrategy = attackStrategy; }

};

