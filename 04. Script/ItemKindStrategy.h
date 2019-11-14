#pragma once
#include "ItemKind.h"

class ItemKindStrategy
{
private:
	Vector3 originPosition;
	Vector3 mouseDirection;

public:
	ItemKindStrategy();
	virtual ~ItemKindStrategy();

public:
	virtual void Action(ItemKind* itemKind) = 0;
	virtual void Update(ItemKind* itemKind) = 0;
};

