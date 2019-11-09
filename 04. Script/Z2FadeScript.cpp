#include "stdafx.h"
#include "Z2FadeScript.h"

#include <Camera.h>

CZ2FadeScript::CZ2FadeScript() : 
	CScript((UINT)SCRIPT_TYPE::Z2FADESCRIPT)
{
}


CZ2FadeScript::~CZ2FadeScript()
{
}

void CZ2FadeScript::start()
{
	alphaValue = 1.f;
	isStart = true;

	vector<CCamera*> findCamera = CSceneMgr::GetInst()->GetCurScene()->GetCamera();
	if (findCamera.empty() == false)
	{
		for (int index = 0; index < findCamera.size(); index++)
		{
			if (findCamera[index]->Object()->GetName().compare(L"MainCamera") == 0)
			{
				mainCamera = findCamera[index];
				break;
			}
		}
	}
}

void CZ2FadeScript::update()
{
	if (isStart == true)
	{
		cloneMtrl = Object()->MeshRender()->GetCloneMaterial();
		alphaValue -= 1.f * DT;
		cloneMtrl->SetData(SHADER_PARAM::FLOAT_0, &alphaValue);

		//float colorMulValue = COLOR_MULIT_VALUE;
		Vec4 colorMulValue = Vec4(COLOR_MULIT_VALUE, COLOR_MULIT_VALUE, COLOR_MULIT_VALUE, COLOR_MULIT_VALUE);
		cloneMtrl->SetData(SHADER_PARAM::VEC4_0, &colorMulValue);

		if (alphaValue <= 0.f)
		{
			isStart = false;
			alphaValue = 1.f;
		}

		Vec3 cameraPosition = mainCamera->Object()->Transform()->GetLocalPos();
		Vec3 objectPosition = Object()->Transform()->GetLocalPos();
		objectPosition.x = cameraPosition.x;
		objectPosition.y = cameraPosition.y;

		Object()->Transform()->SetLocalPos(objectPosition);
	}
}
