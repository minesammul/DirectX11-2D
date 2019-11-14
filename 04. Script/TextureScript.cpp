#include "stdafx.h"
#include "TextureScript.h"

#include <Camera.h>


CTextureScript::CTextureScript():
	CScript((UINT)SCRIPT_TYPE::TEXTURESCRIPT)
{
	UValue = 0.f;
}


CTextureScript::~CTextureScript()
{
}

void CTextureScript::start()
{
	cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
	CResPtr<CTexture> texture = Object()->Animator2D()->GetCurAnim()->GetNowFrameData().pTex;
	cloneMtrl->SetData(SHADER_PARAM::TEX_0, &texture);

	Vector4 color = Vector4(4.f, 4.f, 4.f, 1.f);
	cloneMtrl->SetData(SHADER_PARAM::VEC4_0, &color);

	beforeMainCameraPosition = Object()->Transform()->GetLocalPos();


	mainCamera = nullptr;
	vector<CCamera*> cameras = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	for (int index = 0; index < cameras.size(); index++)
	{
		CCamera* curCamera = cameras[index];

		if (curCamera->Object()->GetName().compare(L"MainCamera") == 0)
		{
			mainCamera = curCamera;
			break;
		}
	}
}

void CTextureScript::update()
{
	if (mainCamera != nullptr)
	{
		Vector3 mainCameraPosition = mainCamera->Object()->Transform()->GetLocalPos();


		if (beforeMainCameraPosition.x < mainCameraPosition.x)
		{
			cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
			UValue += TEXTURE_U_VALUE * DT;
			cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &UValue);
		}
		else if(beforeMainCameraPosition.x > mainCameraPosition.x)
		{
			cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
			UValue -= TEXTURE_U_VALUE * DT;
			cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &UValue);
		}

		beforeMainCameraPosition = mainCameraPosition;
	}

}
