#pragma once
#include "PlayerActionState.h"

class CPlatformRightCollisionScript;
class PlayerActionStateMove : public PlayerActionState
{
private:
	CPlatformRightCollisionScript* platformRightCollisionScript;
	float moveEffectOutputTime;

public:
	PlayerActionStateMove();
	~PlayerActionStateMove();

private:
	void FindAnimation(CPlayerScript * player);
	void ActionState(CPlayerScript * player);
	void TransactionState(CPlayerScript * player);
	void CreateMoveEffect(CPlayerScript* player);

public:
	virtual void Update(CPlayerScript * player) override;
	static PlayerActionStateMove* GetInstance()
	{
		static PlayerActionStateMove instance;
		instance.moveEffectOutputTime = 0.f;
		return &instance;
	}

};

