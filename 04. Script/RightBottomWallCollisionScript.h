#pragma once
#include <Script.h>

class CBottomWallCollisionScript;
class CGravityScript;

class CRightBottomWallCollisionScript : public CScript
{
private:
	bool collisionOn;

	const int USE_POINT_INDEX_0 = 1;
	const int USE_POINT_INDEX_1 = 3;

	CBottomWallCollisionScript* bottomWallCollisionScript;
	CGravityScript* gravityScript;

public:
	CRightBottomWallCollisionScript();
	~CRightBottomWallCollisionScript();

public:
	virtual void start();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
	bool GetCollision(void) { return collisionOn; }
};

