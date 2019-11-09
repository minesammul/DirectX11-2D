#pragma once
#include "MonsterState.h"
class MonsterIdleState : public MonsterState
{
private:
	CAnimation2D* monsterAnimation;
	float stateTime;

public:
	MonsterIdleState();
	~MonsterIdleState();


public:
	// MonsterState을(를) 통해 상속됨
	virtual void Init(CMonsterScript * monster) override;

	// MonsterState을(를) 통해 상속됨
	virtual void Update(CMonsterScript * monster) override;

	static MonsterIdleState* GetInstance()
	{
		static MonsterIdleState* instance = new MonsterIdleState;
		return instance;
	}


};

