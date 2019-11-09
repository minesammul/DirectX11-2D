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
	void ClearParent(); // 부모오브젝트에서 나올때, 부모오브젝트와의 관계 제거
	void ClearLayer();	// 오브젝트가 Layer 에서 나올때, Layer 와의 관계 제거
	void Kill() { m_bDead = true; }
	void ClearChild(UINT _iChildIdx); // 특정 인덱스 자식 오브젝트를 자식에서 제거

	// 안전하게 삭제하기 위해서 연결 끊는 작업
	// 1. 최상위 부모일 경우, Layer 에서 제거
	// 2. 자식 오브젝트였을 경우, 부모에서 제거
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

// 1. dynamic_cast 느리다.
// 2. 상속관계에 따라서 부정확 할 수 있다.
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