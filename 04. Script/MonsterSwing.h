#pragma once
#include "MonsterAttackStrategy.h"
class MonsterSwing : public MonsterAttackStrategy
{
public:
	MonsterSwing();
	~MonsterSwing();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;

};

