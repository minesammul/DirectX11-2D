#pragma once
#include "MonsterAttackStrategy.h"

class MonsterCircleWaveBullet : public MonsterAttackStrategy
{
private:
	CResPtr<CPrefab> bullet;

public:
	MonsterCircleWaveBullet();
	~MonsterCircleWaveBullet();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;

};

