#pragma once
#include "ItemKind.h"

class ItemKindStrategy
{
private:
	Vec3 originPosition;
	Vec3 mouseDirection;

public:
	ItemKindStrategy();
	virtual ~ItemKindStrategy();

public:
	virtual void Action(ItemKind* itemKind) = 0;
	virtual void Update(ItemKind* itemKind) = 0;
};

