// AddAnimFile.cpp: 구현 파일
//

#include "stdafx.h"
#include "AddAnimFile.h"
#include "afxdialogex.h"

#include <Animator2D.h>
#include <Animation2D.h>
#include <GameObject.h>
#include <PathMgr.h>
#include <ResMgr.h>
#include <Texture.h>
// AddAnimFile 대화 상자

IMPLEMENT_DYNAMIC(AddAnimFile, CDialogEx)

AddAnimFile::AddAnimFile(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDANIMFILEDLG, pParent)
{

}

AddAnimFile::~AddAnimFile()
{
}

void AddAnimFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlAnimList);
	DDX_Control(pDX, IDC_EDIT1, m_editAnimKey);
	DDX_Control(pDX, IDC_EDIT2, m_editTerm);
	DDX_Control(pDX, IDC_EDIT3, m_editFolderPath);
	DDX_Control(pDX, IDC_EDIT4, frameCount);
}


BEGIN_MESSAGE_MAP(AddAnimFile, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddAnimFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &AddAnimFile::OnBnClickedFilePathButton)
END_MESSAGE_MAP()


// AddAnimFile 메시지 처리기


void AddAnimFile::OnBnClickedOk()
{
	CString strKey;
	m_editAnimKey.GetWindowTextW(strKey);

	CString strPath;
	m_editFolderPath.GetWindowTextW(strPath);

	CString strTerm;
	m_editTerm.GetWindowTextW(strTerm);
	float fTerm = _wtof(strTerm);

	CString strFrameCount;
	frameCount.GetWindowTextW(strFrameCount);
	int intFrameCount = _wtoi(strFrameCount);

	CString strFilePath;
	m_editFolderPath.GetWindowTextW(strFilePath);

	CResMgr::GetInst()->Load<CTexture>(strFilePath.GetBuffer(), strFilePath.GetBuffer());

	CResPtr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(strFilePath.GetBuffer());
	float originSizeX = (pTex->GetWidth() / intFrameCount) / 5;
	float originSizeY = pTex->GetHeight() / 5;

	Vec2 lt;
	//lt.x = originSizeX;
	//lt.y = originSizeY;
	lt.x = 0;
	lt.y = 0;

	Vec2 sliceSize;
	sliceSize.x = originSizeX * 3;
	sliceSize.y = originSizeY * 3;
	//sliceSize.x = (pTex->GetWidth() / intFrameCount);
	//sliceSize.y = pTex->GetHeight();

	Vec2 offset;
	//offset.x = 0.f;
	//offset.y = 0.f;
	offset.x = (pTex->GetWidth() / intFrameCount) / 5;
	offset.y = pTex->GetHeight() / 5;

	m_pTarget->Animator2D()->AddAnimation(
		strKey.GetBuffer(),
		pTex,
		lt,
		sliceSize,
		offset,
		intFrameCount,
		fTerm
	);

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

BOOL AddAnimFile::OnInitDialog()
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


void AddAnimFile::OnBnClickedFilePathButton()
{
	static wchar_t szFilter[] = L"이미지 파일(*.BMP, *.GIF, *.JPG, *PNG) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.jpg;*.gif;*.png |모든파일(*.*)|*.*||";
	
	// True 지정한 파일까지의 경로
	// False 지정한 경로에서 내가 작성한 이름까지의 경로
	CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	
	CString pathName;
	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName();
		pathName = CPathMgr::GetRelativePath(pathName);
		//pathName.Delete(pathName.GetLength() - 1, 1);
		m_editFolderPath.SetWindowTextW(pathName);
	}
}
