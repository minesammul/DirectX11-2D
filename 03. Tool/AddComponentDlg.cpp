// AddComponentDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "AddComponentDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <Animator2D.h>
#include <Camera.h>

// AddComponentDlg 대화 상자

IMPLEMENT_DYNAMIC(AddComponentDlg, CDialogEx)

AddComponentDlg::AddComponentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDCOMPONENT, pParent)
{

}

AddComponentDlg::~AddComponentDlg()
{
}

void AddComponentDlg::OnOK()
{
}

void AddComponentDlg::OnCancel()
{
}

void AddComponentDlg::SetGameObject(CGameObject * gameObject)
{
	this->targetObject = gameObject;
}

void AddComponentDlg::Renew()
{
	comboAddComponent.ResetContent();

	int comboInsertIndex = 0;
	for (int componentIndex = 0; componentIndex < (int)COMPONENT_TYPE::END; componentIndex++)
	{
		if (this->targetObject->GetComponent((COMPONENT_TYPE)componentIndex) != nullptr)
		{
			continue;
		}

		CString comboInputStr;
		switch ((COMPONENT_TYPE)componentIndex)
		{
		case COMPONENT_TYPE::TRANSFORM:
			comboInputStr = L"TRANSFORM";
			break;
		case COMPONENT_TYPE::MESHRENDER:
			comboInputStr = L"MESHRENDER";
			break;
		case COMPONENT_TYPE::CAMERA:
			comboInputStr = L"CAMERA";
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			comboInputStr = L"COLLIDER2D";
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
			comboInputStr = L"ANIMATOR2D";
			break;
		}
		
		if (comboInputStr.IsEmpty() == false)
		{
			comboAddComponent.InsertString(comboInsertIndex, comboInputStr);
			DWORD_PTR componentEnumValue = (int)componentIndex;
			comboAddComponent.SetItemData(comboInsertIndex, componentEnumValue);
			comboInsertIndex += 1;
		}
	}

	if (this->targetObject->GetComponent(COMPONENT_TYPE::SCRIPT) == nullptr)
	{
		comboAddComponent.InsertString(comboInsertIndex, L"SCRIPT");
		DWORD_PTR componentEnumValue = (int)COMPONENT_TYPE::SCRIPT;
		comboAddComponent.SetItemData(comboInsertIndex, componentEnumValue);
	}
}

void AddComponentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comboAddComponent);
}


BEGIN_MESSAGE_MAP(AddComponentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddComponentDlg::OnBnClickedButtonAddComponent)
END_MESSAGE_MAP()


// AddComponentDlg 메시지 처리기


void AddComponentDlg::OnBnClickedButtonAddComponent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int selectIndex = comboAddComponent.GetCurSel();
	if (selectIndex == -1)
	{
		return;
	}

	DWORD_PTR componentEnumValue = comboAddComponent.GetItemData(selectIndex);

	switch ((COMPONENT_TYPE)componentEnumValue)
	{
	case COMPONENT_TYPE::TRANSFORM:
		break;
	case COMPONENT_TYPE::MESHRENDER:
		break;
	case COMPONENT_TYPE::CAMERA:
		targetObject->AddComponent(new CCamera);
		break;
	case COMPONENT_TYPE::COLLIDER2D:
		break;
	case COMPONENT_TYPE::ANIMATOR2D:
		targetObject->AddComponent(new CAnimator2D);

		break;
	case COMPONENT_TYPE::SCRIPT:
		break;
	}

	Renew();
}

void AddComponentDlg::PostNcDestroy()
{
	delete this;
	CDialogEx::PostNcDestroy();
}
