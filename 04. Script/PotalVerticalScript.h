#pragma once
#include <Script.h>

class CZ4CameraFrameScript;
class CZ2FadeScript;

class CPotalVerticalScript : public CScript
{
private:
	CZ4CameraFrameScript* cameraFrameScript;
	CZ2FadeScript* fadeScript;

public:
	CPotalVerticalScript();
	~CPotalVerticalScript();

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

