#include "stdafx.h"
#include "Camera.h"

#include "Transform.h"
#include "Device.h"
#include "SceneMgr.h"

CCamera::CCamera()
	: m_eType(PROJ_TYPE::PERSPECTIVE)
	, m_fScale(1.f)
	, m_fFOV(XM_PI / 4.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)	
	, m_iLayerCheck(0)
	, CComponent(COMPONENT_TYPE::CAMERA)
{	
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
}

void CCamera::finalupdate()
{
	Vector3 vPos = Transform()->GetLocalPos();

	// View 행렬 만들기
	m_matView = XMMatrixIdentity();
	m_matView._41 = -vPos.x;	
	m_matView._42 = -vPos.y;
	m_matView._43 = -vPos.z;
		
	// Projection 행렬 만들기	
	tResolution tRes = CDevice::GetInst()->GetResolution();

	if( m_eType == PROJ_TYPE::PERSPECTIVE)
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, tRes.fWidth / tRes.fHeight, m_fNear, m_fFar);
	else
		m_matProj = XMMatrixOrthographicLH(tRes.fWidth * m_fScale, tRes.fHeight * m_fScale, m_fNear, m_fFar);

	CSceneMgr::GetInst()->RegisterCamera(this);
}

void CCamera::CheckLayer(UINT _iLayerIdx)
{
	UINT iCheck = 1 << _iLayerIdx;
	if (m_iLayerCheck & iCheck)
		m_iLayerCheck &= ~iCheck;
	else
		m_iLayerCheck |= iCheck;
}

void CCamera::SaveToScene(FILE * _pFile)
{
	fwrite(&m_eType, sizeof(UINT), 1, _pFile);
	fwrite(&m_fScale, sizeof(float), 1, _pFile);
	fwrite(&m_fFOV, sizeof(float), 1, _pFile);
	fwrite(&m_fNear, sizeof(float), 1, _pFile);
	fwrite(&m_fFar, sizeof(float), 1, _pFile);
	fwrite(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}

void CCamera::LoadFromScene(FILE * _pFile)
{
	fread(&m_eType, sizeof(UINT), 1, _pFile);
	fread(&m_fScale, sizeof(float), 1, _pFile);
	fread(&m_fFOV, sizeof(float), 1, _pFile);
	fread(&m_fNear, sizeof(float), 1, _pFile);
	fread(&m_fFar, sizeof(float), 1, _pFile);
	fread(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}
