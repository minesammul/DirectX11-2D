#include "stdafx.h"
#include "Z5CameraTopCheckScript.h"


CZ5CameraTopCheckScript::CZ5CameraTopCheckScript():
	CScript((UINT)SCRIPT_TYPE::Z5CAMERATOPCHECKSCRIPT)
{
}


CZ5CameraTopCheckScript::~CZ5CameraTopCheckScript()
{
}

void CZ5CameraTopCheckScript::OnCollisionEnter(CCollider2D * _pOther)
{
	isCollision = true;
}

void CZ5CameraTopCheckScript::OnCollision(CCollider2D * _pOther)
{
	if (isCollision == true)
	{
		Vector3 cameraFramePosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vector3 cameraFrameScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		cameraFramePosition.y = _pOther->Object()->Transform()->GetLocalPos().y - (_pOther->Object()->Transform()->GetLocalScale().y / 2) - (cameraFrameScale.y / 2);
		Object()->GetParent()->Transform()->SetLocalPos(cameraFramePosition);
	}
}

void CZ5CameraTopCheckScript::OnCollisionExit(CCollider2D * _pOther)
{
	isCollision = false;
}
