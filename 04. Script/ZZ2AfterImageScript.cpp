#include "stdafx.h"
#include "ZZ2AfterImageScript.h"


CZZ2AfterImageScript::CZZ2AfterImageScript() : 
	CScript((UINT)SCRIPT_TYPE::ZZ2AFTERIMAGESCRIPT)
{
	inverse = 0;
}


CZZ2AfterImageScript::~CZZ2AfterImageScript()
{
}

void CZZ2AfterImageScript::start(void)
{
	cloneMtrl = Object()->MeshRender()->GetCloneMaterial();

	texture = Object()->Animator2D()->GetCurAnim()->GetNowFrameData().pTex;
	cloneMtrl->SetData(SHADER_PARAM::TEX_0, &texture);

	alphaValue = 1.0f;
	isDestory = false;
}

void CZZ2AfterImageScript::update(void)
{
	if (isDestory == false)
	{
		cloneMtrl->SetData(SHADER_PARAM::INT_0, &inverse);

		alphaValue -= 3.f * DT;
		cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);

		if (alphaValue < 0.f)
		{
			DeleteObject(Object());
			isDestory = true;
		}
	}
}
