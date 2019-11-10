#pragma once
#include "PlayerActionState.h"

class PlayerActionStateIdle : public PlayerActionState
{
public:
	PlayerActionStateIdle();
	~PlayerActionStateIdle();

private:
	void FindAnimation(CPlayerScript * player);
	void TransactionState(CPlayerScript * player);

	void ChangeIdleToMove(CPlayerScript * player);
	void ChangeIdleToJump(CPlayerScript * player);
	void ChangeIdleToSit(CPlayerScript * player);
	void ChangeIdleToDash(CPlayerScript * player);

	void CreateJumpEffect(CPlayerScript* player);

public:
	virtual void Update(CPlayerScript * player) override;

	static PlayerActionStateIdle* GetInstance()
	{
		static PlayerActionStateIdle instance;
		return &instance;
	}
};

