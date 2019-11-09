#pragma once


// ResourceDlg 대화 상자

class ResourceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ResourceDlg)
private:
	bool	m_bInit;

public:
	ResourceDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResourceDlg();

public:
	void init();
	void Renew();

private:
	void LoadResource(CString _strFolderPath);

	// TreeControl
	HTREEITEM AddItem(CString _str, HTREEITEM _hParent, DWORD_PTR _dwData, HTREEITEM _hSortop);
	void MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem);
	void GetChildItem(HTREEITEM _hItem, vector<HTREEITEM>& _vecChild);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESOURCEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnSize(UINT nType, int cx, int cy);

	CTreeCtrl m_ctrlTree;
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
