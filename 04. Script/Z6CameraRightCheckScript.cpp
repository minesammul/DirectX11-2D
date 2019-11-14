#include "stdafx.h"
#include "Z6CameraRightCheckScript.h"


CZ6CameraRightCheckScript::CZ6CameraRightCheckScript() : 
	CScript((UINT)SCRIPT_TYPE::Z6CAMERARIGHTCHECKSCRIPT)
{
}


CZ6CameraRightCheckScript::~CZ6CameraRightCheckScript()
{
}

void CZ6CameraRightCheckScript::OnCollisionEnter(CCollider2D * _pOther)
{
	isCollision = true;
}

void CZ6CameraRightCheckScript::OnCollision(CCollider2D * _pOther)
{
	if (isCollision == true)
	{
		Vector3 cameraFramePosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vector3 cameraFrameScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		cameraFramePosition.x = _pOther->Object()->Transform()->GetLocalPos().x - (_pOther->Object()->Transform()->GetLocalScale().x / 2) - (cameraFrameScale.x / 2);
		Object()->GetParent()->Transform()->SetLocalPos(cameraFramePosition);
	}
}

void CZ6CameraRightCheckScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCollision = false;
}
