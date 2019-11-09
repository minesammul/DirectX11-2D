#pragma once


// CScriptDlg 대화 상자
#include "ComponentDlg.h"

class CScriptDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CScriptDlg)
private:
	bool isFocus;
	int deleteIndex;

public:
	virtual void init(CGameObject* _pTarget);
	virtual void update(CGameObject* _pTarget);

public:
	CScriptDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CScriptDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCRIPTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlScript;
	CComboBox m_cbScript;
	afx_msg void OnBtnAddScript();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMSetfocusList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusList1(NMHDR *pNMHDR, LRESULT *pResult);
};
