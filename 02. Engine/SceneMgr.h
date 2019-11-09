#pragma once

class CScene;
class CCamera;
class CGameObject;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*	m_pCurScene;
	CScene* m_pNextScene;
	
	CGameObject* mousePickingObject;
	DirectX::XMVECTOR mousePickingPosition;
	RECT windowRect;

public:
	void RegisterCamera(CCamera* _pCam);
	CScene* GetCurScene() { return m_pCurScene; }

	CGameObject* MousePicking(POINT mousePoint);
	CGameObject* GetMousePickingObject();
	DirectX::XMVECTOR GetMousePickingPosition();
	DirectX::XMVECTOR CalculationSceneMousePosition(POINT mousePoint, CCamera* camera);

	void SetWindowRect(RECT rect) { windowRect = rect; }

public:
	void init();
	void progress();
	void progress_pause();
	void render();

	void FindGameObject(const wstring& _strTagName, vector<CGameObject*>& _vecOut);
	void ChangeScene(CScene* _pNextScene);
};

