#pragma once
#include <Script.h>

class CZ9ButtonClickScript : public CScript
{
private:
	CAnimation2D* offAnimation;
	CAnimation2D* onAnimation;

	bool isLoadScene;

public:
	CZ9ButtonClickScript();
	~CZ9ButtonClickScript();

public:
	virtual void start();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);
};

