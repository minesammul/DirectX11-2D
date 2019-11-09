#pragma once
#include "ItemComponent.h"
class ItemImage : public ItemComponent
{
public:
	ItemImage();
	~ItemImage();

public:
	// ItemComponent을(를) 통해 상속됨
	virtual void Action(CItemScript* item) override;

	// ItemComponent을(를) 통해 상속됨
	virtual void Init(CItemScript * item) override;

	// ItemComponent을(를) 통해 상속됨
	virtual void Update(CItemScript * item) override;
};

