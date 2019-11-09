#pragma once
#include <Script.h>

class CBottomWallCollisionScript;

class CLeftWallCollisionScript : public CScript
{
private:
	bool collisionOn;
	CBottomWallCollisionScript* bottomWallCollisionScript;

public:
	CLeftWallCollisionScript();
	~CLeftWallCollisionScript();

public:
	virtual void start();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
	bool GetCollision(void) { return collisionOn; }
};

