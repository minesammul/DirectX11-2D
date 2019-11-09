#pragma once


// CollisionLayer 대화 상자

class CollisionLayer : public CDialogEx
{
	DECLARE_DYNAMIC(CollisionLayer)
private:
	CString clickedCollisionLayerName;

public:
	CollisionLayer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CollisionLayer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLISIONLAYERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl collisionLayerList;
	CListCtrl checkCollisionLayerList;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
