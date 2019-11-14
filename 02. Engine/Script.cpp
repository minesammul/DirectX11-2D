#include "stdafx.h"
#include "Script.h"

#include "EventMgr.h"

CScript::CScript(UINT _iType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_iType)
{
}

CScript::~CScript()
{
}

void CScript::InsertScriptToPrefab(CGameObject * prefabObject, map<UINT, CScript*> scripts)
{
	for (int prefabChildIndex = 0; prefabChildIndex < prefabObject->GetChild().size(); prefabChildIndex++)
	{
		InsertScriptToPrefab(prefabObject->GetChild()[prefabChildIndex], scripts);
	}

	prefabObject->SetLayerIdx(0);
	for (int scriptIndex = 0; scriptIndex < prefabObject->GetScripts().size(); scriptIndex++)
	{
		UINT scriptType = prefabObject->GetScripts()[scriptIndex]->GetScriptType();

		delete prefabObject->GetScripts()[scriptIndex];
		prefabObject->GetScripts()[scriptIndex] = nullptr;

		prefabObject->GetScripts()[scriptIndex] = scripts[scriptType];
		prefabObject->GetScripts()[scriptIndex]->SetGameObject(prefabObject);
	}
}

void CScript::InsertLayerToPrefab(CGameObject * prefabObject, CGameObject * referenceObject)
{
	for (int prefabChildIndex = 0; prefabChildIndex < prefabObject->GetChild().size(); prefabChildIndex++)
	{
		InsertLayerToPrefab(prefabObject->GetChild()[prefabChildIndex], referenceObject->GetChild()[prefabChildIndex]);
	}

	prefabObject->SetLayerIdx(0);


	tEvent event = {};
	event.eType = EVENT_TYPE::CHANGE_LAYER;
	event.lParam = (DWORD_PTR)prefabObject;
	event.wParam = (DWORD_PTR)MAKELONG(false, referenceObject->GetLayerIdx());


	CEventMgr::GetInst()->AddEvent(event);
}

void CScript::Instantiate(CResPtr<CPrefab>& _pPrefab, const Vector3 & _vPos, const wstring & _strLayerName)
{	
	CGameObject* pClone = _pPrefab->Instantiate();
	pClone->Transform()->SetLocalPos(_vPos);

	int layerIndex = CSceneMgr::GetInst()->GetCurScene()->FindLayer(_strLayerName)->GetLayerIdx();
	pClone->SetLayerIdx(layerIndex);

	CreateObject(pClone);	
}

void CScript::Instantiate(CResPtr<CPrefab>& _pPrefab, const Vector3 & _vPos, map<UINT, CScript*> scripts)
{
	CGameObject* pClone = _pPrefab->Instantiate();
	pClone->Transform()->SetLocalPos(_vPos);
	
	wstring cloneName = pClone->GetName();
	//cloneName += L"Prefab";
	pClone->SetName(cloneName);

	InsertScriptToPrefab(pClone, scripts);


	CreateObject(pClone);


	InsertLayerToPrefab(pClone, _pPrefab->GetPrefabObjectOriginal());

	pClone->start();
}


// ===========
// Event Ã³¸®
// ===========
void CScript::AddChild(CGameObject * _pChildObject)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::ADD_CHILD;
	e.lParam = (INT_PTR)Object();
	e.wParam = (INT_PTR)_pChildObject;

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::ClearChild(UINT _iChildIdx)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CLEAR_CHILD;
	e.lParam = (INT_PTR)Object();
	e.wParam = (INT_PTR)_iChildIdx;

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::ClearParent()
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CLEAR_PARANT;
	e.lParam = (INT_PTR)Object();	

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::CreateObject(CGameObject * _pTarget)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::CREATE_OBJECT;

	e.lParam = (INT_PTR)_pTarget;
	e.wParam = (INT_PTR)_pTarget->GetLayerIdx();

	CEventMgr::GetInst()->AddEvent(e);
}

void CScript::DeleteObject(CGameObject * _pTarget)
{
	tEvent e = {};

	e.eType = EVENT_TYPE::DELETE_OBJECT;

	e.lParam = (INT_PTR)_pTarget;	

	CEventMgr::GetInst()->AddEvent(e);
}
