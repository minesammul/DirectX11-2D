#include "stdafx.h"
#include "MonsterResponseScript.h"


CMonsterResponseScript::CMonsterResponseScript()
	:CScript((UINT)SCRIPT_TYPE::MONSTERRESPONSESCRIPT)
{
	isSpawn = false;
}


CMonsterResponseScript::~CMonsterResponseScript()
{
}

void CMonsterResponseScript::SpawnMonster(void)
{
	vector<CGameObject*> monsterSpawns = Object()->GetChild();
	for (int spawnIndex = 0; spawnIndex < monsterSpawns.size(); spawnIndex++)
	{
		if (monsterSpawns[spawnIndex]->IsActive() == false)
		{
			continue;
		}

		{
			map<UINT, CScript*> prefabInputScripts;

			vector<UINT> prefabScriptTypes = monsterSpawnEffectPrefab->GetScriptType();
			vector<wstring> allScriptInfo;
			CScriptMgr::GetScriptInfo(allScriptInfo);

			for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
			{
				UINT scriptType = prefabScriptTypes[scriptIndex];
				wstring scriptName = allScriptInfo[scriptType];
				CScript* prefabScript = CScriptMgr::GetScript(scriptName);
				prefabInputScripts[scriptType] = prefabScript;
			}

			Vector3 paraentPosition = Object()->Transform()->GetLocalPos();
			Vector3 paraentScale = Object()->Transform()->GetLocalScale();
			Vector3 childPosition = monsterSpawns[spawnIndex]->Transform()->GetLocalPos();
			Vector3 spawnPosition = paraentPosition;

			spawnPosition.x += childPosition.x*paraentScale.x;
			spawnPosition.y += childPosition.y*paraentScale.y;

			Instantiate(monsterSpawnEffectPrefab, spawnPosition, prefabInputScripts);
		}


		const wchar_t* subStr = L" ";
		wchar_t spawnName[100];
		wcscpy_s(spawnName, 100, monsterSpawns[spawnIndex]->GetName().c_str());
		wchar_t* remainName;
		const wchar_t* tokStr = wcstok_s(spawnName, subStr, &remainName);
		if (tokStr != nullptr)
		{
			map<UINT, CScript*> prefabInputScripts;

			vector<UINT> prefabScriptTypes = monsterPrefab[tokStr]->GetScriptType();
			vector<wstring> allScriptInfo;
			CScriptMgr::GetScriptInfo(allScriptInfo);

			for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
			{
				UINT scriptType = prefabScriptTypes[scriptIndex];
				wstring scriptName = allScriptInfo[scriptType];
				CScript* prefabScript = CScriptMgr::GetScript(scriptName);
				prefabInputScripts[scriptType] = prefabScript;
			}

			Vector3 paraentPosition = Object()->Transform()->GetLocalPos();
			Vector3 paraentScale = Object()->Transform()->GetLocalScale();
			Vector3 childPosition = monsterSpawns[spawnIndex]->Transform()->GetLocalPos();
			Vector3 spawnPosition = paraentPosition;

			spawnPosition.x += childPosition.x*paraentScale.x;
			spawnPosition.y += childPosition.y*paraentScale.y;

			Instantiate(monsterPrefab[tokStr], spawnPosition, prefabInputScripts);
		}
	}
}

void CMonsterResponseScript::WakeSealObject(void)
{
	for (int layerIndex = 0; layerIndex < MAX_LAYER; layerIndex++)
	{
		CLayer* curLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(layerIndex);
		if (curLayer == nullptr)
		{
			continue;
		}

		vector<CGameObject*> layerParentObject = curLayer->GetParentObject();
		if (layerParentObject.empty() == false)
		{
			for (int objectIndex = 0; objectIndex < layerParentObject.size(); objectIndex++)
			{
				vector<CScript*> objectScripts = layerParentObject[objectIndex]->GetScripts();
				if (objectScripts.empty() == false)
				{
					for (int scriptIndex = 0; scriptIndex < objectScripts.size(); scriptIndex++)
					{
						if (objectScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::Z1MONSTEREXISTFINDSCRIPT)
						{
							objectScripts[scriptIndex]->Object()->Active(true);
							break;
						}
					}
				}
			}
		}
	}
}

void CMonsterResponseScript::start()
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\GiantBat.pref", L"Prefab\\GiantBat.pref");
	monsterPrefab[L"GiantBat"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\GiantBat.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Banshee.pref", L"Prefab\\Banshee.pref");
	monsterPrefab[L"Banshee"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Banshee.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Bat.pref", L"Prefab\\Bat.pref");
	monsterPrefab[L"Bat"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Bat.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Bat_Red.pref", L"Prefab\\Bat_Red.pref");
	monsterPrefab[L"Bat_Red"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Bat_Red.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\BigWhiteSkel.pref", L"Prefab\\BigWhiteSkel.pref");
	monsterPrefab[L"BigWhiteSkel"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\BigWhiteSkel.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\LittleGhost.pref", L"Prefab\\LittleGhost.pref");
	monsterPrefab[L"LittleGhost"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\LittleGhost.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\Minotaurs.pref", L"Prefab\\Minotaurs.pref");
	monsterPrefab[L"Minotaurs"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\Minotaurs.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\RedGiantBat.pref", L"Prefab\\RedGiantBat.pref");
	monsterPrefab[L"RedGiantBat"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\RedGiantBat.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\SkelDog.pref", L"Prefab\\SkelDog.pref");
	monsterPrefab[L"SkelDog"] = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\SkelDog.pref");


	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\SpawnEffect.pref", L"Prefab\\SpawnEffect.pref");
	monsterSpawnEffectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\SpawnEffect.pref");
}

void CMonsterResponseScript::OnCollisionEnter(CCollider2D * _pOther)
{
	if (isSpawn == false)
	{
		isSpawn = true;

		SpawnMonster();
		
		WakeSealObject();
	}
}
