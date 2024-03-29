#pragma once

class CLayer;
class CGameObject;
class CScene;

class CSaveLoadMgr
{
private:
	static vector<bool> m_LayerCollisions;

private:
	CSaveLoadMgr();
	~CSaveLoadMgr();

public:
	static void SaveScene(const wstring& _strPath);
	static void SaveResource(FILE* _pFile);
	static void SaveLayer(CLayer* _pLayer, FILE* _pFile);
	static void SaveGameObject(CGameObject* _pObject, FILE* _pFile);

	static void LoadScene(const wstring& _strPath);
	static void LoadResource(FILE* _pFile);
	static CLayer* LoadLayer(FILE* _pFile, int layerIndex);
	static CGameObject* LoadGameObject(FILE* _pFile);

	static CScene* GetScene(const wstring& _strPath);
	static vector<bool> GetLayerCollisions(void);
};

