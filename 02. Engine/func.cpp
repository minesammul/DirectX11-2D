#include "stdafx.h"
#include "func.h"

float GetAngle(float _fRadian)
{
	return (_fRadian / XM_PI) * 180.f;
}

float GetRadian(float _fAngle)
{
	return (_fAngle / 180.f) * XM_PI;
}

void SaveWString(const wchar_t* _pStr, FILE * _pFile)
{
	int iLen = wcslen(_pStr);
	fwrite(&iLen, sizeof(int), 1, _pFile);
	fwrite(_pStr, sizeof(wchar_t), iLen, _pFile);
}

wchar_t* LoadWString(FILE * _pFile)
{
	static wchar_t szBuffer[255] = {};
	wmemset(szBuffer, L'\0', 255);

	int iLen = 0;
	fread(&iLen, sizeof(int), 1, _pFile);
	fread(szBuffer, sizeof(wchar_t), iLen, _pFile);

	return szBuffer;
}
