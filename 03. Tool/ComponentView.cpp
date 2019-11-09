// ComponentView.cpp: 구현 파일
//

#include "stdafx.h"
#include "ComponentView.h"

#include <SceneMgr.h>
#include <GameObject.h>

#include "resource.h"
#include "TransformDlg.h"
#include "MeshRenderDlg.h"
#include "CameraDlg.h"
#include "Animator2DDlg.h"
#include "ScriptDlg.h"
#include "MaterialDlg.h"
#include "AddComponentDlg.h"
#include "Collider2DDlg.h"

#include <TimeMgr.h>
#include <Resource.h>

// CComponentView

IMPLEMENT_DYNCREATE(CComponentView, CView)

CComponentView::CComponentView()
	: m_pTarget(nullptr)
	, m_arrComDlg{}
{
}

CComponentView::~CComponentView()
{
}

int CComponentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Component Dialog 생성
	m_arrComDlg[(UINT)DLG_TYPE::TRANSFORM] = new CTransformDlg;
	m_arrComDlg[(UINT)DLG_TYPE::TRANSFORM]->Create(IDD_TRANSFORMDLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::TRANSFORM]->ShowWindow(false);

	m_arrComDlg[(UINT)DLG_TYPE::MESHRENDER] = new CMeshRenderDlg;
	m_arrComDlg[(UINT)DLG_TYPE::MESHRENDER]->Create(IDD_MESHRENDERDLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::MESHRENDER]->ShowWindow(false);

	m_arrComDlg[(UINT)DLG_TYPE::CAMERA] = new CCameraDlg;
	m_arrComDlg[(UINT)DLG_TYPE::CAMERA]->Create(IDD_CAMERADLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::CAMERA]->ShowWindow(false);

	m_arrComDlg[(UINT)DLG_TYPE::COLLIDER2D] = new Collider2DDlg;
	m_arrComDlg[(UINT)DLG_TYPE::COLLIDER2D]->Create(IDD_COLLIDER2DDLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::COLLIDER2D]->ShowWindow(false);

	m_arrComDlg[(UINT)DLG_TYPE::ANIMATOR2D] = new CAnimator2DDlg;
	m_arrComDlg[(UINT)DLG_TYPE::ANIMATOR2D]->Create(IDD_ANIMATOR2DDLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::ANIMATOR2D]->ShowWindow(false);

	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT] = new CScriptDlg;
	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT]->Create(IDD_SCRIPTDLG, this);
	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT]->ShowWindow(false);

	m_arrResInfoDlg[(UINT)RES_TYPE::MATERIAL] = new CMaterialDlg;
	m_arrResInfoDlg[(UINT)RES_TYPE::MATERIAL]->Create(IDD_MTRLDLG, this);
	m_arrResInfoDlg[(UINT)RES_TYPE::MATERIAL]->ShowWindow(false);

	addComponentDlg = new AddComponentDlg;
	addComponentDlg->Create(IDD_ADDCOMPONENT, this);
	addComponentDlg->ShowWindow(false);
	return 0;
}

BEGIN_MESSAGE_MAP(CComponentView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CComponentView 그리기

void CComponentView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}

// CComponentView 진단

#ifdef _DEBUG
void CComponentView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CComponentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CComponentView 메시지 처리기

void CComponentView::init()
{
	if (nullptr == m_pTarget)
		return;

	// 타겟 오브젝트 찾기
	vector<CGameObject*> vecOut;
	CSceneMgr::GetInst()->FindGameObject(m_pTarget->GetName(), vecOut);

	if (!vecOut.empty())
	{
		m_pTarget = vecOut[0];
	}

	SetDlgPos();	


	for (UINT i = 0; i < (UINT)DLG_TYPE::END; ++i)
	{
		if (nullptr == m_arrComDlg[i])
			continue;

		m_arrComDlg[i]->init(m_pTarget);
	}
	addComponentDlg->SetGameObject(m_pTarget);
	addComponentDlg->Renew();
}


void CComponentView::update_always()
{
	if (nullptr == m_pTarget)
		return;

	if (m_pTarget->Animator2D())
	{
		((CAnimator2DDlg*)m_arrComDlg[(UINT)DLG_TYPE::ANIMATOR2D])->Animator2DStateCheck(m_pTarget);
	}
}

