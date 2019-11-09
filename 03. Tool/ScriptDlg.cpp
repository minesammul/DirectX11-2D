// ScriptDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ScriptDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <ScriptMgr.h>
#include <Script.h>


// CScriptDlg 대화 상자

IMPLEMENT_DYNAMIC(CScriptDlg, CDialogEx)



CScriptDlg::CScriptDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_SCRIPTDLG, pParent)
{

}

CScriptDlg::~CScriptDlg()
{
}

void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlScript);
	DDX_Control(pDX, IDC_COMBO1, m_cbScript);
}

void CScriptDlg::init(CGameObject * _pTarget)
{
	vector<wstring> vecName;
	CScriptMgr::GetScriptInfo(vecName);

	SetTarget(_pTarget);

	m_cbScript.ResetContent();
	m_ctrlScript.DeleteAllItems();

	for (UINT i = 0; i < vecName.size(); ++i)
	{
		m_cbScript.AddString(vecName[i].c_str());
	}	

	isFocus = false;
}

void CScriptDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	if (isFocus == true)
	{
		return;
	}

	m_ctrlScript.DeleteAllItems();

	const vector<CScript*>& vecScript = _pTarget->GetScripts();

	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		CString strName = CScriptMgr::GetScriptName(vecScript[i]);
		m_ctrlScript.InsertItem(i, strName);
	}
}




BEGIN_MESSAGE_MAP(CScriptDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CScriptDlg::OnBtnAddScript)
	ON_BN_CLICKED(IDC_BUTTON3, &CScriptDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST1, &CScriptDlg::OnNMSetfocusList1)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST1, &CScriptDlg::OnNMKillfocusList1)
END_MESSAGE_MAP()


// CScriptDlg 메시지 처리기


void CScriptDlg::OnBtnAddScript()
{
	CString strScriptName;
	int iSel = m_cbScript.GetCurSel();
	m_cbScript.GetLBText(iSel, strScriptName);

	CScript* pNewScript = CScriptMgr::GetScript(strScriptName.GetBuffer());
	CGameObject* targetObject = GetTarget();
	targetObject->AddComponent(pNewScript);
}

void CScriptDlg::OnBnClickedButtonDelete()
{
	if (deleteIndex != -1)
	{
		GetTarget()->GetScripts().clear();

		m_ctrlScript.DeleteItem(deleteIndex);

		for (int index = 0; index < m_ctrlScript.GetItemCount(); index++)
		{
			CString formatStr = m_ctrlScript.GetItemText(index, 0);
			CScript* pNewScript = CScriptMgr::GetScript(formatStr.GetBuffer());
			GetTarget()->AddComponent(pNewScript);
		}

	}
}


void CScriptDlg::OnNMSetfocusList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	isFocus = true;
}


void CScriptDlg::OnNMKillfocusList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	deleteIndex = m_ctrlScript.GetSelectionMark();
	isFocus = false;
}
