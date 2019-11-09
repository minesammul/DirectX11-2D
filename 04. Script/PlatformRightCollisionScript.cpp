#include "stdafx.h"
#include "PlatformRightCollisionScript.h"
#include "GravityScript.h"
#include "PlayerScript.h"
#include "PlayerActionStateJump.h"

CPlatformRightCollisionScript::CPlatformRightCollisionScript():
	CScript((UINT)SCRIPT_TYPE::PLATFORMRIGHTCOLLISIONSCRIPT)
{
}


CPlatformRightCollisionScript::~CPlatformRightCollisionScript()
{
}

void CPlatformRightCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionOn = true;

	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
		{
			CPlayerScript* playerScript = dynamic_cast<CPlayerScript*>(parentScripts[scriptIndex]);
			if (playerScript->GetActionState() == PlayerActionStateJump::GetInstance())
			{
				bool isFall = PlayerActionStateJump::GetInstance()->GetIsFall();

				if (isFall == false)
				{
					collisionOn = false;
				}
			}
		}
	}
}

void CPlatformRightCollisionScript::OnCollision(CCollider2D * _pOther)
{
	if (collisionOn == true)
	{
		vector<CScript*> parentScripts;
		parentScripts = Object()->GetParent()->GetScripts();

		for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
		{
			if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
			{
				CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
				gravityScript->SetActiveGravity(false);
			}
		}

		CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();
		DirectX::XMVECTOR objectWorldPos[4];

		Matrix objectWorldMatrix = _pOther->Object()->Transform()->GetWorldMat();
		for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++)
		{
			objectWorldPos[vertexIndex] = DirectX::XMVector3TransformCoord(pVtx[vertexIndex].vPos, objectWorldMatrix);
		}

		////y=(y2-y1/x2-x1)*(x-x1) + y1
		float x1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[0];
		float x2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[0];
		float y1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[1];
		float y2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[1];

		collisionMoveDirection = objectWorldPos[USE_POINT_INDEX_0] - objectWorldPos[USE_POINT_INDEX_1];
	}
}

void CPlatformRightCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;

	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(true);
		}
	}
}
