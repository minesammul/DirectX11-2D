#include "stdafx.h"
#include "Transform.h"

#include "Device.h"
#include "ConstBuffer.h"

tTransform g_transform;

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{	
}

CTransform::~CTransform()
{
}

void CTransform::update()
{		
}

void CTransform::finalupdate()
{
	Matrix matScale = XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);
	Matrix matRotationX = XMMatrixRotationX(m_vLocalRot.x);
	Matrix matRotationY = XMMatrixRotationY(m_vLocalRot.y);
	Matrix matRotationZ = XMMatrixRotationZ(m_vLocalRot.z);
	Matrix matTrans = XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;

	// 부모 오브젝트가 있으면, 부모 월드행렬을 뒤에 곱해준다.
	CGameObject* pParentObj = ParentObject();
	if (pParentObj)
	{
		const Matrix& matParentWorld = pParentObj->Transform()->GetWorldMat();
		m_matWorld *= matParentWorld;
	}
}

void CTransform::UpdateData()
{
	g_transform.matWorld = m_matWorld;
	g_transform.matWV = m_matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;



	static CConstBuffer* pCB = CDevice::GetInst()->FindConstBuffer(L"Transform");
	   
	pCB->AddData(&g_transform, sizeof(tTransform));
	pCB->UpdateData();	
	pCB->SetRegister((UINT)SHADER_TYPE::VERTEX_SHADER);
}

void CTransform::SaveToScene(FILE * _pFile)
{
	fwrite(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalRot, sizeof(Vec3), 1, _pFile);
}

void CTransform::LoadFromScene(FILE * _pFile)
{
	fread(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalRot, sizeof(Vec3), 1, _pFile);
}
