#include "stdafx.h"
#include "PlayerActionStateSit.h"
#include "PlayerActionStateJump.h"

PlayerActionStateSit::PlayerActionStateSit()
{
}


PlayerActionStateSit::~PlayerActionStateSit()
{
}

void PlayerActionStateSit::Update(CPlayerScript * player)
{
	if (player->Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
	{
		player->Object()->Animator2D()->GetCurAnim()->Play();
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE) == KEY_STATE::STATE_TAB)
	{
		Vec3 playerPosition = player->Object()->Transform()->GetLocalPos();
		playerPosition.y -= 10.f;
		player->Object()->Transform()->SetLocalPos(playerPosition);

		PlayerActionStateJump::GetInstance()->SetJumpPower(0.f);
		player->SetActionState(PlayerActionStateJump::GetInstance());
	}
}
