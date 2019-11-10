#pragma once
#include "PlayerActionState.h"

class PlayerActionStateSit : public PlayerActionState
{
public:
	PlayerActionStateSit();
	~PlayerActionStateSit();

public:
	// PlayerActionState을(를) 통해 상속됨
	virtual void Update(CPlayerScript * player) override;

	static PlayerActionStateSit* GetInstance()
	{
		static PlayerActionStateSit instance;
		return &instance;
	}

};

