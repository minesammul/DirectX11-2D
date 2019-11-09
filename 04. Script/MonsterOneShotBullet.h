#pragma once
#include "MonsterAttackStrategy.h"

class MonsterOneShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;

public:
	MonsterOneShotBullet();
	~MonsterOneShotBullet();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;

};

