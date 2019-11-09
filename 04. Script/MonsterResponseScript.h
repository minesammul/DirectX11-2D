#pragma once
#include <Script.h>

class CMonsterResponseScript : public CScript
{
private:
	map<wstring, CResPtr<CPrefab>> monsterPrefab;
	CResPtr<CPrefab>	monsterSpawnEffectPrefab;

	bool isSpawn;

public:
	CMonsterResponseScript();
	~CMonsterResponseScript();

private:
	void SpawnMonster(void);
	void WakeSealObject(void);

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

