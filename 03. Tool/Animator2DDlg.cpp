// Animator2DDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Animator2DDlg.h"
#include "afxdialogex.h"

#include "AddAnimDlg.h"
#include "AddAnimFile.h"

#include <GameObject.h>
#include <Animator2D.h>
#include <Animation2D.h>


// CAnimator2DDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnimator2DDlg, CDialogEx)


CAnimator2DDlg::CAnimator2DDlg(CWnd* pParent /*=nullptr*/)
	: CComponentDlg(IDD_ANIMATOR2DDLG, pParent)
	, m_bRepeat(FALSE)	
{
}

CAnimator2DDlg::~CAnimator2DDlg()
{	
}

void CAnimator2DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbAnimList);
	DDX_Control(pDX, IDC_BUTTON2, m_btnPlay);
	DDX_Check(pDX, IDC_CHECK2, m_bRepeat);
	DDX_Control(pDX, IDC_EDIT1, editMaxFrameCount);
	DDX_Control(pDX, IDC_EDIT2, editNowFrameCount);
	DDX_Control(pDX, IDC_EDIT3, editOffsetX);
	DDX_Control(pDX, IDC_EDIT4, editOffsetY);
	DDX_Control(pDX, IDC_EDIT5, editRepeatStartFrame);
	DDX_Control(pDX, IDC_EDIT6, editRepeatEndFrame);
}


void CAnimator2DDlg::init(CGameObject * _pTarget)
{
	// GameObject 의 Animator2D 컴포넌트로 부터 Animation 목록을 읽어온다.
	SetTarget(_pTarget);
	
	if (nullptr == _pTarget->Animator2D())
		return;

	CAnimator2D* pAnimator = GetTarget()->Animator2D();

	const map<wstring, CAnimation2D*>& mapAnim = pAnimator->GetAnimList();

	for (const auto& pair : mapAnim)
	{
		m_cbAnimList.AddString(pair.first.c_str());
	}

	isFocus = false;
}

// 상시 상태값 체크
void CAnimator2DDlg::Animator2DStateCheck(CGameObject* _pTarget)
{
	SetTarget(_pTarget);

	CAnimation2D* pCurAnim = _pTarget->Animator2D()->GetCurAnim();
	if (nullptr == pCurAnim)
		return;

	// 반복재생 아님, Animation 이 종료됨 
	if (pCurAnim->IsFinish() && !_pTarget->Animator2D()->IsRepeat())
	{
		m_btnPlay.SetWindowTextW(L"▶");
	}


	if (isFocus == true)
	{
		return;
	}

	CString formatStr;
	int maxFrameCount = pCurAnim->GetMaxFrameCount();
	formatStr.Format(L"%d", maxFrameCount);
	editMaxFrameCount.SetWindowTextW(formatStr);

	int nowFrameCount = pCurAnim->GetNowFrameCount() + 1;
	formatStr.Format(L"%d", nowFrameCount);
	editNowFrameCount.SetWindowTextW(formatStr);

	float nowOffsetX = pCurAnim->GetNowFrameData().LTOffset.x;
	formatStr.Format(L"%f", nowOffsetX);
	editOffsetX.SetWindowTextW(formatStr);

	float nowOffsetY = pCurAnim->GetNowFrameData().LTOffset.y;
	formatStr.Format(L"%f", nowOffsetY);
	editOffsetY.SetWindowTextW(formatStr);

	int repeatStartFrame = pCurAnim->GetRepeatStartFrame();
	formatStr.Format(L"%d", repeatStartFrame+1);
	editRepeatStartFrame.SetWindowTextW(formatStr);

	int repeatEndFrame = pCurAnim->GetRepeatEndFrame();
	formatStr.Format(L"%d", repeatEndFrame + 1);
	editRepeatEndFrame.SetWindowTextW(formatStr);
}

