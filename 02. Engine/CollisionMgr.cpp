#include "stdafx.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "GameObject.h"
#include "Collider2D.h"

#include "ResMgr.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if (m_arrCheck[i] & (1 << j))
			{
				// i ObjTYpe, j ObjType 충돌 진행
				CollisionGroup(i, j);
			}
		}
	}
}

bool CCollisionMgr::IsCollisionLayers(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	UINT iIdx = (UINT)(pLeftLayer->GetLayerIdx() < pRightLayer->GetLayerIdx() ? pLeftLayer->GetLayerIdx() : pRightLayer->GetLayerIdx());
	UINT iBitIdx = iIdx == (UINT)pLeftLayer->GetLayerIdx() ? (UINT)pRightLayer->GetLayerIdx() : (UINT)pLeftLayer->GetLayerIdx();
	
	bool layerCollision = false;
	if (m_arrCheck[iIdx] & (1 << iBitIdx))
	{
		layerCollision = true;
	}

	return layerCollision;
}

void CCollisionMgr::CollisionUnCheck(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	UINT iIdx = (UINT)(pLeftLayer->GetLayerIdx() < pRightLayer->GetLayerIdx() ? pLeftLayer->GetLayerIdx() : pRightLayer->GetLayerIdx());
	UINT iBitIdx = iIdx == (UINT)pLeftLayer->GetLayerIdx() ? (UINT)pRightLayer->GetLayerIdx() : (UINT)pLeftLayer->GetLayerIdx();
	
	m_arrCheck[iIdx] &= (0 << iBitIdx);
}

void CCollisionMgr::CollisionGroup(int _leftIdx, int _rightIdx)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetLayer(_leftIdx)->GetAllObject();
	const vector<CGameObject*>& vecRight = pCurScene->GetLayer(_rightIdx)->GetAllObject();

	COL_ID colID;

	for (UINT i = 0; i < vecLeft.size(); ++i)
	{
		for (UINT j = 0; j < vecRight.size(); ++j)
		{
			// 두 오브젝트 중에서 충돌체가 없는 경우가 있다면
			/*if (vecLeft[i]->Collider2D() == nullptr || vecLeft[i]->Collider2D() == nullptr)
				continue;*/
			if (vecLeft[i]->Collider2D() == nullptr || vecRight[j]->Collider2D() == nullptr)
			{
				continue;
			}

			colID.left = vecLeft[i]->Collider2D()->GetID();
			colID.right = vecRight[j]->Collider2D()->GetID();

			map<unsigned long long, bool>::iterator iter = m_mapID2D.find(colID.ID);

			if (IsCollision(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				// 충돌 했다.
				if (iter == m_mapID2D.end())
				{
					// 충돌 조합 등록된적 없음 ==> 충돌한적 없음					
					vecLeft[i]->Collider2D()->OnCollisionEnter(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollisionEnter(vecLeft[i]->Collider2D());
					m_mapID2D.insert(make_pair(colID.ID, true));
				}
				else if (false == iter->second)
				{
					// 이전에 충돌하지 않고 있었다.
					vecLeft[i]->Collider2D()->OnCollisionEnter(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollisionEnter(vecLeft[i]->Collider2D());
					iter->second = true;
				}
				else {
					// 충돌 중이다.
					vecLeft[i]->Collider2D()->OnCollision(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollision(vecLeft[i]->Collider2D());
				}
			}
			else // 충돌하지 않고 있다.
			{
				if (iter != m_mapID2D.end() && true == iter->second)
				{
					// 이전에는 충돌 중이었다. ==>이번에 떨어진 상황
					vecLeft[i]->Collider2D()->OnCollisionExit(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollisionExit(vecLeft[i]->Collider2D());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	if (_pLeft->GetCollider2DType() == COLLIDER2D_TYPE::RECT && _pRight->GetCollider2DType() == COLLIDER2D_TYPE::RECT)
	{
		// Rect Rect 충돌
		return CollisionRect(_pLeft, _pRight);
	}
	else if (_pLeft->GetCollider2DType() == COLLIDER2D_TYPE::CIRCLE && _pRight->GetCollider2DType() == COLLIDER2D_TYPE::CIRCLE)
	{
		// Circle Circle

	}
	else
	{
		// Rect, Circle
	}

	return false;
}

bool CCollisionMgr::CollisionRect(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	static CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"ColliderRectMesh");

	Matrix matLeftWorld = _pLeft->GetWorldMat();
	Matrix matRightWorld = _pRight->GetWorldMat();

	VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();

	Vec3 vLeftWorldPos[4] = {};
	Vec3 vRightWorldPos[4] = {};	   

	for (UINT i = 0; i < 4; ++i)
	{
		vLeftWorldPos[i] = XMVector3TransformCoord(pVtx[i].vPos, matLeftWorld);
		vLeftWorldPos[i].z = 0.f;
	}

	for (UINT i = 0; i < 4; ++i)
	{
		vRightWorldPos[i] = XMVector3TransformCoord(pVtx[i].vPos, matRightWorld);
		vRightWorldPos[i].z = 0.f;
	}

	Vec3 vLeftCenter = (vLeftWorldPos[3] + vLeftWorldPos[0]) / 2.f;
	Vec3 vRightCenter = (vRightWorldPos[3] + vRightWorldPos[0]) / 2.f;

	Vec3 vCenter = vLeftCenter - vRightCenter;

	Vec3 vProj[4] = {};
	Vec3 vAxis[4] = {};

	vProj[0] = vLeftWorldPos[0] - vLeftWorldPos[2];
	vAxis[0] = vProj[0];	

	vProj[1] = vLeftWorldPos[3] - vLeftWorldPos[2];
	vAxis[1] = vProj[1];	

	vProj[2] = vRightWorldPos[0] - vRightWorldPos[2];
	vAxis[2] = vProj[2];	

	vProj[3] = vRightWorldPos[3] - vRightWorldPos[2];
	vAxis[3] = vProj[3];
	
	for (UINT i = 0; i < 4; ++i)
	{
		if (vAxis[i].IsZero())
			return false;

		vAxis[i].Normalize();
	}

	float fSum = 0.f;

	for (UINT i = 0; i < 4; ++i)
	{
		fSum = 0.f;
		for (UINT j = 0; j < 4; ++j)
		{
			fSum += abs(vProj[j].Dot(vAxis[i]));
		}

		// 충돌체 각 변을 투영시킨 거리의 절반
		fSum /= 2.f;

		// 중심을 이은 벡터를 투영시킨 거리
		float fDist = abs(vCenter.Dot(vAxis[i]));
		
		if (fDist > fSum)
			return false;
	}

	return true;
}

bool CCollisionMgr::CollisionCircle(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	return false;
}

bool CCollisionMgr::IsCollision(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	return false;
}


bool CCollisionMgr::CollisionCube(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	return false;
}

bool CCollisionMgr::CollisionSphere(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	return false;
}

void CCollisionMgr::CollisionCheck(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	CollisionCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}

void CCollisionMgr::CollisionCheck(int _iLayerIdx1, int _iLayerIdx2)
{
	// 배열의 인덱스
	UINT iIdx = (UINT)(_iLayerIdx1 < _iLayerIdx2 ? _iLayerIdx1 : _iLayerIdx2);
	UINT iBitIdx = iIdx == (UINT)_iLayerIdx1 ? (UINT)_iLayerIdx2 : (UINT)_iLayerIdx1;
	m_arrCheck[iIdx] |= (1 << iBitIdx);
}