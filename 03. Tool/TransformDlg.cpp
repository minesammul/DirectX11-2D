﻿// TransformDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TransformDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"

#include <GameObject.h>
#include <Transform.h>

#include <EventMgr.h>

#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>


#include <func.h>


#include "resource.h"
// CTransformDlg 대화 상자

IMPLEMENT_DYNAMIC(CTransformDlg, CDialogEx)
CTransformDlg::CTransformDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_TRANSFORMDLG, pParent)
	
	, m_bActive(FALSE)
{
}

CTransformDlg::~CTransformDlg()
{
}

void CTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	for (UINT i = 0; i < 9; ++i)
	{
		DDX_Control(pDX, 2001 + i, m_edit[i]);
	}
	DDX_Check(pDX, IDC_CHECK1, m_bActive);
	DDX_Control(pDX, IDC_COMBO1, m_cbLayer);
}

BEGIN_MESSAGE_MAP(CTransformDlg, CDialogEx)

	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_EDIT1, IDC_EDIT9, &CComponentDlg::OnEnSetfocusEdit)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_EDIT1, IDC_EDIT9, &CComponentDlg::OnEnKillfocusEdit)
	
	ON_CONTROL_RANGE(CBN_SETFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbSetfocusEdit)
	ON_CONTROL_RANGE(CBN_KILLFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbKillfocusEdit)

	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT1, IDC_EDIT9, &CTransformDlg::OnEnChangeEdit)
	
	ON_BN_CLICKED(IDC_CHECK1, &CTransformDlg::OnBtnActive)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTransformDlg::OnCbnSelChange)
END_MESSAGE_MAP()

void CTransformDlg::init(CGameObject * _pTarget)
{
	// 현재 레이어 목록 추가
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_cbLayer.ResetContent();

	for (UINT i = 0 , j = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurScene->GetLayer(i);
		if (nullptr == pLayer)
			continue;

		m_cbLayer.InsertString(j, pLayer->GetName().c_str());
		m_cbLayer.SetItemData(j, i);

		++j;
	}	
}

void CTransformDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);
	
	if (IsEditActive() || IsCbActive())
		return;

	CString str;
	CTransform* pTrans = GetTarget()->Transform();
	Vector3 vRot = pTrans->GetLocalRot();	
	
	vRot.x = GetAngle(vRot.x);
	vRot.y = GetAngle(vRot.y);
	vRot.z = GetAngle(vRot.z);

	Vector3 arrData[3] = { pTrans->GetLocalPos() , pTrans->GetLocalScale() , vRot };

	for (UINT i = 0; i < 9; ++i)
	{
		if (i % 3 == 0)
		{
			str.Format(L"%f", arrData[i / 3].x);
		}
		else if (i % 3 == 1)
		{
			str.Format(L"%f", arrData[i / 3].y);
		}
		else if (i % 3 == 2)
		{
			str.Format(L"%f", arrData[i / 3].z);
		}

		m_edit[i].SetWindowTextW(str);
	}

	// Layer 확인
	CGameObject* curTarget = GetTarget();
	CLayer* pLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(GetTarget()->GetLayerIdx());
	//int iSel = m_cbLayer.FindString(0, pLayer->GetName().c_str());
	int iSel = GetTarget()->GetLayerIdx();
	if (iSel == -1)
	{
		int layerCount = m_cbLayer.GetCount();
		m_cbLayer.InsertString(layerCount, pLayer->GetName().c_str());
		iSel = layerCount;
	}
	m_cbLayer.SetCurSel(iSel);

	m_bActive = GetTarget()->IsActive();
	UpdateData(false);
}

void CTransformDlg::OnEnChangeEdit(UINT _id)
{
	// 직접 변경할 경우에만 오브젝트에 적용됨
	// 평소 오브젝트의 값을 가져오는 상황(EnChange) 으로 인해서 다시 오브젝트가 변경되는일을 막는다.
	if (!IsEditActive())
		return;

	CTransform* pTrans = GetTarget()->Transform();

	CString str;

	Vector3 arrData[3] = {};

	for (UINT i = 0; i < 9; ++i)
	{
		m_edit[i].GetWindowTextW(str);

		float fData = _wtof(str);

		if (i % 3 == 0)
		{
			arrData[i / 3].x = fData;
		}
		else if (i % 3 == 1)
		{
			arrData[i / 3].y = fData;
		}
		else if (i % 3 == 2)
		{
			arrData[i / 3].z = fData;
		}
	}

	pTrans->SetLocalPos(arrData[0]);
	pTrans->SetLocalScale(arrData[1]);

	arrData[2].x = GetRadian(arrData[2].x);
	arrData[2].y = GetRadian(arrData[2].y);
	arrData[2].z = GetRadian(arrData[2].z);

	pTrans->SetLocalRot(arrData[2]);
}


void CTransformDlg::OnBtnActive()
{
	UpdateData(true);
	GetTarget()->Active(m_bActive);
}

void CTransformDlg::OnCbnSelChange()
{
	// Layer 변경
	int iSel = m_cbLayer.GetCurSel();
	DWORD_PTR iLayerIdx = m_cbLayer.GetItemData(iSel);

	CGameObject* selObject = GetTarget();

	int iCurIdx = GetTarget()->GetLayerIdx();

	// 변경 사항이 없다.
	if (iCurIdx == iLayerIdx)
		return;

	// 자식까지 전부 이동할 것인지 확인
	bool bMoveAll = true;
	if (!GetTarget()->GetChild().empty())
	{
		int id = MessageBox(L"자식 오브젝트도 Layer 를 변경하시겠습니까?", L"Layer 변경 확인", MB_OKCANCEL);
		if (id == IDCANCEL)
			bMoveAll = false;
	}

	tEvent event = {};	
	event.eType = EVENT_TYPE::CHANGE_LAYER;
	event.lParam = (DWORD_PTR)GetTarget();	
	event.wParam = (DWORD_PTR)MAKELONG(bMoveAll, iLayerIdx);
	
	CEventMgr::GetInst()->AddEvent(event);
}
