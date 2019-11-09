#pragma once
#include <Script.h>

class CZ3CameraBottomCheckScript : public CScript
{
private:
	bool isCollision;

public:
	CZ3CameraBottomCheckScript();
	~CZ3CameraBottomCheckScript();

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	bool GetIsCollision(void)
	{
		return isCollision;
	}

	void SetIsCollision(bool collision)
	{
		isCollision = collision;
	}
};

