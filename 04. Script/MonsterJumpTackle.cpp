#include "stdafx.h"
#include "MonsterJumpTackle.h"
#include "GravityScript.h"


MonsterJumpTackle::MonsterJumpTackle()
{
	firstJumping = false;
	gravityApply = true;
}


MonsterJumpTackle::~MonsterJumpTackle()
{
}


void MonsterJumpTackle::Init()
{
	firstJumping = false;
	gravityApply = true;
}


void MonsterJumpTackle::Attack(CMonsterScript * monster)
{
	if (GetIsAttack() == true)
	{
		monster->SetMonsterDirectionImage();
		if (firstJumping == false)
		{
			Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();
			monsterPosition.y += 20.f;
			monster->Object()->Transform()->SetLocalPos(monsterPosition);
			firstJumping = true;
		}
		else
		{
			Vec3 monsterDirection = monster->GetMonsterDirection();
			Vec3 monsterPosition = monster->Object()->Transform()->GetLocalPos();

			monsterPosition.x += monsterDirection.x*200.f*DT;
			monsterPosition.y += 200.f*DT;
	
			monster->Object()->Transform()->SetLocalPos(monsterPosition);

			vector<CScript*> monsterScripts = monster->Object()->GetScripts();
			for (int scriptIndex = 0; scriptIndex < monsterScripts.size(); scriptIndex++)
			{
				if (monsterScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
				{
					CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(monsterScripts[scriptIndex]);
					gravityApply = gravityScript->GetActiveGravity();
					break;
				}
			}

			if (gravityApply == false)
			{
				SetIsAttack(false);
			}
		}
	}
}

