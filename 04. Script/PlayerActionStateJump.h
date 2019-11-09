#pragma once
#include "PlayerActionState.h"
class CGravityScript;
class PlayerActionStateJump : public PlayerActionState
{
private:
	const float MAX_JUMP_POWER = 700.f;
	const float ADD_JUMP_POWER = 1.005f;

private:
	float nowJumpPower;

	bool isFall;

	CGravityScript* gravityScript;

public:
	const float JUMP_POWER = 500.f;

public:
	PlayerActionStateJump();
	~PlayerActionStateJump();

private:
	void FindAnimation(CPlayerScript * player);
	
	void ActionState(CPlayerScript * player);
	void ActionJump(CPlayerScript * player);
	void ActionMove(CPlayerScript * player);

	void TransactionState(CPlayerScript * player);
	void ChangeJumpToIdle(CPlayerScript * player);
	void ChangeJumpToDash(CPlayerScript * player);
	
	void CheckFall(CPlayerScript * player);
	
public:
	virtual void Update(CPlayerScript * player) override;

	static PlayerActionStateJump* GetInstance()
	{
		static PlayerActionStateJump* instance = new PlayerActionStateJump;
		return instance;
	}

	void SetJumpPower(float jumpPower) { nowJumpPower = jumpPower; }
	
	bool GetIsFall() { return isFall; }
};

