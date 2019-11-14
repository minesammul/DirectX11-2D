#include "stdafx.h"
#include "CameraScript.h"

#include <Camera.h>

CCameraScript::CCameraScript() : 
	CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
{
}


CCameraScript::~CCameraScript()
{
}

void CCameraScript::start()
{
	vector<CGameObject*> playerObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"CameraFrame", playerObject);
	if (playerObject.empty()==false)
	{
		target = playerObject[0];
	}
}

void CCameraScript::update()
{
	if (target->IsActive() == true)
	{
		Vector3 cameraPosition = Object()->Transform()->GetLocalPos();
		Vector3 targetPosition = target->Transform()->GetLocalPos();

		cameraPosition.x = targetPosition.x;
		cameraPosition.y = targetPosition.y;

		Object()->Transform()->SetLocalPos(cameraPosition);

		float cameraScale = 1.f;

		CCamera* nowCamera = Object()->Camera();

		Object()->Camera()->SetScale(cameraScale);
	}

}
