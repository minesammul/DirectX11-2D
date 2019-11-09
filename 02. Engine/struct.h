#pragma once

#include "define.h"

struct Vec3 : public XMFLOAT3
{
	Vec3()
		: XMFLOAT3(0.f, 0.f, 0.f)
	{}

	Vec3(float _x, float _y, float _z)
		: XMFLOAT3(_x, _y, _z)
	{}

	Vec3(const XMVECTOR& _v)
		: XMFLOAT3(_v.vector4_f32[0], _v.vector4_f32[1], _v.vector4_f32[2])
	{}

	Vec3& operator = (const XMVECTOR& _v)
	{
		x = _v.vector4_f32[0];
		y = _v.vector4_f32[1];
		z = _v.vector4_f32[2];
		return *this;
	}

	float& operator[](UINT _iIdx)
	{
		if (_iIdx > 2)
			assert(nullptr);

		return *((float*)this + _iIdx);
	}
	
	operator XMVECTOR()
	{
		XMVECTOR v;
		v.vector4_f32[0] = x;
		v.vector4_f32[1] = y;
		v.vector4_f32[2] = z;
		v.vector4_f32[3] = 0.f;

		return v;
	}

	bool IsZero()
	{
		if (x == 0.f && y == 0.f && z == 0.f)
			return true;
		return false;
	}

	float Distance()
	{
		return sqrt(x*x + y * y + z * z);
	}

	Vec3& Normalize()
	{
		float fDistance = Distance();

		assert(fDistance);

		x /= fDistance;
		y /= fDistance;
		z /= fDistance;

		return *this;
	}

	float Dot(const Vec3& _vOther)
	{
		return (x * _vOther.x) + (y * _vOther.y) + (z * _vOther.z);
	}

	Vec3 operator + (const Vec3& _vec3)
	{
		return Vec3(x + _vec3.x, y + _vec3.y, z + _vec3.z);
	}	

	Vec3 operator * (const Vec3& _vec3)
	{
		return Vec3(x * _vec3.x, y * _vec3.y, z * _vec3.z);
	}

	Vec3 operator / (float _f)
	{
		assert(_f);
		return Vec3(x / _f, y / _f, z / _f);
	}
};

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
};

// Vertex
struct VTX
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
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
	Vec2 vLT;
	Vec2 vSize;
	int  iAnimCheck;
	int  iArrPadding[3];
};

struct tShaderParam
{
	int  arrInt[4];
	int referenceTileIndex[1024];
	float arrFloat[4];
	Vec2 arrVec2[4];
	Vec4 arrVec4[4];
	Matrix arrMat[4];
};

struct tGlobalValue
{
	UINT iLightCount;
	float fDeltaTime;
	double dAccTime;
};