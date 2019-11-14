#pragma once
#include <Script.h>

class MonsterState;
class MonsterIdleState;
class MonsterAttackState;
class MonsterMoveState;

class MonsterComponent;
class MonsterMove;
class MonsterAttack;

enum class MONSTER_COMPONENT
{
	MOVE,
	ATTACK,
	END
};

class CMonsterScript :
	public CScript
{
private:
	MonsterState* monsterState;
	MonsterIdleState* monsterIdleState;
	MonsterAttackState* monsterAttackState;
	MonsterMoveState* monsterMoveState;

	MonsterComponent* monsterComponent[(UINT)MONSTER_COMPONENT::END];

	CResPtr<CMaterial> m_pCloneMtrl;

	Vector3 monsterDirection;

	int hp;
	CResPtr<CPrefab> dieEffectPrefab;
	bool isDie;

	CGameObject* attackBox;

	CGameObject* player;

public:
	CLONE(CMonsterScript);

public:
	CMonsterScript();
	virtual ~CMonsterScript();

private:
	void CheckDie();
	void AftertreatmentDie();
	void CheckAttackBoxDirection();

public:
	virtual void start();
	virtual void update();

	MonsterMove* GetMonsterMove(void);
	MonsterAttack* GetMonsterAttack(void);

	void SetMonsterState(MonsterState* state) { monsterState = state; }
	MonsterIdleState* GetMonsterIdleState(void) { return this->monsterIdleState; }
	MonsterAttackState* GetMonsterAttackState(void) { return this->monsterAttackState; }
	MonsterMoveState* GetMonsterMoveState(void) { return this->monsterMoveState; }

	void SetMonsterLeftRightImage(int OriginZeroInverseOne);
	void SetMonsterDirectionImage(void);

	Vector3 GetMonsterDirection(void) 
	{
		return monsterDirection;
	}

	void SetHp(int hp) { this->hp = hp; }
	int GetHp(void) { return this->hp; }
};

