#pragma once
#include "ComponentDlg.h"

// Collider2DDlg 대화 상자

class CGameObject;
class Collider2DDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(Collider2DDlg)
private:
	bool focus;


public:
	Collider2DDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Collider2DDlg();

private:
	void UpdatePosition(CGameObject* target);
	void UpdateScale(CGameObject* target);
	void UpdateRotation(CGameObject* target);

public:
	virtual void init(CGameObject* _pTarget);
	virtual void update(CGameObject* _pTarget);
	virtual void OnOK();
	virtual void OnCancel();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLIDER2DDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editPositionX;
	CEdit editPositionY;
	CEdit editPositionZ;
	CEdit editScaleX;
	CEdit editScaleY;
	CEdit editScaleZ;
	CEdit editRotationX;
	CEdit editRotationY;
	CEdit editRotationZ;
	afx_msg void OnEnSetfocusEditPositionX();
	afx_msg void OnEnKillfocusEditPositionX();
	afx_msg void OnEnSetfocusEditPositionY();
	afx_msg void OnEnKillfocusEditPositionY();
	afx_msg void OnEnSetfocusEditPositionZ();
	afx_msg void OnEnKillfocusEditPositionZ();
	afx_msg void OnEnSetfocusEditScaleX();
	afx_msg void OnEnKillfocusEditScaleX();
	afx_msg void OnEnSetfocusEditScaleY();
	afx_msg void OnEnKillfocusEditScaleY();
	afx_msg void OnEnSetfocusEditScaleZ();
	afx_msg void OnEnKillfocusEditScaleZ();
};
