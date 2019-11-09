#pragma once


#include "ComponentDlg.h"

class CAnimator2DDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CAnimator2DDlg)
private:
	bool isFocus;


public:

	virtual void init(CGameObject* _pTarget);
	virtual void update(CGameObject* _pTarget);

	void Animator2DStateCheck(CGameObject* _pTarget);




public:
	CAnimator2DDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimator2DDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATOR2DDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox	m_cbAnimList;
	CButton		m_btnPlay;
	BOOL		m_bRepeat;

	afx_msg void OnBtnPlay();
	afx_msg void OnBtnRepeat();
	afx_msg void OnCbAnimChange();
	afx_msg void OnAddAnimation();
	afx_msg void OnBnClickedAddAnimaiotnFileButton();
	afx_msg void OnEnChangeEdit1();
	CEdit editMaxFrameCount;
	CEdit editNowFrameCount;
	CEdit editOffsetX;
	CEdit editOffsetY;
	afx_msg void OnEnSetfocusEditOffsetX();
	afx_msg void OnEnKillfocusEditOffsetX();
	afx_msg void OnEnSetfocusEditOffsetY();
	afx_msg void OnEnKillfocusEditOffsetY();
	afx_msg void OnBnClickedButtonNextFrame();
	afx_msg void OnBnClickedButtonPrevFrame();
	CEdit editRepeatStartFrame;
	afx_msg void OnEnSetfocusEditRepeatStartFrame();
	afx_msg void OnEnKillfocusEditRepeatStartFrame();
	CEdit editRepeatEndFrame;
	afx_msg void OnEnSetfocusEditRepeatEndFrame();
	afx_msg void OnEnKillfocusEditRepeatEndFrame();
};
