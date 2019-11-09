#include "stdafx.h"
#include "Shader.h"

#include "PathMgr.h"

#include "Device.h"

#include "BlendState.h"

CShader::CShader()
	: m_pVSBlob(nullptr)
	, m_pHSBlob(nullptr)
	, m_pDSBlob(nullptr)
	, m_pGSBlob(nullptr)
	, m_pPSBlob(nullptr)
	, m_pErrBlob(nullptr)
	, m_pVS	(nullptr)
	, m_pHS	(nullptr)
	, m_pDS	(nullptr)
	, m_pGS	(nullptr)
	, m_pPS	(nullptr)
	, m_pBlendState(nullptr)
	, CResource(RES_TYPE::SHADER)
{
}

CShader::~CShader()
{
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pHSBlob);
	SAFE_RELEASE(m_pDSBlob);
	SAFE_RELEASE(m_pGSBlob);
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pErrBlob);

	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pHS);
	SAFE_RELEASE(m_pDS);
	SAFE_RELEASE(m_pGS);
	SAFE_RELEASE(m_pPS);
}

void CShader::CreateVertexShader(const wstring & _strFilePath, const string& _strFuncName, UINT _iHigh, UINT _iLow)
{
	// Shader 만들기
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	wstring strPath = CPathMgr::GetResPath();
	strPath += _strFilePath;

	char strTarget[20] = {};
	sprintf_s(strTarget, "vs_%d_%d", _iHigh, _iLow);


	// VtxShader Compile
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFuncName.c_str()
		, strTarget, iFlag, 0, &m_pVSBlob, &m_pErrBlob)))
	{
		char* pErr = (char*)m_pErrBlob->GetBufferPointer();
		MessageBoxA(nullptr, pErr, "Pixel Shader Error", MB_OK);
		assert(nullptr);
	}
	
	// Create Vertex Shader
	DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), nullptr, &m_pVS);
}

void CShader::CreatePixelShader(const wstring & _strFilePath, const string & _strFuncName, UINT _iHigh, UINT _iLow)
{
	// Shader 만들기
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif

	wstring strPath = CPathMgr::GetResPath();
	strPath += _strFilePath;

	char strTarget[20] = {};
	sprintf_s(strTarget, "ps_%d_%d", _iHigh, _iLow);

	// VtxShader Compile
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFuncName.c_str()
		, strTarget, iFlag, 0, &m_pPSBlob, &m_pErrBlob)))
	{
		char* pErr = (char*)m_pErrBlob->GetBufferPointer();
		MessageBoxA(nullptr, pErr, "Pixel Shader Error", MB_OK);
		assert(nullptr);
	}	

	// Create Vertex Shader
	DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize(), nullptr, &m_pPS);
}

void CShader::UpdateData()
{
	// 물체 렌더링
	CONTEXT->VSSetShader(m_pVS, nullptr, 0);
	CONTEXT->HSSetShader(m_pHS, nullptr, 0);
	CONTEXT->DSSetShader(m_pDS, nullptr, 0);
	CONTEXT->GSSetShader(m_pGS, nullptr, 0);
	CONTEXT->PSSetShader(m_pPS, nullptr, 0);

	if (m_pBlendState)
		m_pBlendState->UpdateData();
	else
		CBlendState::UpdateDefaultData();
}
