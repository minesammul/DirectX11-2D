#pragma once
#include "ItemKindStrategy.h"

enum class SWORD_STATE
{
	UP,
	DOWN,
	END
};

class ItemSwordKindStrategy : public ItemKindStrategy
{
private:
	SWORD_STATE swordState;

public:
	ItemSwordKindStrategy();
	~ItemSwordKindStrategy();

public:
	// ItemKindStrategy을(를) 통해 상속됨
	virtual void Action(ItemKind* itemKind) override;

	// ItemKindStrategy을(를) 통해 상속됨
	virtual void Update(ItemKind* itemKind) override;
};

