#include "stdafx.h"
#include "ZZ1MouseTraceScript.h"

#include <Camera.h>

CZZ1MouseTraceScript::CZZ1MouseTraceScript() : 
	CScript((UINT)SCRIPT_TYPE::ZZ1MOUSETRACESCRIPT)
{
}


CZZ1MouseTraceScript::~CZZ1MouseTraceScript()
{
}

void CZZ1MouseTraceScript::start()
{
	mainCamera = nullptr;
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

void CZZ1MouseTraceScript::update()
{
	Vector3 mousePosition = CSceneMgr::GetInst()->CalculationSceneMousePosition(CKeyMgr::GetInst()->GetMousePos(), mainCamera);
	mousePosition.z = Object()->Transform()->GetLocalPos().z;
	Object()->Transform()->SetLocalPos(mousePosition);
}
