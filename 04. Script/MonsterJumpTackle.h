#pragma once
#include "MonsterAttackStrategy.h"

class MonsterJumpTackle : public MonsterAttackStrategy
{
private:
	bool firstJumping;
	bool gravityApply;

public:
	MonsterJumpTackle();
	~MonsterJumpTackle();

public:
	// MonsterAttackStrategy을(를) 통해 상속됨
	virtual void Attack(CMonsterScript * monster) override;
	virtual void Init();

};

