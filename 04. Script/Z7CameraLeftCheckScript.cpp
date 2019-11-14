#include "stdafx.h"
#include "Z7CameraLeftCheckScript.h"


CZ7CameraLeftCheckScript::CZ7CameraLeftCheckScript() : 
	CScript((UINT)SCRIPT_TYPE::Z7CAMERALEFTCHECKSCRIPT)
{
}


CZ7CameraLeftCheckScript::~CZ7CameraLeftCheckScript()
{
}

void CZ7CameraLeftCheckScript::OnCollisionEnter(CCollider2D * _pOther)
{
	isCollision = true;
}

void CZ7CameraLeftCheckScript::OnCollision(CCollider2D * _pOther)
{
	if (isCollision == true)
	{
		Vector3 cameraFramePosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vector3 cameraFrameScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		cameraFramePosition.x = _pOther->Object()->Transform()->GetLocalPos().x + (_pOther->Object()->Transform()->GetLocalScale().x / 2) + (cameraFrameScale.x / 2);
		Object()->GetParent()->Transform()->SetLocalPos(cameraFramePosition);
	}
}

void CZ7CameraLeftCheckScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCollision = false;
}
