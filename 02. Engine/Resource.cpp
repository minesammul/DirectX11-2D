#include "stdafx.h"
#include "Resource.h"


void CResource::SaveToScene(FILE * _pFile)
{
	// 키값
	SaveWString(GetName().c_str(), _pFile);

	// 경로
	SaveWString(m_strPath.c_str(), _pFile);
}

bool CResource::LoadFromScene(FILE * _pFile)
{
	// 키값
	SetName(LoadWString(_pFile));

	// 경로
	m_strPath = LoadWString(_pFile);
	return true;
}

CResource::CResource(RES_TYPE _eType) :
	m_eType(_eType)
{
}


CResource::~CResource()
{
}
