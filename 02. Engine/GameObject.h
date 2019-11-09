#pragma once

#include "entity.h"

class CComponent;
class CTransform;
class CMeshRender;
class CCamera;
class CScript;
class CCollider2D;
class CAnimator2D;

class CGameObject :
	public CEntity
{
private:
	CGameObject*			m_pParent;

	CComponent*				m_arrCom[(UINT)COMPONENT_TYPE::END];
	int						m_iLayerIdx;
	vector<CScript*>		m_vecScript;

	vector<CGameObject*>	m_vecChild;

	bool					m_bDead;
	bool					m_bActive;
	

public:
	void awake();
	void start();

	void update();
	void lateupdate();
	void finalupdate();

	void OnEnable();
	void OnDisable();

	void render();

public:
	void AddComponent(CComponent* _pCom);

	CTransform* Transform() {return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM];}
	CMeshRender* MeshRender() {return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER];}
	CCamera * Camera() {return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA];}
	CCollider2D* Collider2D() { return (CCollider2D*)m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER2D]; }
	CAnimator2D* Animator2D() { return (CAnimator2D*)m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR2D]; }
	CComponent* GetComponent(COMPONENT_TYPE _eType) {return m_arrCom[(UINT)_eType];}
	vector<CScript*>& GetScripts() { return m_vecScript; }
	
	int GetLayerIdx() { return m_iLayerIdx; }
	void SetLayerIdx(UINT _iIdx) { m_iLayerIdx = _iIdx; }

	void AddChild(CGameObject* _pChildObj);
	CGameObject* GetParent() { return m_pParent; }

	const vector<CGameObject*>& GetChild() { return m_vecChild; }
		
	bool IsDead() { return m_bDead; }
	bool IsAncestor(CGameObject* _pTarget);

	bool IsActive() { return m_bActive; }
	void Active(bool _bTrue);

	void SaveToScene(FILE* _pFile);
	void LoadFromScene(FILE* _pFile);

private:
	void SetParent(CGameObject* _pParent);
	void ClearParent(); // �θ������Ʈ���� ���ö�, �θ������Ʈ���� ���� ����
	void ClearLayer();	// ������Ʈ�� Layer ���� ���ö�, Layer ���� ���� ����
	void Kill() { m_bDead = true; }
	void ClearChild(UINT _iChildIdx); // Ư�� �ε��� �ڽ� ������Ʈ�� �ڽĿ��� ����

	// �����ϰ� �����ϱ� ���ؼ� ���� ���� �۾�
	// 1. �ֻ��� �θ��� ���, Layer ���� ����
	// 2. �ڽ� ������Ʈ���� ���, �θ𿡼� ����
	void Disconnect();
	

public:
	template<typename T>
	CScript* GetScript();

public:
	CLONE(CGameObject);
	CGameObject(const CGameObject& _origin);

public:
	CGameObject();
	virtual ~CGameObject();

	friend class CLayer;
	friend class CEventMgr;
};

// 1. dynamic_cast ������.
// 2. ��Ӱ��迡 ���� ����Ȯ �� �� �ִ�.
template<typename T>
inline CScript * CGameObject::GetScript()
{
	const type_info& info = typeid(T);	

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		if (dynamic_cast<T*>(m_vecScript[i]))
			return m_vecScript[i];
	}	

	return nullptr;
}