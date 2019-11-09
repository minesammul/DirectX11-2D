#pragma once
#include "MonsterScript.h"

class MonsterMoveStrategy
{
private:
	bool isMove;

public:
	MonsterMoveStrategy();
	virtual ~MonsterMoveStrategy();

public:
	virtual void Move(CMonsterScript* monster) = 0;

	bool GetIsMove(void) { return isMove; }
	void SetIsMove(bool isMove) { this->isMove = isMove; }
};

