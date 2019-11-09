#pragma once
#include "Entity.h"


class CConstBuffer :
	public CEntity
{
private:
	ID3D11Buffer*		m_pBuffer;
	UINT				m_iSize;		//상수버퍼 최대 사이즈
	UINT				m_iRegister;

	void*				m_pSysMem;
	UINT				m_iCurSize; // SystemMem 에 현재 Add 된 데이터 사이즈


public:
	void Create(UINT _iSize, UINT _iRegiserNum);	
	void AddData(void* _pSrc, UINT _iSize);
	void UpdateData();
	void SetRegister(UINT _iShaderType);
	void SetRegisterAll();

public:
	CLONE_DISABLE(CConstBuffer);

public:
	CConstBuffer();
	virtual ~CConstBuffer();
};

