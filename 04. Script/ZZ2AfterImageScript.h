#pragma once

#include <Script.h>

class CZZ2AfterImageScript : public CScript
{
private:
	CResPtr<CMaterial> cloneMtrl;
	CResPtr<CTexture> texture;

	float alphaValue;
	bool isDestory;
	int inverse;

public:
	CZZ2AfterImageScript();
	~CZZ2AfterImageScript();

public:
	virtual void start(void);
	virtual void update(void);

	void SetInverse(int zeroRightoneLeft)
	{
		inverse = zeroRightoneLeft;
	}
};