void CAnimator2DDlg::update(CGameObject * _pTarget)
{
	SetTarget(_pTarget);

	if (IsCbActive())
		return;
	   	 
	CAnimator2D* pAnimator = GetTarget()->Animator2D();

	// 목록 갱신
	m_cbAnimList.ResetContent();

	const map<wstring, CAnimation2D*>& mapAnim = pAnimator->GetAnimList();
	for (const auto& pair : mapAnim)
	{
		m_cbAnimList.AddString(pair.first.c_str());
	}	

	// 현재 재생중인 애니메이션을 목록에서 선택
	CAnimation2D* pCurAnim = pAnimator->GetCurAnim();

	if (nullptr != pCurAnim)
	{
		CString strCurName = pCurAnim->GetName().c_str();
		int idx = m_cbAnimList.FindString(0, strCurName);
		
		//if(-1 == idx)

		m_cbAnimList.SetCurSel(idx);
	}

}


BEGIN_MESSAGE_MAP(CAnimator2DDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnimator2DDlg::OnBtnPlay)
	ON_BN_CLICKED(IDC_CHECK2, &CAnimator2DDlg::OnBtnRepeat)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAnimator2DDlg::OnCbAnimChange)

	ON_CONTROL_RANGE(CBN_SETFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbSetfocusEdit)
	ON_CONTROL_RANGE(CBN_KILLFOCUS, IDC_COMBO1, IDC_COMBO1, &CComponentDlg::OnCbKillfocusEdit)

	ON_BN_CLICKED(IDC_BUTTON1, &CAnimator2DDlg::OnAddAnimation)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnimator2DDlg::OnBnClickedAddAnimaiotnFileButton)
	ON_EN_CHANGE(IDC_EDIT1, &CAnimator2DDlg::OnEnChangeEdit1)
	ON_EN_SETFOCUS(IDC_EDIT3, &CAnimator2DDlg::OnEnSetfocusEditOffsetX)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CAnimator2DDlg::OnEnKillfocusEditOffsetX)
	ON_EN_SETFOCUS(IDC_EDIT4, &CAnimator2DDlg::OnEnSetfocusEditOffsetY)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CAnimator2DDlg::OnEnKillfocusEditOffsetY)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnimator2DDlg::OnBnClickedButtonNextFrame)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnimator2DDlg::OnBnClickedButtonPrevFrame)
	ON_EN_SETFOCUS(IDC_EDIT5, &CAnimator2DDlg::OnEnSetfocusEditRepeatStartFrame)
	ON_EN_KILLFOCUS(IDC_EDIT5, &CAnimator2DDlg::OnEnKillfocusEditRepeatStartFrame)
	ON_EN_SETFOCUS(IDC_EDIT6, &CAnimator2DDlg::OnEnSetfocusEditRepeatEndFrame)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CAnimator2DDlg::OnEnKillfocusEditRepeatEndFrame)
END_MESSAGE_MAP()


// CAnimator2DDlg 메시지 처리기


void CAnimator2DDlg::OnBtnPlay()
{	
	CAnimation2D* pAnim = GetTarget()->Animator2D()->GetCurAnim();

	OnOK();

	if (nullptr == pAnim)
		return;

	if (pAnim->IsPlay())
	{
		pAnim->Pause();
		m_btnPlay.SetWindowTextW(L"▶");
	}
	else
	{
		GetTarget()->Animator2D()->SetRepeat(m_bRepeat);
		pAnim->Play();
		m_btnPlay.SetWindowTextW(L"∥");
	}	
}

void CAnimator2DDlg::OnBtnRepeat()
{
	UpdateData();

	CAnimation2D* pAnim = GetTarget()->Animator2D()->GetCurAnim();
	if (pAnim->IsPlay())
	{
		GetTarget()->Animator2D()->SetRepeat(m_bRepeat);
	}
}


void CAnimator2DDlg::OnCbAnimChange()
{
	int iIdx = m_cbAnimList.GetCurSel();
	CString str;
	m_cbAnimList.GetLBText(iIdx, str);
	GetTarget()->Animator2D()->PlayAnimation(str.GetBuffer(), m_bRepeat);
	GetTarget()->Animator2D()->Pause();

	m_btnPlay.SetWindowTextW(L"▶");

	CAnimation2D* pCurAnim = GetTarget()->Animator2D()->GetCurAnim();
}


