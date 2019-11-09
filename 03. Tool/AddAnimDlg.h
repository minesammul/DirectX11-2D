#pragma once


class CGameObject;

class CAddAnimDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddAnimDlg)

private:
	CGameObject*		m_pTarget;

public:
	void SetTargetObject(CGameObject* _pObj) { m_pTarget = _pObj; }


public:
	CAddAnimDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddAnimDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDANIMDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editAnimKey;
	CEdit m_editTerm;
	CEdit m_editFolderPath;
	afx_msg void OnBtnSelectFolder();	
	virtual void OnOK();
	CListCtrl m_ctrlAnimList;

	virtual BOOL OnInitDialog();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult);
};
