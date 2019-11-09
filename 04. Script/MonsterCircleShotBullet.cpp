#include "stdafx.h"
#include "MonsterCircleShotBullet.h"
#include "BulletScript.h"


MonsterCircleShotBullet::MonsterCircleShotBullet()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\GiantBatBullet.pref", L"Prefab\\GiantBatBullet.pref");
	bullet = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\GiantBatBullet.pref");
}


MonsterCircleShotBullet::~MonsterCircleShotBullet()
{
}

void MonsterCircleShotBullet::Attack(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();

	Vec3 bulletDirection = monster->GetMonsterDirection();

	for (int bulletCount = 0; bulletCount < 16; bulletCount++)
	{
		Vec3 bulletCreateDirection = Vec3(1.0f, 0.0f, 0.0f);
		float radian = (2 * g_XMPi.f[0] / 16) * bulletCount;
		float xPosition = cosf(radian);
		float yPosition = sinf(radian);
		bulletCreateDirection.x = xPosition;
		bulletCreateDirection.y = yPosition;
		bulletCreateDirection = XMVector2Normalize(bulletCreateDirection);

		map<UINT, CScript*> prefabInputScripts;

		vector<UINT> prefabScriptTypes = bullet->GetScriptType();
		vector<wstring> allScriptInfo;
		CScriptMgr::GetScriptInfo(allScriptInfo);

		for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
		{
			UINT scriptType = prefabScriptTypes[scriptIndex];
			wstring scriptName = allScriptInfo[scriptType];
			CScript* prefabScript = CScriptMgr::GetScript(scriptName);

			if (prefabScript->GetScriptType() == (UINT)SCRIPT_TYPE::BULLETSCRIPT)
			{
				CBulletScript* bulletScript = dynamic_cast<CBulletScript*>(prefabScript);
				bulletScript->SetDirection(bulletDirection);
				bulletScript->SetDelayTime(0.5f);
			}

			prefabInputScripts[scriptType] = prefabScript;
		}

		Vec3 bulletPosition = monster->Object()->Transform()->GetLocalPos();
		bulletPosition.x += bulletCreateDirection.x*CREATE_INTERVAL;
		bulletPosition.y += bulletCreateDirection.y*CREATE_INTERVAL;

		monster->Instantiate(bullet, bulletPosition, prefabInputScripts);
	}

	SetIsAttack(false);
}
