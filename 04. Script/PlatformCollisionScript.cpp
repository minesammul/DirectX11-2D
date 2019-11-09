#include "stdafx.h"
#include "PlatformCollisionScript.h"
#include "GravityScript.h"
#include "PlayerActionState.h"
#include "PlayerActionStateJump.h"

CPlatformCollisionScript::CPlatformCollisionScript():
	CScript((UINT)SCRIPT_TYPE::PLATFORMCOLLISIONSCRIPT)
{
	playerScript = nullptr;
	gravityScript = nullptr;
}


CPlatformCollisionScript::~CPlatformCollisionScript()
{
}

void CPlatformCollisionScript::start()
{
	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
		{
			playerScript = dynamic_cast<CPlayerScript*>(parentScripts[scriptIndex]);
		}
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
		}
	}
}

void CPlatformCollisionScript::update()
{
}

void CPlatformCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	if (playerScript != nullptr)
	{
		if (playerScript->GetActionState() == PlayerActionStateJump::GetInstance())
		{
			bool isFall = PlayerActionStateJump::GetInstance()->GetIsFall();

			if (isFall == false)
			{
				return;
			}
		}
	}

	gravityScript->SetActiveGravity(false);
}

void CPlatformCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	gravityScript->SetActiveGravity(true);
}
