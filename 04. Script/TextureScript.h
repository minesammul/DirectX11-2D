#pragma once
#include <Script.h>

class CTextureScript : public CScript
{
private:
	const float TEXTURE_U_VALUE = 0.01f;

private:
	CResPtr<CMaterial> cloneMtrl;

	float UValue;
	Vector3 beforeMainCameraPosition;
	CCamera* mainCamera;

public:
	CTextureScript();
	~CTextureScript();

public:
	virtual void start();
	virtual void update();

};

