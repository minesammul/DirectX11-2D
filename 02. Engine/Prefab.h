#pragma once
#include "Resource.h"

class CGameObject;

class CPrefab :
	public CResource
{
private:
	CGameObject*	m_pProto;
	vector<UINT>    m_vecScriptType;

public:
	CGameObject* Instantiate();
	CGameObject* GetPrefabObjectOriginal();

public:
	virtual bool LoadFromScene(FILE* _pFile);

private:
	void SaveProtoObject(CGameObject* _pProto, FILE* _pFile);
	CGameObject* LoadProtoObject(FILE* _pFile);


public:
	virtual void Save();
	virtual void Load(const wstring& _strFilePath);

public:
	CPrefab();
	CPrefab(CGameObject* _pProtoObj);
	virtual ~CPrefab();

public:
	vector<UINT> GetScriptType(void) 
	{
		return m_vecScriptType;
	}
};

