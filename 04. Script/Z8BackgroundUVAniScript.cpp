#include "stdafx.h"
#include "Z8BackgroundUVAniScript.h"


CZ8BackgroundUVAniScript::CZ8BackgroundUVAniScript() :
	CScript((UINT)SCRIPT_TYPE::Z8BACKGROUNDUVANISCRIPT)
{
	textureUValue = 0.f;
}


CZ8BackgroundUVAniScript::~CZ8BackgroundUVAniScript()
{
}

void CZ8BackgroundUVAniScript::start()
{
	cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
	CResPtr<CTexture> selectTexture = Object()->Animator2D()->GetCurAnim()->GetNowFrameData().pTex;
	cloneMtrl->SetData(SHADER_PARAM::TEX_0, &selectTexture);
	
	if (Object()->GetName().compare(L"IntroBackGround1") == 0)
	{
		Vector4 colorMulValue = Vector4(2.46f, 1.49f, 1.f, 1.f);
		cloneMtrl->SetData(SHADER_PARAM::VEC4_0, &colorMulValue);
	}
	else if (Object()->GetName().compare(L"IntroBackGround2") == 0)
	{
		Vector4 colorMulValue = Vector4(1.53f, 1.22f, 1.f, 1.f);
		cloneMtrl->SetData(SHADER_PARAM::VEC4_0, &colorMulValue);
	}
	else if (Object()->GetName().compare(L"IntroBackGround3") == 0)
	{
		Vector4 colorMulValue = Vector4(1.f, 1.f, 1.f, 1.f);
		cloneMtrl->SetData(SHADER_PARAM::VEC4_0, &colorMulValue);
	}
}

void CZ8BackgroundUVAniScript::update()
{
	if (Object()->GetName().compare(L"IntroBackGround2") == 0)
	{
		textureUValue += 0.01f * DT;
		cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &textureUValue);
	}
	else if (Object()->GetName().compare(L"IntroBackGround3") == 0)
	{
		textureUValue += 0.05f * DT;
		cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &textureUValue);
	}
}
