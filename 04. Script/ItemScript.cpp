#include "stdafx.h"
#include "ItemScript.h"
#include "ItemComponent.h"
#include "ItemKind.h"
#include "ItemEffect.h"
#include "ItemImage.h"

#include "EventQueueScript.h"

CItemScript::CItemScript():
	CScript((UINT)SCRIPT_TYPE::ITEMSCRIPT)
{
	//임시코드 나중에 각각의 Component가 자신의 타입을 알게한다.
	//그리고 Player에서 item의 Component를 설정해서 넘겨줄 수 있도록 한다.
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		itemComponents[itemComponentIndex] = nullptr;
	}

	itemComponents[(UINT)ITEM_TYPE::KIND] = new ItemKind;
	itemComponents[(UINT)ITEM_TYPE::IMAGE] = new ItemImage;
	itemComponents[(UINT)ITEM_TYPE::EFFECT] = new ItemEffect;

	activeAttack = false;
	activeAttackTime = 0.f;
	isHit = false;
}


CItemScript::~CItemScript()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] != nullptr)
		{
			delete itemComponents[itemComponentIndex];
			itemComponents[itemComponentIndex] = nullptr;
		}
	}
}

void CItemScript::awake()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}

		itemComponents[itemComponentIndex]->Init(this);
	}
}

void CItemScript::start()
{
	m_pCloneMtrl = MeshRender()->GetCloneMaterial();
}

void CItemScript::update()
{
	//임시코드 나중에 플레이어에서 조작할 수 있도록 한다.
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN) == KEY_STATE::STATE_TAB)
	{
		Play();
		activeAttack = true;
	}


	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}

		itemComponents[itemComponentIndex]->Update(this);
	}


	if (activeAttack == true)
	{
		activeAttackTime += DT;
		if (activeAttackTime > 0.2)
		{
			activeAttack = false;
		}
	}
	else
	{
		activeAttackTime = 0.f;
	}
}

void CItemScript::OnCollision(CCollider2D * _pOther)
{
	if (activeAttack == true)
	{
		EVENT_PACKET packet;
		packet.eventSendTargetID = _pOther->Object()->GetID();
		packet.eventType = EVENTQUEUE_TYPE::ATTACK;
		CEventQueueScript::GetInstance()->EnqueueEvent(packet);
		
		hitPosition = _pOther->Object()->Transform()->GetLocalPos();

		activeAttack = false;
		isHit = true;
	}
}

void CItemScript::Play()
{
	for (UINT itemComponentIndex = 0; itemComponentIndex < (UINT)ITEM_TYPE::END; itemComponentIndex++)
	{
		if (itemComponents[itemComponentIndex] == nullptr)
		{
			continue;
		}
		itemComponents[itemComponentIndex]->Action(this);
	}
}

ItemKind * CItemScript::GetItemKind(void)
{
	ItemKind* itemKind = dynamic_cast<ItemKind*>(itemComponents[(UINT)ITEM_TYPE::KIND]);
	return itemKind;
}
