#pragma once
#include "ItemComponent.h"

class ItemKindStrategy;
class ItemKind : public ItemComponent
{
private:
	ItemKindStrategy* itemKindStrategy;
	Vector3 itemDirection;
	Vector3 mouseDirection;
	Vector3 itemAxisRotate;
	Vector3 itemRotate;
	Vector3 itemPosition;

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
	
	Vector3 GetItemDirection(void) { return itemDirection; }
	void SetItemDirection(Vector3 direction) { itemDirection = direction; }

	Vector3 GetMouseDirection(void) { return mouseDirection; }
	void SetMouseDirection(Vector3 direction) { mouseDirection = direction; }

	Vector3 GetItemAxisRotate(void) { return itemAxisRotate; }
	void SetItemAxisRotate(Vector3 rotate) { itemAxisRotate = rotate; }

	Vector3 GetItemRotate(void) { return itemRotate; }
	void SetItemRotate(Vector3 rotate) { itemRotate = rotate; }

	Vector3 GetItemPosition(void) { return itemPosition; }
	void SetItemPosition(Vector3 position) { itemPosition = position; }
};

