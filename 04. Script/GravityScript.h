#pragma once
#include <Script.h>

class CGravityScript : public CScript
{
private:
	const float GRAVITY_VALUE = 1.86f;

private:
	float nowGravityValue;

	bool activeGravity;

public:
	CGravityScript();
	~CGravityScript();

public:
	CLONE(CGravityScript);

public:
	virtual void update();
	
	void SetActiveGravity(bool gravity) { activeGravity = gravity; }
	bool GetActiveGravity() { return activeGravity; }

	float GetNowGravityValue() { return nowGravityValue; }
	void SetNowGravityValue(float value) { nowGravityValue = value; }
};

