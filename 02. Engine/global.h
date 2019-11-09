#pragma once

#define _XM_NO_INTRINSICS_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

typedef XMFLOAT2 Vec2;
//typedef XMFLOAT3 Vec3;
typedef XMFLOAT4 Vec4;
typedef XMMATRIX Matrix;

#include <vector>
#include <list>
#include <map>

using namespace std;

#include "define.h"
#include "struct.h"

extern tTransform g_transform;
extern tAnim2D g_anim2d;
extern tGlobalValue g_global;

// 숙제.
// - 플레이어 Animation 에 그림자 만들기