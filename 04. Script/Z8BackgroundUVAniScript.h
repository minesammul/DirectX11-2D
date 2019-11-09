#pragma once
#include <Script.h>

class CZ8BackgroundUVAniScript : public CScript
{
private:
	CResPtr<CMaterial> cloneMtrl;
	float textureUValue;

public:
	CZ8BackgroundUVAniScript();
	~CZ8BackgroundUVAniScript();

public:
	virtual void start();
	virtual void update();
};

