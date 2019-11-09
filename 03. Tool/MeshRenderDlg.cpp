// MeshRenderDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MeshRenderDlg.h"
#include "afxdialogex.h"

#include "resource.h"

#include "ListDlg.h"

#include <GameObject.h>
#include <ResMgr.h>
#include <MeshRender.h>

// CMeshRenderDlg 대화 상자

IMPLEMENT_DYNAMIC(CMeshRenderDlg, CDialogEx)

CMeshRenderDlg::CMeshRenderDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_MESHRENDERDLG, pParent)
{

}

CMeshRenderDlg::~CMeshRenderDlg()
{
}

void CMeshRenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editMesh);
	DDX_Control(pDX, IDC_EDIT2, m_editMtrl);
}

void CMeshRenderDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	CMeshRender* pMeshRender = GetTarget()->MeshRender();
	
	CString strName = pMeshRender->GetMesh()->GetName().c_str();
	m_editMesh.SetWindowTextW(strName);

	strName = pMeshRender->GetSharedMaterial()->GetName().c_str();
	m_editMtrl.SetWindowTextW(strName);
}


BEGIN_MESSAGE_MAP(CMeshRenderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeshRenderDlg::OnBtnMesh)
	ON_BN_CLICKED(IDC_BUTTON2, &CMeshRenderDlg::OnBtnMtrl)
END_MESSAGE_MAP()

// CMeshRenderDlg 메시지 처리기


void CMeshRenderDlg::OnBtnMesh()
{
	const map<wstring, CResource*>& mapRes =CResMgr::GetInst()->GetResources(RES_TYPE::MESH);

	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Mesh", vecResName);	
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();

		CResPtr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(strSelect.GetBuffer());

		GetTarget()->MeshRender()->SetMesh(pMesh);
	}
}

void CMeshRenderDlg::OnBtnMtrl()
{
	const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources(RES_TYPE::MATERIAL);

	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Material", vecResName);
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();
		CResPtr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strSelect.GetBuffer());
		GetTarget()->MeshRender()->SetMaterial(pMtrl);
	}
}