#include "stdafx.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateMove.h"
#include "PlayerActionStateJump.h"
#include "PlayerActionStateSit.h"
#include "PlayerActionStateDash.h"

#include "GravityScript.h"
#include "EffectScript.h"

#include <Camera.h>

PlayerActionStateIdle::PlayerActionStateIdle()
{
}


PlayerActionStateIdle::~PlayerActionStateIdle()
{
}

void PlayerActionStateIdle::FindAnimation(CPlayerScript * player)
{
	//임시코드. 캐릭터가 지닌 애니메이션 key값은 추후 코스튬의 분기점에 따라 달라진다.
	if (player->Object()->Animator2D()->GetAnimList().find(L"adventure_idle") !=
		player->Object()->Animator2D()->GetAnimList().end())
	{
		CAnimation2D* curAnimation = player->Object()->Animator2D()->GetAnimList().find(L"adventure_idle")->second;

		if (player->Object()->Animator2D()->GetCurAnim()->GetID() != curAnimation->GetID())
		{
			player->Object()->Animator2D()->SetCurAnim(curAnimation);
		}
	}

	if (player->Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
	{
		player->Object()->Animator2D()->GetCurAnim()->Play();
	}
}

void PlayerActionStateIdle::TransactionState(CPlayerScript * player)
{
	ChangeIdleToMove(player);
	ChangeIdleToSit(player);
	ChangeIdleToJump(player);
	ChangeIdleToDash(player);
}

void PlayerActionStateIdle::ChangeIdleToMove(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_TAB ||
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_TAB)
	{
		player->SetActionState(PlayerActionStateMove::GetInstance());
	}
}

void PlayerActionStateIdle::ChangeIdleToJump(CPlayerScript * player)
{
	vector<CScript*> playerScripts;
	playerScripts = player->Object()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < playerScripts.size(); scriptIndex++)
	{
		if (playerScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(playerScripts[scriptIndex]);
			if (gravityScript->GetActiveGravity() == true)
			{
				PlayerActionStateJump::GetInstance()->SetJumpPower(0.f);
				player->SetActionState(PlayerActionStateJump::GetInstance());
			}
			else
			{
				if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE) == KEY_STATE::STATE_TAB)
				{
					CreateJumpEffect(player);

					gravityScript->SetActiveGravity(true);

					Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
					playerPosition.y += 20.f;
					player->Object()->Transform()->SetLocalPos(playerPosition);

					PlayerActionStateJump::GetInstance()->SetJumpPower(PlayerActionStateJump::GetInstance()->JUMP_POWER);
					player->SetActionState(PlayerActionStateJump::GetInstance());
				}
			}

		}
	}
}

void PlayerActionStateIdle::ChangeIdleToSit(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S) == KEY_STATE::STATE_TAB)
	{
		player->SetActionState(PlayerActionStateSit::GetInstance());
	}
}

void PlayerActionStateIdle::ChangeIdleToDash(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RBTN) == KEY_STATE::STATE_TAB)
	{
		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
		PlayerActionStateDash::GetInstance()->SetStartPosition(playerPosition);


		Vector3 dashDirection = player->GetMouseDirection();
		playerPosition.x += dashDirection.x * PlayerActionStateDash::GetInstance()->DASH_FIRST_POWER;
		playerPosition.y += dashDirection.y * PlayerActionStateDash::GetInstance()->DASH_FIRST_POWER;

		player->Object()->Transform()->SetLocalPos(playerPosition);

		PlayerActionStateDash::GetInstance()->SetDashDirection(dashDirection);


		player->SetActionState(PlayerActionStateDash::GetInstance());
	}
}

void PlayerActionStateIdle::CreateJumpEffect(CPlayerScript * player)
{
	map<UINT, CScript*> prefabInputScripts;

	CResPtr<CPrefab> moveEffect = player->GetMoveEffectPrefab();

	vector<UINT> prefabScriptTypes = moveEffect->GetScriptType();
	vector<wstring> allScriptInfo;
	CScriptMgr::GetScriptInfo(allScriptInfo);

	for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
	{
		UINT scriptType = prefabScriptTypes[scriptIndex];
		wstring scriptName = allScriptInfo[scriptType];
		CScript* prefabScript = CScriptMgr::GetScript(scriptName);

		if (prefabScript->GetScriptType() == (UINT)SCRIPT_TYPE::EFFECTSCRIPT)
		{
			CEffectScript* effectScript = dynamic_cast<CEffectScript*>(prefabScript);
		}

		prefabInputScripts[scriptType] = prefabScript;
	}

	Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
	Vector3 effectPosition = playerPosition;
	effectPosition.y -= player->Object()->Collider2D()->GetFinalScale().y / 4;
	player->Instantiate(moveEffect, effectPosition, prefabInputScripts);
}

void PlayerActionStateIdle::Update(CPlayerScript * player)
{
	FindAnimation(player);
	TransactionState(player);
}