void CComponentView::update()
{
	update_always();
	   
	// 1 초에 한번
	static float fAccTime = 0.f;
	fAccTime += DT;
	if (fAccTime < 1.f)
		return;
	
	fAccTime = 0.f;

	// CompnentView Update
	SetDlgPos();

	if (nullptr == m_pTarget)
		return;

	for (UINT i = 0; i < (UINT)DLG_TYPE::END; ++i)
	{
		if (i != (UINT)DLG_TYPE::SCRIPT)
		{
			if (nullptr == m_pTarget->GetComponent((COMPONENT_TYPE)i))
			{
				continue;
			}
		}
		else
		{
			if (m_pTarget->GetScripts().empty())
			{
				continue;
			}
		}

		if (nullptr == m_arrComDlg[i])
		{
			continue;
		}

		m_arrComDlg[i]->update(m_pTarget);
	}
	addComponentDlg->SetGameObject(m_pTarget);
}

void CComponentView::SetTarget(CGameObject * _pTarget)
{
	if (nullptr != m_pCurResInfoDlg)
	{
		m_pCurResInfoDlg->ShowWindow(false);
	}

	m_pTarget = _pTarget;
	SetDlgPos();
}

void CComponentView::SetResoure(CResource * _pResource)
{
	for (UINT i = 0; i < (UINT)DLG_TYPE::END; ++i)
	{
		if (nullptr != m_arrComDlg[i])
			m_arrComDlg[i]->ShowWindow(false);
	}

	RES_TYPE eType = _pResource->GetType();
	m_pCurResInfoDlg = m_arrResInfoDlg[(UINT)eType];

	if (nullptr == m_pCurResInfoDlg)
		return;

	m_pTarget = nullptr;
	m_pCurResInfoDlg->ShowWindow(true);

	// dlg 에 Resource 을 알려준다.
	m_pCurResInfoDlg->SetResource(_pResource);


	CRect rtView, rtDlg;
	GetClientRect(rtView);

	m_pCurResInfoDlg->GetWindowRect(rtDlg);
	m_pCurResInfoDlg->SetWindowPos(nullptr, 0, 0, rtView.Width(), rtDlg.Height(), 0);

}

void CComponentView::SetDlgPos()
{
	if (nullptr == m_pTarget)
	{
		for (UINT i = 0; i < (UINT)DLG_TYPE::END; ++i)
		{
			if (nullptr == m_arrComDlg[i])
				continue;

			m_arrComDlg[i]->ShowWindow(false);
		}

		return;
	}
	addComponentDlg->ShowWindow(false);

	// Dlg Size 조절
	int iHeight = 0;

	CRect rtView;
	GetClientRect(rtView);

	CRect rtDlg;

	for (UINT i = 0; i < (UINT)DLG_TYPE::END; ++i)
	{
		if (nullptr == m_arrComDlg[i] || i == (UINT)DLG_TYPE::SCRIPT)
			continue;

		if (m_pTarget->GetComponent((COMPONENT_TYPE)i))
		{
			m_arrComDlg[i]->GetWindowRect(rtDlg);
			m_arrComDlg[i]->SetWindowPos(nullptr, 0, iHeight, rtView.Width(), rtDlg.Height(), 0);
			m_arrComDlg[i]->ShowWindow(true);
			iHeight += rtDlg.Height() - 1;
		}
		else
		{
			m_arrComDlg[i]->ShowWindow(false);
		}
	}

	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT]->GetWindowRect(rtDlg);
	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT]->SetWindowPos(nullptr, 0, iHeight, rtView.Width(), rtDlg.Height(), 0);
	m_arrComDlg[(UINT)DLG_TYPE::SCRIPT]->ShowWindow(true);

	iHeight += rtDlg.Height();

	addComponentDlg->GetWindowRect(rtDlg);
	addComponentDlg->SetWindowPos(nullptr, 0, iHeight, rtView.Width(), rtDlg.Height(), 0);
	addComponentDlg->ShowWindow(true);
}


