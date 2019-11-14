#include "stdafx.h"
#include "ItemEffect.h"

#include "EffectScript.h"
#include "ItemKind.h"

#include <random>
#include <time.h>

ItemEffect::ItemEffect()
{
}


ItemEffect::~ItemEffect()
{
}

void ItemEffect::Init(CItemScript * item)
{
	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\SwingEffect.pref", L"Prefab\\SwingEffect.pref");
	effectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\SwingEffect.pref");

	CResMgr::GetInst()->Load<CPrefab>(L"Prefab\\SwingHitEffect.pref", L"Prefab\\SwingHitEffect.pref");
	hitEffectPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Prefab\\SwingHitEffect.pref");
}

void ItemEffect::Action(CItemScript * item)
{
	CreateEffectPrefab(item);
}

void ItemEffect::Update(CItemScript * item)
{
	CreateHitEffectPrefab(item);
}

void ItemEffect::CreateEffectPrefab(CItemScript * item)
{
	Vector3 mouseDirection = item->GetItemKind()->GetMouseDirection();
	Vector3 effectDirection = Vector3(0.f, 1.f, 0.f);
	mouseDirection = XMVector2Normalize(mouseDirection);
	Vector3 dotValue = XMVector2Dot(effectDirection, mouseDirection);

	float radian = acosf(dotValue.x);
	if (mouseDirection.x > 0)
	{
		radian = g_XMPi.f[0] * 2 - radian;
	}

	Vector3 effectRotate = Vector3(0.f, 0.f, radian);

	map<UINT, CScript*> prefabInputScripts;

	vector<UINT> prefabScriptTypes = effectPrefab->GetScriptType();
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
			effectScript->SetRotate(effectRotate);
		}

		prefabInputScripts[scriptType] = prefabScript;
	}

	Vector3 playerPosition = item->ParentObject()->GetParent()->Transform()->GetLocalPos();
	Vector3 playerColliderScale = item->ParentObject()->GetParent()->Collider2D()->GetFinalScale();

	Vector3 itemRotateAxisPosition = item->ParentObject()->Transform()->GetLocalPos();
	Vector3 itemRotateAxisScale = item->ParentObject()->Transform()->GetLocalScale();

	Vector3 itemPosition = item->Object()->Transform()->GetLocalPos();

	Vector3 effectPosition = playerPosition;

	effectPosition.x += (itemRotateAxisPosition.x * playerColliderScale.x);
	effectPosition.y += (itemRotateAxisPosition.y * playerColliderScale.y);

	effectPosition.x += (itemPosition.x * itemRotateAxisScale.x);
	effectPosition.y += (itemPosition.y * itemRotateAxisScale.y);

	effectPosition.x += mouseDirection.x*50.f;
	effectPosition.y += mouseDirection.y*50.f;

	item->Instantiate(effectPrefab, effectPosition, prefabInputScripts);
}

void ItemEffect::CreateHitEffectPrefab(CItemScript * item)
{
	if (item->GetIsHit() == true)
	{
		item->SetIsHit(false);

		map<UINT, CScript*> prefabInputScripts;

		vector<UINT> prefabScriptTypes = hitEffectPrefab->GetScriptType();
		vector<wstring> allScriptInfo;
		CScriptMgr::GetScriptInfo(allScriptInfo);

		srand(time(NULL));

		for (int scriptIndex = 0; scriptIndex < prefabScriptTypes.size(); scriptIndex++)
		{
			UINT scriptType = prefabScriptTypes[scriptIndex];
			wstring scriptName = allScriptInfo[scriptType];
			CScript* prefabScript = CScriptMgr::GetScript(scriptName);

			if (prefabScript->GetScriptType() == (UINT)SCRIPT_TYPE::EFFECTSCRIPT)
			{
				CEffectScript* effectScript = dynamic_cast<CEffectScript*>(prefabScript);

				mt19937 engine((unsigned int)time(NULL));
				uniform_real_distribution<float> distribution(0.f, 3.14f);
				auto generator = bind(distribution, engine);

				float randomZRadian = generator();
				Vector3 effectRotate = Vector3(0.f, 0.f, randomZRadian);

				effectScript->SetRotate(effectRotate);
			}
			
			prefabInputScripts[scriptType] = prefabScript;
		}

		Vector3 effectPosition = item->GetHitPosition();
		
	
		int randomXValue = (rand() % 100) - 50;
		int randomYValue = (rand() % 100) - 50;

		effectPosition.x += randomXValue;
		effectPosition.y += randomYValue;

		item->Instantiate(hitEffectPrefab, effectPosition, prefabInputScripts);
	}
}


