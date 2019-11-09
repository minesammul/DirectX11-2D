// Collider2DDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Collider2DDlg.h"
#include "afxdialogex.h"

#include <GameObject.h>
#include <Collider2D.h>

// Collider2DDlg 대화 상자

IMPLEMENT_DYNAMIC(Collider2DDlg, CDialogEx)


Collider2DDlg::Collider2DDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_COLLIDER2DDLG, pParent)
{
	focus = false;
}

Collider2DDlg::~Collider2DDlg()
{
}

void Collider2DDlg::UpdatePosition(CGameObject * target)
{
	CCollider2D* targetCollider2D = target->Collider2D();
	Vec3 collider2DPosition = targetCollider2D->GetOffset();
	
	CString inputStr;
	inputStr.Format(L"%f", collider2DPosition.x);
	editPositionX.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider2DPosition.y);
	editPositionY.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider2DPosition.z);
	editPositionZ.SetWindowTextW(inputStr);
}

void Collider2DDlg::UpdateScale(CGameObject * target)
{
	CCollider2D* targetCollider2D = target->Collider2D();
	Vec3 collider2DScale = targetCollider2D->GetScale();

	CString inputStr;
	inputStr.Format(L"%f", collider2DScale.x);
	editScaleX.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider2DScale.y);
	editScaleY.SetWindowTextW(inputStr);
	inputStr.Format(L"%f", collider2DScale.z);
	editScaleZ.SetWindowTextW(inputStr);
}

void Collider2DDlg::UpdateRotation(CGameObject * target)
{
	CCollider2D* targetCollider2D = target->Collider2D();
	//Collider2D에서 Rotation이 필요한지 모르겠다.
}

void Collider2DDlg::init(CGameObject * _pTarget)
{
}

void Collider2DDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);
	if (_pTarget == nullptr)
	{
		return;
	}

	if (focus == true)
	{
		return;
	}

	UpdatePosition(_pTarget);
	UpdateScale(_pTarget);
}

void Collider2DDlg::OnOK()
{
	focus = false;
	CComponentDlg::OnOK();
}

void Collider2DDlg::OnCancel()
{
}

void Collider2DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editPositionX);
	DDX_Control(pDX, IDC_EDIT2, editPositionY);
	DDX_Control(pDX, IDC_EDIT3, editPositionZ);
	DDX_Control(pDX, IDC_EDIT4, editScaleX);
	DDX_Control(pDX, IDC_EDIT5, editScaleY);
	DDX_Control(pDX, IDC_EDIT6, editScaleZ);
	DDX_Control(pDX, IDC_EDIT7, editRotationX);
	DDX_Control(pDX, IDC_EDIT8, editRotationY);
	DDX_Control(pDX, IDC_EDIT9, editRotationZ);
}


BEGIN_MESSAGE_MAP(Collider2DDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_EDIT1, &Collider2DDlg::OnEnSetfocusEditPositionX)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Collider2DDlg::OnEnKillfocusEditPositionX)
	ON_EN_SETFOCUS(IDC_EDIT2, &Collider2DDlg::OnEnSetfocusEditPositionY)
	ON_EN_KILLFOCUS(IDC_EDIT2, &Collider2DDlg::OnEnKillfocusEditPositionY)
	ON_EN_SETFOCUS(IDC_EDIT3, &Collider2DDlg::OnEnSetfocusEditPositionZ)
	ON_EN_KILLFOCUS(IDC_EDIT3, &Collider2DDlg::OnEnKillfocusEditPositionZ)
	ON_EN_SETFOCUS(IDC_EDIT4, &Collider2DDlg::OnEnSetfocusEditScaleX)
	ON_EN_KILLFOCUS(IDC_EDIT4, &Collider2DDlg::OnEnKillfocusEditScaleX)
	ON_EN_SETFOCUS(IDC_EDIT5, &Collider2DDlg::OnEnSetfocusEditScaleY)
	ON_EN_KILLFOCUS(IDC_EDIT5, &Collider2DDlg::OnEnKillfocusEditScaleY)
	ON_EN_SETFOCUS(IDC_EDIT6, &Collider2DDlg::OnEnSetfocusEditScaleZ)
	ON_EN_KILLFOCUS(IDC_EDIT6, &Collider2DDlg::OnEnKillfocusEditScaleZ)
END_MESSAGE_MAP()


// Collider2DDlg 메시지 처리기


void Collider2DDlg::OnEnSetfocusEditPositionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;

}


void Collider2DDlg::OnEnKillfocusEditPositionX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetOffset();
		CString inputStr;
		editPositionX.GetWindowTextW(inputStr);
		inputVec3.x = static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetOffset(inputVec3);
	}

}


void Collider2DDlg::OnEnSetfocusEditPositionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void Collider2DDlg::OnEnKillfocusEditPositionY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetOffset();
		CString inputStr;
		editPositionY.GetWindowTextW(inputStr);
		inputVec3.y = static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetOffset(inputVec3);
	}
}


void Collider2DDlg::OnEnSetfocusEditPositionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void Collider2DDlg::OnEnKillfocusEditPositionZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetOffset();
		CString inputStr;
		editPositionZ.GetWindowTextW(inputStr);
		inputVec3.z = static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetOffset(inputVec3);
	}
}


void Collider2DDlg::OnEnSetfocusEditScaleX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void Collider2DDlg::OnEnKillfocusEditScaleX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetScale();
		CString inputStr;
		editScaleX.GetWindowTextW(inputStr);
		inputVec3.x = static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetScale(inputVec3);
	}
}


void Collider2DDlg::OnEnSetfocusEditScaleY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void Collider2DDlg::OnEnKillfocusEditScaleY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetScale();
		CString inputStr;
		editScaleY.GetWindowTextW(inputStr);
		inputVec3.y = static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetScale(inputVec3);
	}
}


void Collider2DDlg::OnEnSetfocusEditScaleZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = true;
}


void Collider2DDlg::OnEnKillfocusEditScaleZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	focus = false;
	CGameObject* target = GetTarget();
	if (target != nullptr)
	{
		Vec3 inputVec3 = target->Collider2D()->GetScale();
		CString inputStr;
		editScaleX.GetWindowTextW(inputStr);
		inputVec3.z= static_cast<float>(_wtof(inputStr));
		target->Collider2D()->SetScale(inputVec3);
	}
}
