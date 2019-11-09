// AddAnimDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "AddAnimDlg.h"
#include "afxdialogex.h"

#include <Animator2D.h>
#include <Animation2D.h>
#include <GameObject.h>
#include <PathMgr.h>

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

IMPLEMENT_DYNAMIC(CAddAnimDlg, CDialogEx)

CAddAnimDlg::CAddAnimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDANIMDLG, pParent)
{

}

CAddAnimDlg::~CAddAnimDlg()
{
}

void CAddAnimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editAnimKey);
	DDX_Control(pDX, IDC_EDIT2, m_editTerm);
	DDX_Control(pDX, IDC_EDIT3, m_editFolderPath);
	DDX_Control(pDX, IDC_LIST1, m_ctrlAnimList);
}


BEGIN_MESSAGE_MAP(CAddAnimDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddAnimDlg::OnBtnSelectFolder)

//	ON_WM_KEYDOWN()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CAddAnimDlg::OnLvnKeydown)
END_MESSAGE_MAP()

// pAnimator2D->AddAnimation(L"Player_Down_Walk", pTex, Vec2(0, 260), Vec2(60, 65), 10, 0.08f);
// pAnimator2D->AddAnimation(L"Player_Left_Walk", pTex, Vec2(0, 325), Vec2(60, 65), 10, 0.08f);
// pAnimator2D->AddAnimation(L"Player_Up_Walk", pTex, Vec2(0, 390), Vec2(60, 65), 10, 0.08f);
// pAnimator2D->AddAnimation(L"Player_Down_Walk", pTex, Vec2(0, 260), Vec2(60, 65), 10, 0.08f);

// pAnimator2D->AddAnimation(L"Explosion", L"Texture\\Animation\\Explosion\\", 0.03f);


// CAddAnimDlg 메시지 처리기


void CAddAnimDlg::OnBtnSelectFolder()
{
	//static wchar_t szFilter[] = L"이미지 파일(*.BMP, *.GIF, *.JPG, *PNG) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.jpg;*.gif;*.png |모든파일(*.*)|*.*||";
	//
	//// True 지정한 파일까지의 경로
	//// False 지정한 경로에서 내가 작성한 이름까지의 경로
	//CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	//
	//CString pathName;
	//if (IDOK == dlg.DoModal())
	//{
	//	pathName = dlg.GetPathName();
	//}

	//BROWSEINFO BrInfo;
	//wchar_t szBuffer[512];                                      // 경로저장 버퍼 
	//
	//::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	//::ZeroMemory(szBuffer, 512);
	//
	//BrInfo.hwndOwner = GetSafeHwnd();
	//BrInfo.lpszTitle = L"폴더를 선택하세요";
	//BrInfo.lpfn = BrowseCallbackProc;
	//BrInfo.lParam = (DWORD)CPathMgr::GetResPath();
	//BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	//LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	//
	//::SHGetPathFromIDList(pItemIdList, szBuffer);               // 파일경로 읽어오기
	//CString strFolderPath = szBuffer;

	const wchar_t* pInitPath = CPathMgr::GetResPath();

	CFolderPickerDialog Picker(pInitPath, OFN_FILEMUSTEXIST);

	CString path;
	if (IDOK == Picker.DoModal())
	{
		path = Picker.GetPathName();
		path = CPathMgr::GetRelativePath(path);
		path += L"\\";
		m_editFolderPath.SetWindowTextW(path);
	}
}


void CAddAnimDlg::OnOK()
{
	CString strKey;
	m_editAnimKey.GetWindowTextW(strKey);

	CString strPath;
	m_editFolderPath.GetWindowTextW(strPath);

	CString strTerm;
	m_editTerm.GetWindowTextW(strTerm);
	float fTerm = _wtof(strTerm);

	m_pTarget->Animator2D()->AddAnimation(strKey.GetBuffer(), strPath.GetBuffer(), fTerm);	

	// 리스트 컨트롤 갱신
	m_ctrlAnimList.DeleteAllItems();

	const map<wstring, CAnimation2D*>& mapAnim = m_pTarget->Animator2D()->GetAnimList();

	int i = 0;
	for (const auto& pair : mapAnim)
	{
		m_ctrlAnimList.InsertItem(i, pair.first.c_str());
		++i;
	}
}

BOOL CAddAnimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const map<wstring, CAnimation2D*>& mapAnim = m_pTarget->Animator2D()->GetAnimList();

	int i = 0;
	for (const auto& pair : mapAnim)
	{
		m_ctrlAnimList.InsertItem(i, pair.first.c_str());
		++i;
	}

	return TRUE;  
}


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// 폴더선택 다이얼로그의 초기화가 끝난 경우
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CAddAnimDlg::OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	
	if (pLVKeyDow->wVKey == VK_DELETE)
	{
		CString strKey;

		POSITION pos = m_ctrlAnimList.GetFirstSelectedItemPosition();

		int i = m_ctrlAnimList.GetNextSelectedItem(pos);

		strKey = m_ctrlAnimList.GetItemText(i, 0);

		m_ctrlAnimList.DeleteItem(i);

		m_pTarget->Animator2D()->DeleteAnimation(strKey.GetBuffer());
	}

	*pResult = 0;
}
