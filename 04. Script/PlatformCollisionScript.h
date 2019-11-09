#pragma once
#include <Script.h>

class CPlayerScript;
class CGravityScript;

class CPlatformCollisionScript : public CScript
{
private:
	CPlayerScript* playerScript;
	CGravityScript* gravityScript;

public:
	CPlatformCollisionScript();
	~CPlatformCollisionScript();

public:
	CLONE(CPlatformCollisionScript);

public:
	virtual void start();
	virtual void update();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);
};

