#include "stdafx.h"
#include "Z4CameraFrameScript.h"

#include "Z3CameraBottomCheckScript.h"
#include "Z5CameraTopCheckScript.h"
#include "Z6CameraRightCheckScript.h"
#include "Z7CameraLeftCheckScript.h"

#include "PlayerScript.h"

CZ4CameraFrameScript::CZ4CameraFrameScript() : 
	CScript((UINT)SCRIPT_TYPE::Z4CAMERAFRAMESCRIPT)
{
	isPotalUse = false;
}


CZ4CameraFrameScript::~CZ4CameraFrameScript()
{
}

void CZ4CameraFrameScript::start()
{
	vector<CGameObject*> playerObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", playerObject);
	if (playerObject.empty() == false)
	{
		target = playerObject[0];

		vector<CScript*> findScript = playerObject[0]->GetScripts();
		if (findScript.empty() == false)
		{
			for (int index = 0; index < findScript.size(); index++)
			{
				if (findScript[index]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
				{
					playerScript = dynamic_cast<CPlayerScript*>(findScript[index]);
				}
			}
		}
		else
		{
			assert(false);
		}
	}


	vector<CGameObject*> childObject = Object()->GetChild();
	for (int index = 0; index < childObject.size(); index++)
	{
		vector<CScript*> childScript = childObject[index]->GetScripts();
		if (childScript.empty() == false)
		{
			if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z3CAMERABOTTOMCHECKSCRIPT)
			{
				cameraBottomScript = dynamic_cast<CZ3CameraBottomCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z5CAMERATOPCHECKSCRIPT)
			{
				cameraTopScript = dynamic_cast<CZ5CameraTopCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z6CAMERARIGHTCHECKSCRIPT)
			{
				cameraRightScript = dynamic_cast<CZ6CameraRightCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z7CAMERALEFTCHECKSCRIPT)
			{
				cameraLeftScript = dynamic_cast<CZ7CameraLeftCheckScript*>(childScript[0]);
			}
		}
	}
}

void CZ4CameraFrameScript::update()
{
	if (target->IsActive() == true)
	{
		Vec3 cameraFramePosition = Object()->Transform()->GetLocalPos();
		Vec3 targetPosition = target->Transform()->GetLocalPos();

		if (isPotalUse == false)
		{

			bool isBottomCollision = cameraBottomScript->GetIsCollision();
			bool isTopCollision = cameraTopScript->GetIsCollision();
			if (isBottomCollision == true || isTopCollision == true)
			{
				if (isBottomCollision == true)
				{
					if (targetPosition.y > cameraFramePosition.y)
					{
						cameraFramePosition.y = targetPosition.y;
					}
				}

				if (isTopCollision == true)
				{
					if (targetPosition.y < cameraFramePosition.y)
					{
						cameraFramePosition.y = targetPosition.y;
					}
				}
			}
			else
			{
				Vec3 VectorCameraFrameToTarget = targetPosition - cameraFramePosition;
				
				Vec3 distanceCameraFrameToTarget = VectorCameraFrameToTarget;

				distanceCameraFrameToTarget.x = 0.f;
				distanceCameraFrameToTarget.z = 0.f;

				distanceCameraFrameToTarget = XMVector2Length(distanceCameraFrameToTarget);

				Vec3 cameraFrameMoveDirection = XMVector2Normalize(VectorCameraFrameToTarget);

				if (distanceCameraFrameToTarget.x > MOVE_START_DISTANCE)
				{
					cameraFramePosition.y += cameraFrameMoveDirection.y*MOVE_SPEED*DT;
				}
				else
				{
					cameraFramePosition.y = targetPosition.y;
				}
			}


			bool isRightCollision = cameraRightScript->GetIsCollision();
			bool isLeftCollision = cameraLeftScript->GetIsCollision();
			if (isRightCollision == true || isLeftCollision == true)
			{
				if (isLeftCollision == true)
				{
					if (targetPosition.x > cameraFramePosition.x)
					{
						cameraFramePosition.x = targetPosition.x;
					}
				}

				if (isRightCollision == true)
				{
					if (targetPosition.x < cameraFramePosition.x)
					{
						cameraFramePosition.x = targetPosition.x;
					}
				}
			}
			else
			{
				Vec3 VectorCameraFrameToTarget = targetPosition - cameraFramePosition;

				Vec3 distanceCameraFrameToTarget = VectorCameraFrameToTarget;

				distanceCameraFrameToTarget.y = 0.f;
				distanceCameraFrameToTarget.z = 0.f;

				distanceCameraFrameToTarget = XMVector2Length(distanceCameraFrameToTarget);

				Vec3 cameraFrameMoveDirection = XMVector2Normalize(VectorCameraFrameToTarget);

				if (distanceCameraFrameToTarget.x > MOVE_START_DISTANCE)
				{
					cameraFramePosition.x += cameraFrameMoveDirection.x*MOVE_SPEED*DT;
				}
				else
				{
					cameraFramePosition.x = targetPosition.x;
				}
			}

		}
		else
		{
			if (playerScript->GetIsCameraFocusPositionFind() == true &&
				isPotalUse == true)
			{
				cameraFramePosition = playerScript->GetCameraFocusPosition();
				isPotalUse = false;
				playerScript->SetIsCameraFocusPositionFind(false);
			}

		}

		Object()->Transform()->SetLocalPos(cameraFramePosition);
	}
}
