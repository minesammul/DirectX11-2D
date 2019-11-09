#pragma once
#include "Script.h"


struct PlayerData
{
	int maxHp;
	int nowHp;
};

class PlayerActionState;
class CPlatformRightCollisionScript;
class CPlatformLeftCollisionScript;

class CPlayerScript :
	public CScript
{
private:
	PlayerActionState* actionState;
	float moveSpeed;
	Vec3 moveDirection;
	Vec3 mouseDirection;

	CResPtr<CMaterial> cloneMtrl;

	PlayerData playerData;
	bool isHited;

	bool isCameraFocusPositionFind;
	UINT beforeCameraFocusObjectID;
	Vec3 cameraFocusPosition;
	int cameraFocusLayerIndex;

	CGameObject* playerHPBar;
	CCamera* mainCamera;

	CPlatformRightCollisionScript* platformRightCollisionScript;
	CPlatformLeftCollisionScript* platformLeftCollisionScript;

	CResPtr<CPrefab> dashAfterImage;
	CResPtr<CPrefab> moveEffect;

public:
	CPlayerScript();
	virtual ~CPlayerScript();

private:
	CLONE(CPlayerScript);

private:
	void CalculationMoveDirection();
	void CalculationMouseDirection();
	void ChangeImageInverse();
	void CheckHited();

public:
	virtual void start();
	virtual void update();

	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);

	void SetActionState(PlayerActionState* state) { actionState = state; }
	PlayerActionState* GetActionState() { return actionState; }

	float GetMoveSpeed() { return moveSpeed; }

	Vec3 GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(Vec3 direction) { moveDirection = direction; }

	Vec3 GetMouseDirection() { return mouseDirection; }

	void SendPlayerDataToEventQueue(void);
	void PlayerHited(void);

	bool GetIsCameraFocusPositionFind(void) 
	{
		return isCameraFocusPositionFind;
	}
	void SetIsCameraFocusPositionFind(bool find)
	{
		isCameraFocusPositionFind = find;
	}

	Vec3 GetCameraFocusPosition(void)
	{
		return cameraFocusPosition;
	}

	CResPtr<CPrefab> GetDashAfterImagePrefab(void)
	{
		return dashAfterImage;
	}

	CResPtr<CPrefab> GetMoveEffectPrefab(void)
	{
		return moveEffect;
	}
};


