#pragma once
#include "MonsterState.h"

class MonsterMoveState : public MonsterState
{
private:
	CAnimation2D* monsterAnimation;

public:
	MonsterMoveState();
	~MonsterMoveState();

public:
	// MonsterState을(를) 통해 상속됨
	virtual void Init(CMonsterScript * monster) override;
	virtual void Update(CMonsterScript * monster) override;

	static MonsterMoveState* GetInstance()
	{
		static MonsterMoveState* instance = new MonsterMoveState;
		return instance;
	}
};

