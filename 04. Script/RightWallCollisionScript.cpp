#include "stdafx.h"
#include "RightWallCollisionScript.h"
#include "BottomWallCollisionScript.h"


CRightWallCollisionScript::CRightWallCollisionScript():
	CScript((UINT)SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT)
{
}


CRightWallCollisionScript::~CRightWallCollisionScript()
{
}

void CRightWallCollisionScript::start()
{
	vector<CGameObject*> brotherObject = Object()->GetParent()->GetChild();
	for (int brotherIndex = 0; brotherIndex < brotherObject.size(); brotherIndex++)
	{
		vector<CScript*> brotherScripts;
		brotherScripts = brotherObject[brotherIndex]->GetScripts();

		for (int scriptIndex = 0; scriptIndex < brotherScripts.size(); scriptIndex++)
		{
			if (brotherScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT)
			{
				bottomWallCollisionScript = dynamic_cast<CBottomWallCollisionScript*>(brotherScripts[scriptIndex]);
			}
		}
	}
}

void CRightWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionOn = true;
}

void CRightWallCollisionScript::OnCollision(CCollider2D * _pOther)
{

	bool isBottomWallCollision = false;
	Vec3 bottomWallCollisionPosition = Vec3(0.f, 0.f, 0.f);

	isBottomWallCollision = bottomWallCollisionScript->GetCollision();
	bottomWallCollisionPosition = bottomWallCollisionScript->GetCollisionPosition();

	Vec3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
	if (isBottomWallCollision == true)
	{
		characterPosition.y = bottomWallCollisionPosition.y;
	}
	
	Vec3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
	characterPosition.x = _pOther->Object()->Transform()->GetLocalPos().x - (_pOther->Object()->Transform()->GetLocalScale().x / 2) - (characterScale.x / 2);
	Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
}

void CRightWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;
}
