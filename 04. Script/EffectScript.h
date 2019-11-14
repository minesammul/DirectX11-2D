#pragma once
#include <Script.h>

class CEffectScript : public CScript
{
private:
	bool isDestory;
	Vector3 rotate;

public:
	CEffectScript();
	~CEffectScript();

public:
	virtual void start();
	virtual void update();

	void SetRotate(Vector3 rotate) 
	{
		this->rotate = rotate;
	}

};

