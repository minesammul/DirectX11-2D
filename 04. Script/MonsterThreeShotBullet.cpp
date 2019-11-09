#include "stdafx.h"
#include "MonsterThreeShotBullet.h"
#include "BulletScript.h"


MonsterThreeShotBullet::MonsterThreeShotBullet()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\GiantBatBullet.pref", L"Prefab\\GiantBatBullet.pref");
	bullet = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\GiantBatBullet.pref");
}


MonsterThreeShotBullet::~MonsterThreeShotBullet()
{
}

void MonsterThreeShotBullet::Attack(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();

	for (int bulletCount=0; bulletCount < 3; bulletCount++)
	{
		Vec3 bulletMiddleDirection = monster->GetMonsterDirection();
		Vec3 mosnterNomalVector = Vec3(1.f, 0.f, 0.f);
		mosnterNomalVector = XMVector2Normalize(mosnterNomalVector);

		Vec3 bulletMiddleDirectionAngle = XMVector2AngleBetweenNormals(
			bulletMiddleDirection,
			mosnterNomalVector
		);

		float angle = bulletMiddleDirectionAngle.x;
		if (bulletMiddleDirection.y < 0)
		{
			angle = g_XMPi.f[0] * 2 - angle;
		}

		float degree = XMConvertToDegrees(angle);

		float bulletFirstDirectionDegree = degree - 30.f;
		float bulletFirstDirectionRadian = XMConvertToRadians(bulletFirstDirectionDegree);

		float bulletLastDirectionDegree = degree + 30.f;
		float bulletLastDirectionRadian = XMConvertToRadians(bulletLastDirectionDegree);

		Vec3 bulletFirstDirection = Vec3(
			cosf(bulletFirstDirectionRadian),
			sinf(bulletFirstDirectionRadian),
			0.f
		);

		Vec3 bulletLastDirection = Vec3(
			cosf(bulletLastDirectionRadian),
			sinf(bulletLastDirectionRadian),
			0.f
		);

		map<UINT, CScript*> prefabInputFirstScripts;
		map<UINT, CScript*> prefabInputMiddleScripts;
		map<UINT, CScript*> prefabInputLastScripts;

		vector<UINT> prefabScriptTypes = bullet->GetScriptType();
		vector<wstring> allScriptInfo;
		CScriptMgr::GetScriptInfo(allScriptInfo);

		for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
		{
			UINT scriptType = prefabScriptTypes[scriptIndex];
			wstring scriptName = allScriptInfo[scriptType];

			CScript* prefabFirstScript = CScriptMgr::GetScript(scriptName);
			CScript* prefabMiddleScript = CScriptMgr::GetScript(scriptName);
			CScript* prefabLastScript = CScriptMgr::GetScript(scriptName);

			if (prefabFirstScript->GetScriptType() == (UINT)SCRIPT_TYPE::BULLETSCRIPT)
			{
				CBulletScript* bulletFirstScript = dynamic_cast<CBulletScript*>(prefabFirstScript);
				bulletFirstScript->SetDirection(bulletFirstDirection);
				bulletFirstScript->SetDelayTime(0.5f + bulletCount * 0.3);

				CBulletScript* bulletMiddleScript = dynamic_cast<CBulletScript*>(prefabMiddleScript);
				bulletMiddleScript->SetDirection(bulletMiddleDirection);
				bulletMiddleScript->SetDelayTime(0.5f + bulletCount * 0.3);

				CBulletScript* bulletLastScript = dynamic_cast<CBulletScript*>(prefabLastScript);
				bulletLastScript->SetDirection(bulletLastDirection);
				bulletLastScript->SetDelayTime(0.5f + bulletCount * 0.3);
			}

			prefabInputFirstScripts[scriptType] = prefabFirstScript;
			prefabInputMiddleScripts[scriptType] = prefabMiddleScript;
			prefabInputLastScripts[scriptType] = prefabLastScript;
		}


		Vec3 bulletFirstPosition = monster->Object()->Transform()->GetLocalPos();
		bulletFirstPosition.x += bulletFirstDirection.x*20.f;
		bulletFirstPosition.y += bulletFirstDirection.y*20.f;

		bulletFirstPosition.z -= 1;

		monster->Instantiate(bullet, bulletFirstPosition, prefabInputFirstScripts);


		Vec3 bulletMiddlePosition = monster->Object()->Transform()->GetLocalPos();
		bulletMiddlePosition.x += bulletMiddleDirection.x*20.f;
		bulletMiddlePosition.y += bulletMiddleDirection.y*20.f;

		bulletMiddlePosition.z -= 1;

		monster->Instantiate(bullet, bulletMiddlePosition, prefabInputMiddleScripts);


		Vec3 bulletLastPosition = monster->Object()->Transform()->GetLocalPos();
		bulletLastPosition.x += bulletLastDirection.x*20.f;
		bulletLastPosition.y += bulletLastDirection.y*20.f;

		bulletLastPosition.z -= 1;

		monster->Instantiate(bullet, bulletLastPosition, prefabInputLastScripts);
	}

	SetIsAttack(false);
}
