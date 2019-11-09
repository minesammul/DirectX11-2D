#pragma once
#include <Script.h>

class CZ3CameraBottomCheckScript;
class CZ5CameraTopCheckScript;
class CZ6CameraRightCheckScript;
class CZ7CameraLeftCheckScript;
class CPlayerScript;

class CZ4CameraFrameScript : public CScript
{
private:
	CGameObject* target;

	CZ3CameraBottomCheckScript* cameraBottomScript;
	CZ5CameraTopCheckScript* cameraTopScript;
	CZ6CameraRightCheckScript* cameraRightScript;
	CZ7CameraLeftCheckScript* cameraLeftScript;

	CPlayerScript* playerScript;

	bool isPotalUse;

	const float MOVE_SPEED = 1200.f;
	const float MOVE_START_DISTANCE = 100.f;

public:
	CZ4CameraFrameScript();
	~CZ4CameraFrameScript();

public:
	virtual void start();
	virtual void update();

	void SetIsPotalUse(bool use)
	{
		isPotalUse = use;
	}

	bool GetIsPotalUse(void)
	{
		return isPotalUse;
	}
};

