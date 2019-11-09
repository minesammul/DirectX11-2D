// CameraDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CameraDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <Camera.h>
#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>

// CCameraDlg 대화 상자

IMPLEMENT_DYNAMIC(CCameraDlg, CDialogEx)

CCameraDlg::CCameraDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_CAMERADLG, pParent)
{
}

CCameraDlg::~CCameraDlg()
{
}

void CCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbProj);
	DDX_Control(pDX, IDC_EDIT1, m_editFar);
	DDX_Control(pDX, IDC_EDIT2, m_editScale);
	DDX_Control(pDX, IDC_EDIT3, m_editFOV);
	DDX_Control(pDX, IDC_LIST1, listCtrlCameraViewLayer);
}

void CCameraDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);
	
	CCamera* pCam = GetTarget()->Camera();
	
	if (IsEditActive() || IsCbActive())
		return;
	
	// 직교, 원근
	PROJ_TYPE ePType = pCam->GetProjType();

	if (PROJ_TYPE::ORTHOGRAPHIC == ePType)
	{
		if (m_cbProj.GetCurSel() != 0)
		{
			m_cbProj.SetCurSel(0);			
			m_cbProj.GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(m_cbProj.GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)m_cbProj.GetSafeHwnd());			
		}
	}	
	else
	{
		if (m_cbProj.GetCurSel() == 0)
		{
			m_cbProj.SetCurSel(1);
			m_cbProj.GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(m_cbProj.GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)m_cbProj.GetSafeHwnd());
		}		
	}
	

	CString str;
	float fData = 0.f;

	// Far
	fData = pCam->GetFar();
	str.Format(L"%f", fData);
	m_editFar.SetWindowTextW(str);

	// scale(직교)
	fData = pCam->GetScale();
	str.Format(L"%f", fData);
	m_editScale.SetWindowTextW(str);
	
	// FOV(원근)
	fData = pCam->GetFOV();
	fData = (fData / XM_PI) * 180.f;

	str.Format(L"%f", fData);
	m_editFOV.SetWindowTextW(str);

	listCtrlCameraViewLayer.DeleteAllItems();

	int listInputIndex = 0;
	for (int layerIndex = 0; layerIndex < MAX_LAYER; layerIndex++)
	{
		CLayer* curLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(layerIndex);
		if (curLayer == nullptr)
		{
			continue;
		}
		
		listCtrlCameraViewLayer.InsertItem(listInputIndex, curLayer->GetName().c_str());
		
		bool cameraView = false;
		cameraView = pCam->IsValiedLayer(layerIndex);

		listCtrlCameraViewLayer.SetCheck(listInputIndex, cameraView);

		listInputIndex++;
	}

}


BEGIN_MESSAGE_MAP(CCameraDlg, CDialogEx)

	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_EDIT1, IDC_EDIT3, &CComponentDlg::OnEnSetfocusEdit)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_EDIT1, IDC_EDIT3, &CComponentDlg::OnEnKillfocusEdit)

	ON_CONTROL_RANGE(CBN_SETFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbSetfocusEdit)
	ON_CONTROL_RANGE(CBN_KILLFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbKillfocusEdit)

	ON_EN_CHANGE(IDC_EDIT1, &CCameraDlg::OnEnChangeFar)
	ON_EN_CHANGE(IDC_EDIT2, &CCameraDlg::OnEnChangeScale)
	ON_EN_CHANGE(IDC_EDIT3, &CCameraDlg::OnEnChangeFOV)

	ON_CBN_SELCHANGE(IDC_COMBO1, &CCameraDlg::OnCbnSelchangeCombo)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCameraDlg::OnNMClickListViewLayerCheck)
END_MESSAGE_MAP()

BOOL CCameraDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();
	
	m_cbProj.AddString(L"Orthographic");
	m_cbProj.AddString(L"Perspective");		

	listCtrlCameraViewLayer.SetExtendedStyle(LVS_EX_CHECKBOXES);
	//listCtrlCameraViewLayer.InsertColumn(0, L"non Head");
	return TRUE;
}


void CCameraDlg::OnEnChangeFar()
{
	CString str;
	m_editFar.GetWindowTextW(str);
	float fFar = _wtof(str);
	GetTarget()->Camera()->SetFar(fFar);
}


void CCameraDlg::OnEnChangeScale()
{
	CString str;
	m_editScale.GetWindowTextW(str);
	float fScale = _wtof(str);
	GetTarget()->Camera()->SetScale(fScale);
}


void CCameraDlg::OnEnChangeFOV()
{
	CString str;
	m_editFOV.GetWindowTextW(str);
	float fFOV = _wtof(str);
	fFOV = (fFOV / 180.f) * XM_PI;
	GetTarget()->Camera()->SetFOV(fFOV);
}

void CCameraDlg::OnCbnSelchangeCombo()
{
	int iIdx = m_cbProj.GetCurSel();

	if (0 == iIdx)
	{
		GetTarget()->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		m_editFOV.EnableWindow(false);
		m_editScale.EnableWindow(true);
	}		
	else
	{
		GetTarget()->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		m_editFOV.EnableWindow(true);
		m_editScale.EnableWindow(false);
	}

	OnOK();
}


void CCameraDlg::OnNMClickListViewLayerCheck(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMItemActivate->iItem == -1)
	{
		return;
	}

	CCamera* camera = GetTarget()->Camera();
	CString checkViewLayerName = listCtrlCameraViewLayer.GetItemText(pNMItemActivate->iItem, 0);
	
	CLayer* selectLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(checkViewLayerName.GetBuffer());
	int selectLayerIndex = selectLayer->GetLayerIdx();
	camera->CheckLayer(selectLayerIndex);

	if (listCtrlCameraViewLayer.GetCheck(pNMItemActivate->iItem) == true)
	{
		listCtrlCameraViewLayer.SetCheck(pNMItemActivate->iItem, false);
	}
	else
	{
		listCtrlCameraViewLayer.SetCheck(pNMItemActivate->iItem, true);
	}

	*pResult = 0;
}
