#include "stdafx.h"
#include "GravityScript.h"


CGravityScript::CGravityScript():
	CScript((UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
{
	nowGravityValue = GRAVITY_VALUE;
	activeGravity = true;
}


CGravityScript::~CGravityScript()
{
}

void CGravityScript::update()
{
	if (activeGravity == false)
	{
		nowGravityValue = GRAVITY_VALUE;
		return;
	}

	nowGravityValue += GRAVITY_VALUE;

	Vec3 objectPosition = Object()->Transform()->GetLocalPos();
	objectPosition.y -= nowGravityValue * DT;
	Object()->Transform()->SetLocalPos(objectPosition);
}
