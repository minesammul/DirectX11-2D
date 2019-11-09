#include "stdafx.h"
#include "ResInfoDlg.h"


CResInfoDlg::CResInfoDlg(UINT _iResID, CWnd* _pParent)
	: CDialogEx(_iResID, _pParent)
	, m_pResource(nullptr)
{
}


CResInfoDlg::~CResInfoDlg()
{
}


void CResInfoDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CResInfoDlg::OnOK() {}
void CResInfoDlg::OnCancel() {}