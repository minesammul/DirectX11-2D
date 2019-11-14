#include "stdafx.h"
#include "PlayerActionStateJump.h"
#include "PlayerActionStateIdle.h"
#include "PlayerActionStateDash.h"
#include "TopWallCollisionScript.h"
#include "GravityScript.h"


PlayerActionStateJump::PlayerActionStateJump()
{
	isFall = false;
	gravityScript = nullptr;
}


PlayerActionStateJump::~PlayerActionStateJump()
{
}

void PlayerActionStateJump::FindAnimation(CPlayerScript * player)
{
	//임시코드. 캐릭터가 지닌 애니메이션 key값은 추후 코스튬의 분기점에 따라 달라진다.
	if (player->Object()->Animator2D()->GetAnimList().find(L"adventure_jump") !=
		player->Object()->Animator2D()->GetAnimList().end())
	{
		CAnimation2D* curAnimation = player->Object()->Animator2D()->GetAnimList().find(L"adventure_jump")->second;

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

void PlayerActionStateJump::ActionState(CPlayerScript * player)
{
	ActionJump(player);
	ActionMove(player);
}

void PlayerActionStateJump::ActionJump(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE) == KEY_STATE::STATE_HOLD)
	{
		if (nowJumpPower < MAX_JUMP_POWER)
		{
			nowJumpPower *= ADD_JUMP_POWER;
		}
	}

	vector<CGameObject*> childObjects = player->Object()->GetChild();
	for (int objectIndex = 0; objectIndex < childObjects.size(); objectIndex++)
	{
		bool isFind = false;

		vector<CScript*> scripts = childObjects[objectIndex]->GetScripts();
		for (int scriptIndex = 0; scriptIndex < scripts.size(); scriptIndex++)
		{
			if (scripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT)
			{
				CTopWallCollisionScript* topWallCollisionScript = dynamic_cast<CTopWallCollisionScript*>(scripts[scriptIndex]);
				if (topWallCollisionScript->GetCollision() == true)
				{
					nowJumpPower = 0.f;
				}
				isFind = true;
				break;
			}
		}

		if (isFind == true)
		{
			break;
		}
	}


	Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
	playerPosition.y += nowJumpPower * DT;
	player->Object()->Transform()->SetLocalPos(playerPosition);
}

void PlayerActionStateJump::ActionMove(CPlayerScript * player)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A) == KEY_STATE::STATE_HOLD)
	{
		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
		playerPosition.x -= player->GetMoveSpeed() * DT;
		player->Object()->Transform()->SetLocalPos(playerPosition);
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D) == KEY_STATE::STATE_HOLD)
	{
		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
		playerPosition.x += player->GetMoveSpeed() * DT;
		player->Object()->Transform()->SetLocalPos(playerPosition);
	}
}

void PlayerActionStateJump::TransactionState(CPlayerScript * player)
{
	ChangeJumpToIdle(player);
	ChangeJumpToDash(player);
}

void PlayerActionStateJump::ChangeJumpToIdle(CPlayerScript * player)
{
	if (gravityScript == nullptr)
	{
		vector<CScript*> objectScripts = player->Object()->GetScripts();
		for (int scriptIndex = 0; scriptIndex < objectScripts.size(); scriptIndex++)
		{
			if (objectScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
			{
				gravityScript = dynamic_cast<CGravityScript*>(objectScripts[scriptIndex]);

				if (gravityScript->GetActiveGravity() == false)
				{
					player->SetActionState(PlayerActionStateIdle::GetInstance());
				}
			}
		}
	}
	else
	{
		if (gravityScript->GetActiveGravity() == false)
		{
			player->SetActionState(PlayerActionStateIdle::GetInstance());
		}
	}
}

void PlayerActionStateJump::ChangeJumpToDash(CPlayerScript * player)
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


		if (gravityScript == nullptr)
		{
			vector<CScript*> objectScripts = player->Object()->GetScripts();
			for (int scriptIndex = 0; scriptIndex < objectScripts.size(); scriptIndex++)
			{
				if (objectScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
				{
					gravityScript = dynamic_cast<CGravityScript*>(objectScripts[scriptIndex]);

					gravityScript->SetNowGravityValue(0.f);
				}
			}
		}
		else
		{
			gravityScript->SetNowGravityValue(0.f);
		}


		player->SetActionState(PlayerActionStateDash::GetInstance());
	}
}

void PlayerActionStateJump::CheckFall(CPlayerScript * player)
{
	if (gravityScript == nullptr)
	{
		vector<CScript*> objectScripts = player->Object()->GetScripts();
		for (int scriptIndex = 0; scriptIndex < objectScripts.size(); scriptIndex++)
		{
			if (objectScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
			{
				gravityScript = dynamic_cast<CGravityScript*>(objectScripts[scriptIndex]);

				if (gravityScript->GetNowGravityValue() > nowJumpPower)
				{
					isFall = true;
				}
				else
				{
					isFall = false;
				}
			}
		}
	}
	else
	{
		if (gravityScript->GetNowGravityValue() > nowJumpPower)
		{
			isFall = true;
		}
		else
		{
			isFall = false;
		}
	}
}

void PlayerActionStateJump::Update(CPlayerScript * player)
{
	FindAnimation(player);
	ActionState(player);
	CheckFall(player);
	TransactionState(player);	
}
