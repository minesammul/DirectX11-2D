#include "stdafx.h"
#include "Z3CameraBottomCheckScript.h"


CZ3CameraBottomCheckScript::CZ3CameraBottomCheckScript() : 
	CScript((UINT)SCRIPT_TYPE::Z3CAMERABOTTOMCHECKSCRIPT)
{
	isCollision = false;
}


CZ3CameraBottomCheckScript::~CZ3CameraBottomCheckScript()
{
}

void CZ3CameraBottomCheckScript::OnCollisionEnter(CCollider2D * _pOther)
{
	isCollision = true;
}

void CZ3CameraBottomCheckScript::OnCollision(CCollider2D * _pOther)
{
	if (isCollision == true)
	{
		Vec3 cameraFramePosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vec3 cameraFrameScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		cameraFramePosition.y = _pOther->Object()->Transform()->GetLocalPos().y + (_pOther->Object()->Transform()->GetLocalScale().y / 2) + (cameraFrameScale.y / 2);
		Object()->GetParent()->Transform()->SetLocalPos(cameraFramePosition);
	}
}

void CZ3CameraBottomCheckScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCollision = false;
}
