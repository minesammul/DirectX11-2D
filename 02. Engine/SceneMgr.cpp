#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"

#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"

#include "GameObject.h"

#include "MeshRender.h"
#include "Transform.h"
#include "Camera.h"
#include "Collider2D.h"
#include "Animator2D.h"

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Sound.h"
#include "Texture.h"
#include "Prefab.h"

#include "Core.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_pNextScene(nullptr)
	, mousePickingObject(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);
	SAFE_DELETE(m_pNextScene);
}

void CSceneMgr::RegisterCamera(CCamera * _pCam)
{
	m_pCurScene->AddCamera(_pCam);
}

CGameObject* CSceneMgr::MousePicking(POINT mousePoint)
{
	//vector<CGameObject*> cameraObject;
	//m_pCurScene->FindGameObject(L"MainCamera", cameraObject);

	vector<CCamera*> cameraObjects = m_pCurScene->GetCamera();
	vector<CCamera*>::reverse_iterator cameraObjectsReverseIterator;
	cameraObjectsReverseIterator = cameraObjects.rbegin();
	
	CGameObject* finalSelectObject = nullptr;

	while (cameraObjectsReverseIterator != cameraObjects.rend())
	{
		//Matrix projectionMatrix = cameraObject[0]->Camera()->GetProjMat();
		Matrix projectionMatrix = (*cameraObjectsReverseIterator)->GetProjMat();
		DirectX::XMVECTOR projectionDeterminant = DirectX::XMMatrixDeterminant(projectionMatrix);
		Matrix inverseProjectionMatrix = DirectX::XMMatrixInverse(&projectionDeterminant, projectionMatrix);

		Matrix viewMatrix = (*cameraObjectsReverseIterator)->GetViewMat();
		DirectX::XMVECTOR viewDeterminant = DirectX::XMMatrixDeterminant(viewMatrix);
		Matrix inverseViewMatrix = DirectX::XMMatrixInverse(&viewDeterminant, viewMatrix);

		DirectX::XMVECTOR mouseClickPosition = DirectX::XMVectorSet(
			(2 * (float)(mousePoint.x - (windowRect.right / 2))) / (float)windowRect.right,
			(2 * (float)((windowRect.bottom / 2) - mousePoint.y)) / (float)windowRect.bottom,
			1.f,
			0.f);

		mouseClickPosition = DirectX::XMVector3Transform(mouseClickPosition, inverseProjectionMatrix);
		mouseClickPosition = DirectX::XMVector3Transform(mouseClickPosition, inverseViewMatrix);

		DirectX::XMVECTOR mouseClickOriginPos = mouseClickPosition;
		mouseClickOriginPos = DirectX::XMVectorSetZ(mouseClickOriginPos, 1.f);

		mousePickingPosition = mouseClickPosition;

		CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();

		CGameObject* selectObject = nullptr;
		float selectObjectZ = 1000.f;

		for (int layerIndex = 0; layerIndex < MAX_LAYER; layerIndex++)
		{

			if (m_pCurScene->GetLayer(layerIndex) == nullptr)
			{
				continue;
			}

			if ((*cameraObjectsReverseIterator)->IsValiedLayer(layerIndex) == false)
			{
				continue;
			}


			vector<CGameObject*> gameObject = m_pCurScene->GetLayer(layerIndex)->GetParentObject();
			for (int gameObjectIndex = 0; gameObjectIndex < gameObject.size(); gameObjectIndex++)
			{
				if (gameObject[gameObjectIndex]->IsActive() == false)
				{
					continue;
				}

				wstring tempName = gameObject[gameObjectIndex]->GetName();
				Matrix tempWorldMatrix = gameObject[gameObjectIndex]->Transform()->GetWorldMat();

				DirectX::XMVECTOR objectWorldPos[4];
				for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++)
				{
					objectWorldPos[vertexIndex] = DirectX::XMVector3TransformCoord(pVtx[vertexIndex].vPos, tempWorldMatrix);
				}

				DirectX::XMVECTOR mouseClickDirection = mouseClickPosition - mouseClickOriginPos;
				mouseClickDirection = DirectX::XMVector3Normalize(mouseClickDirection);
				float clickObjectUpperRightTriangleDist;

				bool isObjectUpperRightTriangleClick = DirectX::TriangleTests::Intersects(
					mouseClickOriginPos,
					mouseClickDirection,
					objectWorldPos[0],
					objectWorldPos[1],
					objectWorldPos[3],
					clickObjectUpperRightTriangleDist
				);

				float clickObjectBottomLeftTriangleDist;
				bool isObjectBottomLeftTriangleClick = DirectX::TriangleTests::Intersects(
					mouseClickOriginPos,
					mouseClickDirection,
					objectWorldPos[0],
					objectWorldPos[3],
					objectWorldPos[2],
					clickObjectBottomLeftTriangleDist
				);

				if (isObjectBottomLeftTriangleClick || isObjectUpperRightTriangleClick)
				{
					float clickObjectDist = 0;
					if (isObjectBottomLeftTriangleClick)
					{
						clickObjectDist = clickObjectBottomLeftTriangleDist;
					}
					else if (isObjectUpperRightTriangleClick)
					{
						clickObjectDist = clickObjectUpperRightTriangleDist;
					}

					if (clickObjectDist < selectObjectZ)
					{
						selectObject = gameObject[gameObjectIndex];
						selectObjectZ = clickObjectDist;
					}
				}
			}
		}

		if (selectObject != nullptr &&
			selectObject->GetComponent(COMPONENT_TYPE::CAMERA) == nullptr)
		{
			finalSelectObject = selectObject;
			break;
		}

		cameraObjectsReverseIterator++;
	}

	mousePickingObject = finalSelectObject;

	return finalSelectObject;
}

