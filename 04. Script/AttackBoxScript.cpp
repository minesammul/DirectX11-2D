#include "stdafx.h"
#include "AttackBoxScript.h"

#include "EventQueueScript.h"


CAttackBoxScript::CAttackBoxScript() : 
	CScript((UINT)SCRIPT_TYPE::ATTACKBOXSCRIPT)
{
	isAttack = false;
}


CAttackBoxScript::~CAttackBoxScript()
{
}

void CAttackBoxScript::OnCollision(CCollider2D* _pOther)
{
	if (isAttack == true)
	{
		if (_pOther->Object()->GetName().compare(L"Player") == 0)
		{
			EVENT_PACKET packet;
			packet.eventType = EVENTQUEUE_TYPE::HITED;
			packet.eventSendTargetID = _pOther->Object()->GetID();
			CEventQueueScript::GetInstance()->EnqueueEvent(packet);
		}
		isAttack = false;
	}
}
