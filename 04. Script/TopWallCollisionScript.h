#pragma once
#include "Script.h"
class CTopWallCollisionScript : public CScript
{
private:
	bool collisionOn;

public:
	CTopWallCollisionScript();
	~CTopWallCollisionScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetCollision(bool collision) { collisionOn = collision; }
	bool GetCollision(void) { return collisionOn; }
};

