#pragma once
#include "ResInfoDlg.h"

// CMaterialDlg 대화 상자

class CMaterialDlg : public CResInfoDlg
{
	DECLARE_DYNAMIC(CMaterialDlg)

public:
	CMaterialDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaterialDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MTRLDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetResource(CResource* _pRes);
	BOOL OnInitDialog();

public:
	CEdit m_editShaderName;
	afx_msg void OnSelShader();
	CListBox listShaderParameterType;
	CListCtrl listctrlShaderParameterValue;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl listctrlShaderTextureParameter;
	CEdit editShaderTextureValue;
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonShaderTextureChange();
};
