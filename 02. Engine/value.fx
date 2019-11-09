#ifndef _VALUE
#define _VALUE

struct TileComponent
{
    int4 referenceIndex;
};

cbuffer MATRIX : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
}

cbuffer MATERIAL : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;

    TileComponent g_tileData[256];

    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;

    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;

    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;

    row_major Matrix g_mat_0;
    row_major Matrix g_mat_1;
    row_major Matrix g_mat_2;
    row_major Matrix g_mat_3;
}

cbuffer ANIM2D : register(b2)
{
    float2 vLT;
    float2 vSize;
    int iAnimCheck;
    float3 vPadding;
}

cbuffer GLOBAL_VALUE : register(b3)
{
    uint iLightCount; // 광원 개수
    float fDT; // deltatime
    float fAccTime; // 누적시간
    float fPadding;
}


Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);

Texture2D g_tex_anim : register(t17);

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);
SamplerState g_sam_2 : register(s2);
SamplerState g_sam_3 : register(s3);






#endif