// GameView.cpp: 구현 파일
//

#include "stdafx.h"
#include "GameView.h"
#include "MainFrm.h"
#include "ComponentView.h"
#include <SceneMgr.h>

// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

CGameView::CGameView()
{

}

CGameView::~CGameView()
{
}

BEGIN_MESSAGE_MAP(CGameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGameView 그리기

void CGameView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CGameView 진단

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGameView 메시지 처리기


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	POINT mousePoint;
	mousePoint.x = point.x;
	mousePoint.y = point.y;

	CComponentView* pComView = (CComponentView*)((CMainFrame*)AfxGetMainWnd())->GetComView();

	pComView->SetTarget(CSceneMgr::GetInst()->MousePicking(mousePoint));

	CView::OnLButtonDown(nFlags, point);
}
