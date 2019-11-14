#pragma once

#include "define.h"

struct tResolution
{
	float fWidth;
	float fHeight;
};

struct tEvent
{
	EVENT_TYPE	eType;
	INT_PTR		wParam;	
	INT_PTR		lParam;	
	vector<bool> boolVector;
};

// Vertex
struct VTX
{
	Vector3 vPos;
	Vector4 vColor;
	Vector2 vUV;
};



//===============
// 상수버퍼 구조체
//===============
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWV;
	Matrix matWVP;
};

struct tAnim2D
{
	Vector2 vLT;
	Vector2 vSize;
	int  iAnimCheck;
	int  iArrPadding[3];
};

struct tShaderParam
{
	int  arrInt[4];
	int referenceTileIndex[1024];
	float arrFloat[4];
	Vector2 arrVec2[4];
	Vector4 arrVec4[4];
	Matrix arrMat[4];
};

struct tGlobalValue
{
	UINT iLightCount;
	float fDeltaTime;
	double dAccTime;
};