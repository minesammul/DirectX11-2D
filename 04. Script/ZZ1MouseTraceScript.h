#pragma once
#include <Script.h>

class CZZ1MouseTraceScript : public CScript
{
private:
	CCamera* mainCamera;

public:
	CZZ1MouseTraceScript();
	~CZZ1MouseTraceScript();

public:
	virtual void start();
	virtual void update();
};

