#pragma once
#include "MonsterScript.h"

class MonsterComponent
{
private:
	CMonsterScript* monster;

public:
	MonsterComponent();
	virtual ~MonsterComponent();

public:
	virtual void Init() = 0;
	virtual void Update(CMonsterScript* monster) = 0;

	void SetMonster(CMonsterScript* monster) { this->monster = monster; }
	CMonsterScript* GetMonster(void) { return monster; }
};

