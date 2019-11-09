#pragma once
#include <Script.h>

class CEffectScript : public CScript
{
private:
	bool isDestory;
	Vec3 rotate;

public:
	CEffectScript();
	~CEffectScript();

public:
	virtual void start();
	virtual void update();

	void SetRotate(Vec3 rotate) 
	{
		this->rotate = rotate;
	}

};

