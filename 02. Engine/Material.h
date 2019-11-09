#pragma once
#include "Resource.h"

#include "ResPtr.h"
#include "Shader.h"
#include "Texture.h"

class CMaterial :
	public CResource
{
private:
	CResPtr<CShader>	m_pShader;
	tShaderParam		m_param;
	CResPtr<CTexture>   m_arrTex[(UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0];

public:
	CResPtr<CShader> GetShader() { return m_pShader; }
	void SetShader(CResPtr<CShader> _pShader);
	void SetData(SHADER_PARAM _eType, void* _pSrc);
	tShaderParam GetParamData() { return m_param; }
	CResPtr<CTexture>* GetTexData() { return m_arrTex; }

	void SetTileData(int tileData[]);

public:
	void UpdateData();

public:
	virtual void Load(const wstring& _strFilePath);
	virtual void Save();
	virtual bool LoadFromScene(FILE* _pFile);

	CLONE(CMaterial);

public:
	CMaterial();
	virtual ~CMaterial();
};

