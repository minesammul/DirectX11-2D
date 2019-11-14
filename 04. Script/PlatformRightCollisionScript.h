#pragma once
#include <Script.h>

class CPlatformRightCollisionScript : public CScript
{
private:
	bool collisionOn;

	const int USE_POINT_INDEX_0 = 1;
	const int USE_POINT_INDEX_1 = 3;

	Vector3 collisionMoveDirection;

public:
	CPlatformRightCollisionScript();
	~CPlatformRightCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
	bool GetCollision(void) { return collisionOn; }

	Vector3 GetCollisionMoveDirection(void) { return collisionMoveDirection; }
};