void CAnimator2DDlg::OnAddAnimation()
{
	CAddAnimDlg dlg;
	dlg.SetTargetObject(GetTarget());
	dlg.DoModal();
}


void CAnimator2DDlg::OnBnClickedAddAnimaiotnFileButton()
{
	AddAnimFile dlg;

	CGameObject* targetObject = GetTarget();

	if (targetObject == nullptr)
	{
		assert(false);
	}

	dlg.SetTargetObject(targetObject);
	dlg.DoModal();
}


void CAnimator2DDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAnimator2DDlg::OnEnSetfocusEditOffsetX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CAnimator2DDlg::OnEnKillfocusEditOffsetX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString offsetXFormat;
	editOffsetX.GetWindowTextW(offsetXFormat);
	float offsetX = _wtof(offsetXFormat);
	Vec2 offset = GetTarget()->Animator2D()->GetCurAnim()->GetNowFrameData().LTOffset;
	offset.x = offsetX;
	GetTarget()->Animator2D()->GetCurAnim()->SetNowFrameOffset(offset);

	isFocus = false;
}


void CAnimator2DDlg::OnEnSetfocusEditOffsetY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CAnimator2DDlg::OnEnKillfocusEditOffsetY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString offsetYFormat;
	editOffsetY.GetWindowTextW(offsetYFormat);
	float offsetY = _wtof(offsetYFormat);
	Vec2 offset = GetTarget()->Animator2D()->GetCurAnim()->GetNowFrameData().LTOffset;
	offset.y = offsetY;
	GetTarget()->Animator2D()->GetCurAnim()->SetNowFrameOffset(offset);

	isFocus = false;
}


void CAnimator2DDlg::OnBnClickedButtonNextFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString formatStr;
	editNowFrameCount.GetWindowTextW(formatStr);
	int nowFrameCount = _wtoi(formatStr);
	nowFrameCount += 1;

	editMaxFrameCount.GetWindowTextW(formatStr);
	int maxFrameCount = _wtoi(formatStr);
	if (nowFrameCount > maxFrameCount)
	{
		nowFrameCount = 1;
	}

	GetTarget()->Animator2D()->GetCurAnim()->SetFrm(nowFrameCount-1);
}


void CAnimator2DDlg::OnBnClickedButtonPrevFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString formatStr;
	editNowFrameCount.GetWindowTextW(formatStr);
	int nowFrameCount = _wtoi(formatStr);
	nowFrameCount -= 1;

	editMaxFrameCount.GetWindowTextW(formatStr);
	int maxFrameCount = _wtoi(formatStr);
	if (nowFrameCount < 1)
	{
		nowFrameCount = maxFrameCount;
	}

	GetTarget()->Animator2D()->GetCurAnim()->SetFrm(nowFrameCount - 1);
}


void CAnimator2DDlg::OnEnSetfocusEditRepeatStartFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CAnimator2DDlg::OnEnKillfocusEditRepeatStartFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString repeatStartFrameFormat;
	editRepeatStartFrame.GetWindowTextW(repeatStartFrameFormat);
	int nowRepeatStartFrame = _wtoi(repeatStartFrameFormat);
	GetTarget()->Animator2D()->GetCurAnim()->SetRepeatStartFrame(nowRepeatStartFrame-1);

	isFocus = false;
}


void CAnimator2DDlg::OnEnSetfocusEditRepeatEndFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isFocus = true;
}


void CAnimator2DDlg::OnEnKillfocusEditRepeatEndFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString repeatEndFrameFormat;
	editRepeatEndFrame.GetWindowTextW(repeatEndFrameFormat);
	int nowRepeatEndFrame = _wtoi(repeatEndFrameFormat);
	GetTarget()->Animator2D()->GetCurAnim()->SetRepeatEndFrame(nowRepeatEndFrame - 1);

	isFocus = false;
}
