#pragma once
#include <Script.h>

class CRightBottomWallCollisionScript;
class CLeftBottomWallCollisionScript;
class CGravityScript;

class CBottomWallCollisionScript : public CScript
{
private:
	Vec3 collisionPosition;
	bool collisionOn;

	CRightBottomWallCollisionScript* rightBottomWallCollisionScript;
	CLeftBottomWallCollisionScript* leftBottomWallCollisionScript;
	CGravityScript* gravityScript;

public:
	CBottomWallCollisionScript();
	~CBottomWallCollisionScript();
	CLONE(CBottomWallCollisionScript);

public:
	virtual void start();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
	bool GetCollision(void) { return collisionOn; }

	Vec3 GetCollisionPosition(void) { return collisionPosition; }
};

