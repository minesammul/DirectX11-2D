#pragma once
#include <Script.h>

class CZ1MonsterExistFindScript : public CScript
{
private:
	CLayer* enemyLayer;

public:
	CZ1MonsterExistFindScript();
	~CZ1MonsterExistFindScript();

public:
	virtual void start();
	virtual void update();
};