CGameObject * CSceneMgr::GetMousePickingObject()
{
	return mousePickingObject;
}

DirectX::XMVECTOR CSceneMgr::GetMousePickingPosition()
{
	return mousePickingPosition;
}

DirectX::XMVECTOR CSceneMgr::CalculationSceneMousePosition(POINT mousePoint, CCamera * camera)
{
	Matrix projectionMatrix = camera->GetProjMat();
	DirectX::XMVECTOR projectionDeterminant = DirectX::XMMatrixDeterminant(projectionMatrix);
	Matrix inverseProjectionMatrix = DirectX::XMMatrixInverse(&projectionDeterminant, projectionMatrix);

	Matrix viewMatrix = camera->GetViewMat();
	DirectX::XMVECTOR viewDeterminant = DirectX::XMMatrixDeterminant(viewMatrix);
	Matrix inverseViewMatrix = DirectX::XMMatrixInverse(&viewDeterminant, viewMatrix);

	DirectX::XMVECTOR sceneMousePosition = DirectX::XMVectorSet(
		(2 * (float)(mousePoint.x - (windowRect.right / 2))) / (float)windowRect.right,
		(2 * (float)((windowRect.bottom / 2) - mousePoint.y)) / (float)windowRect.bottom,
		1.f,
		0.f);

	sceneMousePosition = DirectX::XMVector3Transform(sceneMousePosition, inverseProjectionMatrix);
	sceneMousePosition = DirectX::XMVector3Transform(sceneMousePosition, inverseViewMatrix);

	return sceneMousePosition;
}

void CSceneMgr::init()
{
	// 수업용 임시 Scene 생성
	m_pCurScene = new CScene;

	// Layer 추가하기
	m_pCurScene->AddLayer(L"Default", 0);

	// Camera Object 만들기
	CGameObject* newObject = new CGameObject;

	newObject->SetName(L"MainCamera");
	newObject->AddComponent(new CTransform);
	newObject->AddComponent(new CCamera);

	newObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	newObject->Camera()->SetFOV(XM_PI / 4.f);
	newObject->Camera()->SetScale(1.f);
	newObject->Camera()->CheckLayer(m_pCurScene->FindLayer(L"Default")->GetLayerIdx());

	m_pCurScene->AddObject(L"Default", newObject);
	
	GetClientRect(CCore::GetInst()->GetWindowHwnd(), &windowRect);
}

void CSceneMgr::progress()
{
	m_pCurScene->update();
	m_pCurScene->lateupdate();

	m_pCurScene->finalupdate();

	CCollisionMgr::GetInst()->update();
	CEventMgr::GetInst()->update();
}

void CSceneMgr::progress_pause()
{
	m_pCurScene->finalupdate();
	CEventMgr::GetInst()->update();
}

void CSceneMgr::render()
{
	m_pCurScene->render();
}

void CSceneMgr::FindGameObject(const wstring & _strTagName, vector<CGameObject*>& _vecOut)
{
	m_pCurScene->FindGameObject(_strTagName, _vecOut);
}

void CSceneMgr::ChangeScene(CScene * _pNextScene)
{
	SAFE_DELETE(m_pCurScene);
	m_pCurScene = _pNextScene;
}