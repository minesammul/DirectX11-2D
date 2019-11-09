#pragma once


// AddLayerDlg 대화 상자

class AddLayerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddLayerDlg)

public:
	AddLayerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddLayerDlg();

public:
	virtual BOOL OnInitDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDLAYERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox listboxExistLayer;
	CEdit editAddLayerName;
	afx_msg void OnBnClickedOkAddLayer();
};
