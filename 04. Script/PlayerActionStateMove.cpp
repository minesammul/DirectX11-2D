#include "stdafx.h"
#include "PlayerActionStateMove.h"
#include "PlayerActionStateIdle.h"
#include "PlatformRightCollisionScript.h"

#include "EffectScript.h"

PlayerActionStateMove::PlayerActionStateMove()
{
}


PlayerActionStateMove::~PlayerActionStateMove()
{
}

void PlayerActionStateMove::FindAnimation(CPlayerScript * player)
{
	//임시코드. 캐릭터가 지닌 애니메이션 key값은 추후 코스튬의 분기점에 따라 달라진다.
	if (player->Object()->Animator2D()->GetAnimList().find(L"adventure_move") !=
		player->Object()->Animator2D()->GetAnimList().end())
	{
		CAnimation2D* curAnimation = player->Object()->Animator2D()->GetAnimList().find(L"adventure_move")->second;

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

void PlayerActionStateMove::ActionState(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
	{
		CreateMoveEffect(player);

		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();

		playerPosition.x -= player->GetMoveSpeed()*(player->GetMoveDirection().x)*DT;
		playerPosition.y -= player->GetMoveSpeed()*(player->GetMoveDirection().y)*DT;

		player->Object()->Transform()->SetLocalPos(playerPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
	{
		CreateMoveEffect(player);

		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();

		playerPosition.x += player->GetMoveSpeed()*(player->GetMoveDirection().x)*DT;
		playerPosition.y += player->GetMoveSpeed()*(player->GetMoveDirection().y)*DT;

		player->Object()->Transform()->SetLocalPos(playerPosition);
	}
}

void PlayerActionStateMove::TransactionState(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_AWAY ||
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_AWAY)
	{
		player->SetActionState(PlayerActionStateIdle::GetInstance());
	}
}

void PlayerActionStateMove::CreateMoveEffect(CPlayerScript * player)
{
	moveEffectOutputTime -= DT;
	if (moveEffectOutputTime < 0.f)
	{
		moveEffectOutputTime = 0.15f;
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
		effectPosition.y -= player->Object()->Collider2D()->GetFinalScale().y/4;
		player->Instantiate(moveEffect, effectPosition, prefabInputScripts);
	}
}

void PlayerActionStateMove::Update(CPlayerScript * player)
{
	FindAnimation(player);
	TransactionState(player);
	ActionState(player);
}
