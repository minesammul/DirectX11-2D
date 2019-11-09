#pragma once
#include "ItemScript.h"

class ItemComponent
{
public:
	ItemComponent();
	virtual ~ItemComponent();

public:
	virtual void Init(CItemScript* item) = 0;
	virtual void Action(CItemScript* item) = 0;
	virtual void Update(CItemScript* item) = 0;
};

