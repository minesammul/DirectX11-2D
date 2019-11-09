#pragma once
#include "ItemComponent.h"

class ItemKindStrategy;
class ItemKind : public ItemComponent
{
private:
	ItemKindStrategy* itemKindStrategy;
	Vec3 itemDirection;
	Vec3 mouseDirection;
	Vec3 itemAxisRotate;
	Vec3 itemRotate;
	Vec3 itemPosition;

public:
	ItemKind();
	~ItemKind();

public:
	// ItemComponent을(를) 통해 상속됨
	virtual void Action(CItemScript* item) override;

	// ItemComponent을(를) 통해 상속됨
	virtual void Init(CItemScript * item) override;

	// ItemComponent을(를) 통해 상속됨
	virtual void Update(CItemScript * item) override;

	void SetKindStrategy(ItemKindStrategy* itemKindStrategy) { this->itemKindStrategy = itemKindStrategy; }
	
	Vec3 GetItemDirection(void) { return itemDirection; }
	void SetItemDirection(Vec3 direction) { itemDirection = direction; }

	Vec3 GetMouseDirection(void) { return mouseDirection; }
	void SetMouseDirection(Vec3 direction) { mouseDirection = direction; }

	Vec3 GetItemAxisRotate(void) { return itemAxisRotate; }
	void SetItemAxisRotate(Vec3 rotate) { itemAxisRotate = rotate; }

	Vec3 GetItemRotate(void) { return itemRotate; }
	void SetItemRotate(Vec3 rotate) { itemRotate = rotate; }

	Vec3 GetItemPosition(void) { return itemPosition; }
	void SetItemPosition(Vec3 position) { itemPosition = position; }
};

