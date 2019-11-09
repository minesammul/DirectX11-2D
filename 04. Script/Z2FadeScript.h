#pragma once
#include <Script.h>

class CZ2FadeScript : public CScript
{
private:
	const float COLOR_MULIT_VALUE = 4.0f;

private:
	CResPtr<CMaterial> cloneMtrl;
	float alphaValue;
	bool isStart;

	CCamera* mainCamera;

public:
	CZ2FadeScript();
	~CZ2FadeScript();

public:
	virtual void start();
	virtual void update();

	void SetIsStart(bool start) 
	{ 
		alphaValue = 1.0f;
		isStart = start; 
	}
};

