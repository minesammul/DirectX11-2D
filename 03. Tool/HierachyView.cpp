// HierachyView.cpp: 구현 파일
//

#include "stdafx.h"
#include "HierachyView.h"

#include "GameObjectDlg.h"
#include "ResourceDlg.h"

IMPLEMENT_DYNCREATE(CHierachyView, CView)



CHierachyView::CHierachyView()
{

}

CHierachyView::~CHierachyView()
{
}

void CHierachyView::init()
{
	m_pResourceDlg->init();
}

void CHierachyView::init_object()
{
	m_pGameObjectDlg->init();
}



BEGIN_MESSAGE_MAP(CHierachyView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CHierachyView 그리기

void CHierachyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CHierachyView 진단

#ifdef _DEBUG
void CHierachyView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHierachyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG




// CHierachyView 메시지 처리기

int CHierachyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	UINT iHeight = 0;

	CRect rt;
	GetClientRect(rt);

	CRect rtDlg;
	
	m_pGameObjectDlg = new CGameObjectDlg;
	m_pGameObjectDlg->Create(IDD_GAMEOBJECTDLG, this);
	//m_pGameObjectDlg->SetWindowPos(nullptr, 1, 0, rt.Width() - 1, rtDlg.Height(), 0);
	m_pGameObjectDlg->SetWindowPos(nullptr, 1, 0, rt.Width() - 1, rt.Height()/2, 0);
	m_pGameObjectDlg->GetWindowRect(rtDlg);
	m_pGameObjectDlg->ShowWindow(true);

	iHeight += rtDlg.Height();

	m_pResourceDlg = new ResourceDlg;
	m_pResourceDlg->Create(IDD_RESOURCEDLG, this);
	m_pResourceDlg->ShowWindow(true);
	m_pResourceDlg->GetWindowRect(rtDlg);
	m_pResourceDlg->SetWindowPos(nullptr, 1, iHeight, rt.Width() - 1, rt.Height() - iHeight, 0);
	//m_pResourceDlg->SetWindowPos(nullptr, 1, iHeight, rt.Width() - 1, 1000, 0);

	return 0;
}
