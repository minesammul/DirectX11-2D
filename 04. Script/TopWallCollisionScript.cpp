#include "stdafx.h"
#include "TopWallCollisionScript.h"


CTopWallCollisionScript::CTopWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT)
{
}


CTopWallCollisionScript::~CTopWallCollisionScript()
{
}

void CTopWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionOn = true;
}

void CTopWallCollisionScript::OnCollision(CCollider2D* _pOther)
{
	Vec3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
	Vec3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
	characterPosition.y = _pOther->Object()->Transform()->GetLocalPos().y - (_pOther->Object()->Transform()->GetLocalScale().y / 2) - (characterScale.y / 2);
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CTopWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;
}
