#include "stdafx.h"
#include "MonsterCircleWaveBullet.h"
#include "BulletScript.h"

MonsterCircleWaveBullet::MonsterCircleWaveBullet()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\BansheeBullet.pref", L"Prefab\\BansheeBullet.pref");
	bullet = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\BansheeBullet.pref");
}


MonsterCircleWaveBullet::~MonsterCircleWaveBullet()
{
}

void MonsterCircleWaveBullet::Attack(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();

	for (int bulletCount = 0; bulletCount < 16; bulletCount++)
	{
		Vec3 bulletDirection = Vec3(1.0f, 0.0f, 0.0f);
		float radian = (2 * g_XMPi.f[0] / 16) * bulletCount;
		float xPosition = cosf(radian);
		float yPosition = sinf(radian);
		bulletDirection.x = xPosition;
		bulletDirection.y = yPosition;
		bulletDirection = XMVector2Normalize(bulletDirection);

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
			}

			prefabInputScripts[scriptType] = prefabScript;
		}

		monster->Instantiate(bullet, monster->Object()->Transform()->GetLocalPos(), prefabInputScripts);
	}

	SetIsAttack(false);
}
