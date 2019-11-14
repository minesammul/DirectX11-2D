#pragma once
#include <Script.h>

enum class ITEM_TYPE
{
	KIND,
	IMAGE,
	EFFECT,
	END
};

class ItemComponent;
class ItemKind;

class CItemScript : public CScript
{
private:
	ItemComponent* itemComponents[(UINT)ITEM_TYPE::END];
	CResPtr<CMaterial>  m_pCloneMtrl;

	bool activeAttack;
	float activeAttackTime;
	bool isHit;
	Vector3 hitPosition;

public:
	CItemScript();
	~CItemScript();

public:
	virtual void awake();
	virtual void start();
	virtual void update();
	virtual void OnCollision(CCollider2D* _pOther);

	void Play();

	CResPtr<CMaterial>& GetItemMtrl() { return m_pCloneMtrl; }

	ItemKind* GetItemKind(void);

	bool GetIsHit(void) { return isHit; }
	void SetIsHit(bool hit) { isHit = hit; }

	Vector3 GetHitPosition(void) { return hitPosition; }
};

