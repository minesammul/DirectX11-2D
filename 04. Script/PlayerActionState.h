#pragma once
#include "PlayerScript.h"

class PlayerActionState
{
public:
	PlayerActionState();
	virtual ~PlayerActionState();

public:
	virtual void Update(CPlayerScript* player) = 0;

};

