#pragma once
#include "PlayerActionState.h"
class PlayerActionStateDash : public PlayerActionState
{
private:
	Vec3 dashDirection;
	Vec3 startPosition;
	const float DASH_DISTANCE = 150.f;
	const float DASH_POWER = 2000.f;

	float dashAfterImageOutputTime;

public:
	const float DASH_FIRST_POWER = 15.f;

public:
	PlayerActionStateDash();
	~PlayerActionStateDash();

private:
	void FindAnimation(CPlayerScript * player);
	void TransactionState(CPlayerScript * player);
	void ChangeDashToIdle(CPlayerScript * player);
	void CheckDashDistance(CPlayerScript * player);
	void CheckDashWithWallCollision(CPlayerScript * player);
	void CreateDashAfterImage(CPlayerScript* player);

public:
	virtual void Update(CPlayerScript * player) override;

	static PlayerActionStateDash* GetInstance()
	{
		static PlayerActionStateDash instance;
		instance.dashAfterImageOutputTime = 0.f;
		return &instance;
	}

	void SetDashDirection(Vec3 direction) { dashDirection = direction; }
	void SetStartPosition(Vec3 position) { startPosition = position; }
};

