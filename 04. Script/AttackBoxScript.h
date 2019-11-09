#pragma once
#include <Script.h>

class CAttackBoxScript : public CScript
{
private:
	bool isAttack;
	
public:
	CAttackBoxScript();
	~CAttackBoxScript();

public:
	virtual void OnCollision(CCollider2D* _pOther);

	void SetIsAttack(bool attack) { isAttack = attack; }
	bool GetIsAttack(void) { return isAttack; }
};

