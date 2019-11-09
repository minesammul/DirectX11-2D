#pragma once
#include <Script.h>

class CZ7CameraLeftCheckScript : public CScript
{
private:
	bool isCollision;

public:
	CZ7CameraLeftCheckScript();
	~CZ7CameraLeftCheckScript();

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

