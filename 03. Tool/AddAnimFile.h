#pragma once


// AddAnimFile 대화 상자
class CGameObject;
class AddAnimFile : public CDialogEx
{
	DECLARE_DYNAMIC(AddAnimFile)
private:
	CGameObject*		m_pTarget;
public:
	void SetTargetObject(CGameObject* _pObj) { m_pTarget = _pObj; }

public:
	AddAnimFile(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddAnimFile();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDANIMFILEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();
	CListCtrl m_ctrlAnimList;
	CEdit m_editAnimKey;
	CEdit m_editTerm;
	CEdit m_editFolderPath;
	CEdit frameCount;
	afx_msg void OnBnClickedFilePathButton();
};
