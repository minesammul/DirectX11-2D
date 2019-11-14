#pragma once
#include "Component.h"

#include "ResPtr.h"
#include "Mesh.h"
#include "Material.h"

// 1. ���簢�� 
// 2. ��

class CCollider2D :
	public CComponent
{
private:
	static vector<CResPtr<CMaterial>>	g_vecColMtrl;	// �浹ü���� ��� �� Material Pool
	static CResPtr<CMaterial>			g_pOriginMtrl;  // �浹ü�� ����� ���� Material

public:
	static void CreateMaterial();
	static CResPtr<CMaterial> GetCloneMtrl();
	static void ClearMaterial();


private:
	Vector3				m_vOffset;	// Object �� ���� �����ǥ
	Vector3				m_vFinalPos;// Transform ��ġ + Offset

	Vector3				m_vScale;	// �߰��� �������� ũ�� ������
	Vector3				m_vFinalScale; // Transform ũ�� * �浹ü ũ��
	
	COLLIDER2D_TYPE		m_eType;
	Matrix				m_matColWorld; // �浹ü ���� ���

	UINT				m_iColCount;

	CResPtr<CMesh>		m_pMesh;		
	CResPtr<CMaterial>  m_pCurMtrl;
	
public:
	virtual void update();
	virtual void finalupdate();
	
public:
	void SetOffset(const Vector3& _vOffset) { m_vOffset = _vOffset; m_vOffset.z = 0.f; }
	const Vector3& GetOffset() { return m_vOffset; }	

	void SetScale(const Vector3& _vScale) { m_vScale = _vScale; m_vScale.z = 0.f; }
	const Vector3& GetScale() { return m_vScale; }

	Vector3 GetFinalPositon() { return m_vFinalPos; }
	Vector3 GetFinalScale() { return m_vFinalScale; }

	void SetColliderType(COLLIDER2D_TYPE _eType);
	COLLIDER2D_TYPE GetCollider2DType() { return m_eType; }
	
	const Matrix& GetWorldMat() { return m_matColWorld; }

	void OnCollisionEnter(CCollider2D* _pOther);
	void OnCollision(CCollider2D* _pOther);
	void OnCollisionExit(CCollider2D* _pOther);

	void UpdateData();
	void render();

	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

	CLONE(CCollider2D);

public:
	CCollider2D();
	virtual ~CCollider2D();
};

