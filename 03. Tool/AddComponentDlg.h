#pragma once


// AddComponentDlg 대화 상자
class CGameObject;

class AddComponentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddComponentDlg)
private:
	CGameObject* targetObject;


public:
	AddComponentDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddComponentDlg();

public:
	virtual void OnOK();
	virtual void OnCancel();

	void SetGameObject(CGameObject* gameObject);
	void Renew();
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDCOMPONENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox comboAddComponent;
	afx_msg void OnBnClickedButtonAddComponent();

	virtual void PostNcDestroy();
};
