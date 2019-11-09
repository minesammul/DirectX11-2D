#include "stdafx.h"
#include "MonsterOneShotBullet.h"

#include "BulletScript.h"


MonsterOneShotBullet::MonsterOneShotBullet()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Bat_RedBullet.pref", L"Prefab\\Bat_RedBullet.pref");
	bullet = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Bat_RedBullet.pref");
}


MonsterOneShotBullet::~MonsterOneShotBullet()
{
}

void MonsterOneShotBullet::Attack(CMonsterScript * monster)
{
	monster->SetMonsterDirectionImage();

	Vec3 bulletDirection = monster->GetMonsterDirection();

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
	bulletPosition.x += bulletDirection.x*20.f;
	bulletPosition.y += bulletDirection.y*20.f;

	bulletPosition.z -= 1;


	monster->Instantiate(bullet, bulletPosition, prefabInputScripts);

	SetIsAttack(false);
}
