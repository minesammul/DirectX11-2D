#include "stdafx.h"
#include "PlayerActionStateDash.h"
#include "PlayerActionStateIdle.h"
#include "BottomWallCollisionScript.h"
#include "RightBottomWallCollisionScript.h"
#include "LeftBottomWallCollisionScript.h"
#include "TopWallCollisionScript.h"
#include "RightWallCollisionScript.h"
#include "LeftWallCollisionScript.h"

#include "ZZ2AfterImageScript.h"

PlayerActionStateDash::PlayerActionStateDash()
{
	dashAfterImageOutputTime = 0.f;
}


PlayerActionStateDash::~PlayerActionStateDash()
{
}

void PlayerActionStateDash::FindAnimation(CPlayerScript * player)
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

void PlayerActionStateDash::TransactionState(CPlayerScript * player)
{
	ChangeDashToIdle(player);
}

void PlayerActionStateDash::ChangeDashToIdle(CPlayerScript * player)
{
	CheckDashDistance(player);
	CheckDashWithWallCollision(player);
}

void PlayerActionStateDash::CheckDashDistance(CPlayerScript * player)
{
	Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
	playerPosition.x += dashDirection.x*DASH_POWER*DT;
	playerPosition.y += dashDirection.y*DASH_POWER*DT;
	player->Object()->Transform()->SetLocalPos(playerPosition);

	XMVECTOR nowDistance = XMVector3Length(startPosition - playerPosition);
	if (nowDistance.vector4_f32[0] > DASH_DISTANCE)
	{
		player->SetActionState(PlayerActionStateIdle::GetInstance());
	}
}

void PlayerActionStateDash::CheckDashWithWallCollision(CPlayerScript * player)
{
	bool isCollision = false;

	vector<CGameObject*> childObjects = player->Object()->GetChild();
	for (int objectIndex = 0; objectIndex < childObjects.size(); objectIndex++)
	{
		vector<CScript*> childScripts = childObjects[objectIndex]->GetScripts();
		for (int scriptIndex = 0; scriptIndex < childScripts.size(); scriptIndex++)
		{
			switch ((UINT)childScripts[scriptIndex]->GetScriptType())
			{
			case (UINT)SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT:
			{
				CBottomWallCollisionScript* script = dynamic_cast<CBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::LEFTBOTTOMWALLCOLLISIONSCRIPT:
			{
				CLeftBottomWallCollisionScript* script = dynamic_cast<CLeftBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT:
			{
				CRightBottomWallCollisionScript* script = dynamic_cast<CRightBottomWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::LEFTWALLCOLLISIONSCRIPT:
			{
				CLeftWallCollisionScript* script = dynamic_cast<CLeftWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::RIGHTWALLCOLLISIONSCRIPT:
			{
				CRightWallCollisionScript* script = dynamic_cast<CRightWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			case (UINT)SCRIPT_TYPE::TOPWALLCOLLISIONSCRIPT:
			{
				CTopWallCollisionScript* script = dynamic_cast<CTopWallCollisionScript*>(childScripts[scriptIndex]);
				isCollision = script->GetCollision();
			}
			break;

			}

			if (isCollision == true)
			{
				player->SetActionState(PlayerActionStateIdle::GetInstance());
			}
		}
	}
}

void PlayerActionStateDash::CreateDashAfterImage(CPlayerScript * player)
{
	dashAfterImageOutputTime -= DT;
	if (dashAfterImageOutputTime < 0.f)
	{
		dashAfterImageOutputTime = 0.05f;
		map<UINT, CScript*> prefabInputScripts;

		CResPtr<CPrefab> dashAfterImage = player->GetDashAfterImagePrefab();

		vector<UINT> prefabScriptTypes = dashAfterImage->GetScriptType();
		vector<wstring> allScriptInfo;
		CScriptMgr::GetScriptInfo(allScriptInfo);

		for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
		{
			UINT scriptType = prefabScriptTypes[scriptIndex];
			wstring scriptName = allScriptInfo[scriptType];
			CScript* prefabScript = CScriptMgr::GetScript(scriptName);

			if (prefabScript->GetScriptType() == (UINT)SCRIPT_TYPE::ZZ2AFTERIMAGESCRIPT)
			{
				CZZ2AfterImageScript* afterImageScript = dynamic_cast<CZZ2AfterImageScript*>(prefabScript);

				Vector3 mouseDirection = player->GetMouseDirection();

				if (mouseDirection.x > 0)
				{
					afterImageScript->SetInverse(0);
				}
				else
				{
					afterImageScript->SetInverse(1);
				}
			}

			prefabInputScripts[scriptType] = prefabScript;
		}

		Vector3 playerPosition = player->Object()->Transform()->GetLocalPos();
		player->Instantiate(dashAfterImage, playerPosition, prefabInputScripts);
	}
}

void PlayerActionStateDash::Update(CPlayerScript * player)
{
	FindAnimation(player);
	TransactionState(player);
	CreateDashAfterImage(player);
}
