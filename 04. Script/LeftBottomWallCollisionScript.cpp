#include "stdafx.h"
#include "LeftBottomWallCollisionScript.h"
#include "BottomWallCollisionScript.h"
#include "GravityScript.h"

CLeftBottomWallCollisionScript::CLeftBottomWallCollisionScript() : 
	CScript((UINT)SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT)
{
}


CLeftBottomWallCollisionScript::~CLeftBottomWallCollisionScript()
{
}

void CLeftBottomWallCollisionScript::start()
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


	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
		}
	}
}

void CLeftBottomWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionOn = true;

	bottomWallCollisionScript->SetCollision(false);
}

void CLeftBottomWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	if (collisionOn == true)
	{
		gravityScript->SetActiveGravity(false);

		CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();
		DirectX::XMVECTOR objectWorldPos[4];

		Matrix objectWorldMatrix = _pOther->Object()->Transform()->GetWorldMat();
		for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++)
		{
			objectWorldPos[vertexIndex] = DirectX::XMVector3TransformCoord(pVtx[vertexIndex].vPos, objectWorldMatrix);
		}

		//y=(y2-y1/x2-x1)*(x-x1) + y1
		float x1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[0];
		float x2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[0];
		float y1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[1];
		float y2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[1];

		float characterPositionX = Object()->GetParent()->Collider2D()->GetFinalPositon().x - Object()->GetParent()->Collider2D()->GetFinalScale().x / 2;
		float x = characterPositionX;

		if (x < x1)
		{
			return;
		}

		float y = ((y2 - y1) / (x2 - x1))*(x - x1) + y1;

		Vector3 characterPosition = Object()->GetParent()->Collider2D()->GetFinalPositon();
		Vector3 characterScale = Object()->GetParent()->Collider2D()->GetFinalScale();
		characterPosition.y = y + (characterScale.y / 2) - 7.f;
		Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
	}
}

void CLeftBottomWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;

	gravityScript->SetActiveGravity(true);
}
