#pragma once
#include <Script.h>

class CCameraScript : public CScript
{
private:
	CGameObject* target;

public:
	CCameraScript();
	~CCameraScript();

public:
	virtual void start();
	virtual void update();
};

