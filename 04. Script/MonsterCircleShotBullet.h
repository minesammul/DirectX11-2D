#pragma once
#include "MonsterAttackStrategy.h"

class MonsterCircleShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;
	const float CREATE_INTERVAL = 100.f;

public:
	MonsterCircleShotBullet();
	~MonsterCircleShotBullet();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;

};

