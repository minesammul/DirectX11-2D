#pragma once
#include <Script.h>

class CZ4CameraFrameScript;
class CZ2FadeScript;

class CPotalScript : public CScript
{
private:
	CZ4CameraFrameScript* cameraFrameScript;
	CZ2FadeScript* fadeScript;

public:
	CPotalScript();
	~CPotalScript();

public:
	virtual void start();
	virtual void OnCollisionEnter(CCollider2D* _pOther);
};

