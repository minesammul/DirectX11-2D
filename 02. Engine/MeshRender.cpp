#include "stdafx.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Transform.h"

#include "Collider2D.h"
#include "Animator2D.h"
#include "Animation2D.h"
#include "ResMgr.h"

CMeshRender::CMeshRender()
	: m_pMesh(nullptr)
	, m_pMtrl(nullptr)
	, CComponent(COMPONENT_TYPE::MESHRENDER)
{	
}

CMeshRender::~CMeshRender()
{
}

CResPtr<CMaterial> CMeshRender::GetCloneMaterial()
{
	if (nullptr == m_pMtrl)
		return nullptr;	
	   
	m_pMtrl = m_pMtrl->Clone();

	CResMgr::GetInst()->AddCloneRes(m_pMtrl);

	return m_pMtrl;
}

void CMeshRender::update()
{
}

void CMeshRender::render()
{	
	Transform()->UpdateData();

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		CAnimation2D::ClearRegister();
	}

	if (m_pMtrl->GetShader() == nullptr)
	{
		return;
	}

	m_pMtrl->UpdateData();
	m_pMesh->SetLayout(m_pMtrl->GetShader());	
	m_pMesh->render();

	// Collider 가 있으면 그려준다.
	if (nullptr != Collider2D())
		Collider2D()->render();
}	

void CMeshRender::SaveToScene(FILE * _pFile)
{
	bool bMesh = true, bMtrl = true;

	if (nullptr == m_pMesh)
		bMesh = false;
	if (nullptr == m_pMtrl)
		bMtrl = false;

	fwrite(&bMesh, 1, 1, _pFile);
	if (bMesh)
	{
		SaveWString(m_pMesh->GetName().c_str(), _pFile);
		SaveWString(m_pMesh->GetPath().c_str(), _pFile);
	}

	fwrite(&bMtrl, 1, 1, _pFile);
	if (bMtrl)
	{
		SaveWString(m_pMtrl->GetName().c_str(), _pFile);
		SaveWString(m_pMtrl->GetPath().c_str(), _pFile);
	}
}

void CMeshRender::LoadFromScene(FILE * _pFile)
{
	bool bMesh = true, bMtrl = true;

	wstring strKey, strPath;

	fread(&bMesh, 1, 1, _pFile);
	if (bMesh)
	{
		strKey = LoadWString(_pFile);
		strPath = LoadWString(_pFile);

		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(strKey);
		if (nullptr == m_pMesh)
		{
			CResMgr::GetInst()->Load<CMesh>(strKey, strPath);
		}
	}

	fread(&bMtrl, 1, 1, _pFile);
	if (bMtrl)
	{
		strKey = LoadWString(_pFile);
		strPath = LoadWString(_pFile);

		m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(strKey);
		if (nullptr == m_pMtrl)
		{
			CResMgr::GetInst()->Load<CMaterial>(strKey, strPath);
		}
	}
}

