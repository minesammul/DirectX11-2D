#pragma once
#include "MonsterScript.h"
class MonsterState
{
public:
	MonsterState();
	virtual ~MonsterState();

public:
	virtual void Init(CMonsterScript* monster) = 0;
	virtual void Update(CMonsterScript* monster) = 0;
};

