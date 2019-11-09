#include "stdafx.h"
#include "EventQueueScript.h"

#include "MonsterScript.h"
#include "UIScript.h"
#include "PlayerScript.h"


CEventQueueScript::CEventQueueScript() : 
	CScript((UINT)SCRIPT_TYPE::EVENTQUEUESCRIPT)
{
}


CEventQueueScript::~CEventQueueScript()
{

}

void CEventQueueScript::start()
{
}

void CEventQueueScript::update()
{
	eventQueue = CEventQueueScript::GetInstance()->GetEventQueue();
	if (eventQueue.empty() == false)
	{
		if (eventQueue.front().eventType == EVENTQUEUE_TYPE::ATTACK)
		{
			vector<CGameObject*> curSceneObject;
			CLayer* targetLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Enemy");
			curSceneObject = targetLayer->GetParentObject();

			vector<CScript*> targetScripts;
			for (int index = 0; index < curSceneObject.size(); index++)
			{
				if (curSceneObject[index]->GetID() == eventQueue.front().eventSendTargetID)
				{
					targetScripts = curSceneObject[index]->GetScripts();
					break;
				}
			}

			CScript* findScript = nullptr;
			for (int index = 0; index < targetScripts.size(); index++)
			{
				if (targetScripts[index]->GetScriptType() == (UINT)SCRIPT_TYPE::MONSTERSCRIPT)
				{
					findScript = targetScripts[index];
					break;
				}
			}

			CMonsterScript* monsterScript = dynamic_cast<CMonsterScript*>(findScript);
			int nowMonsterHp = monsterScript->GetHp();
			nowMonsterHp -= 1;
			monsterScript->SetHp(nowMonsterHp);

			eventQueue.pop();

			CEventQueueScript::GetInstance()->SetEventQueue(eventQueue);
		}
		else if (eventQueue.front().eventType == EVENTQUEUE_TYPE::PLAYER_DATA)
		{
			vector<CGameObject*> curSceneObject;
			CLayer* targetLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"UI");
			curSceneObject = targetLayer->GetParentObject();

			vector<CScript*> targetScripts;
			for (int index = 0; index < curSceneObject.size(); index++)
			{
				if (curSceneObject[index]->GetID() == eventQueue.front().eventSendTargetID)
				{
					targetScripts = curSceneObject[index]->GetScripts();
					break;
				}
			}

			CScript* findScript = nullptr;
			for (int index = 0; index < targetScripts.size(); index++)
			{
				if (targetScripts[index]->GetScriptType() == (UINT)SCRIPT_TYPE::UISCRIPT)
				{
					findScript = targetScripts[index];
					break;
				}
			}

			CUIScript* uiScript = dynamic_cast<CUIScript*>(findScript);
			uiScript->SetHp(eventQueue.front().value[0], eventQueue.front().value[1]);

			eventQueue.pop();

			CEventQueueScript::GetInstance()->SetEventQueue(eventQueue);
		}
		else if (eventQueue.front().eventType == EVENTQUEUE_TYPE::HITED)
		{
			vector<CGameObject*> curSceneObject;
			CLayer* targetLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Player");
			curSceneObject = targetLayer->GetParentObject();

			vector<CScript*> targetScripts;
			for (int index = 0; index < curSceneObject.size(); index++)
			{
				if (curSceneObject[index]->GetID() == eventQueue.front().eventSendTargetID)
				{
					targetScripts = curSceneObject[index]->GetScripts();
					break;
				}
			}

			CScript* findScript = nullptr;
			for (int index = 0; index < targetScripts.size(); index++)
			{
				if (targetScripts[index]->GetScriptType() == (UINT)SCRIPT_TYPE::PLAYERSCRIPT)
				{
					findScript = targetScripts[index];
					break;
				}
			}

			CPlayerScript* playerScript = dynamic_cast<CPlayerScript*>(findScript);
			playerScript->PlayerHited();

			eventQueue.pop();

			CEventQueueScript::GetInstance()->SetEventQueue(eventQueue);
		}
	}
}
