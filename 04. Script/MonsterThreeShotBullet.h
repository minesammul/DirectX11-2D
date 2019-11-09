#pragma once
#include "MonsterAttackStrategy.h"

class MonsterThreeShotBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;


public:
	MonsterThreeShotBullet();
	~MonsterThreeShotBullet();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;

};

