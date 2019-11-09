// ResourceDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ResourceDlg.h"
#include "afxdialogex.h"
#include "ComponentView.h"
#include "MainFrm.h"

#include <ResMgr.h>
#include <PathMgr.h>
// ResourceDlg 대화 상자

IMPLEMENT_DYNAMIC(ResourceDlg, CDialogEx)

ResourceDlg::ResourceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESOURCEDLG, pParent),
	m_bInit(false)
{

}

ResourceDlg::~ResourceDlg()
{
}

void ResourceDlg::init()
{
	CString strContent = CPathMgr::GetResPath();

	LoadResource(strContent);

	Renew();
}

void ResourceDlg::Renew()
{
	m_ctrlTree.DeleteAllItems();

	// 항목 추가
	HTREEITEM arrItem[(UINT)RES_TYPE::END] = {
		AddItem(L"Material", nullptr, 0, TVI_LAST)
		, AddItem(L"Prefab", nullptr, 0, TVI_LAST)
		, AddItem(L"Mesh", nullptr, 0, TVI_LAST)
		, AddItem(L"Shader", nullptr, 0, TVI_LAST)
		, AddItem(L"Texture", nullptr, 0, TVI_LAST)
		, AddItem(L"Sound", nullptr, 0, TVI_LAST)
	};

	// ResMgr 에서 현재 로딩되어있는 리소스 목록을 가져온다.
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		const map<wstring, CResource*>& map = CResMgr::GetInst()->GetResources(RES_TYPE(i));

		for (const auto& pair : map)
		{
			CString strName = CPathMgr::GetFileName(pair.first.c_str());
			AddItem(strName, arrItem[i], (DWORD_PTR)pair.second, TVI_SORT);
		}
	}
}

void ResourceDlg::LoadResource(CString _strFolderPath)
{
	wstring strFolderPath = _strFolderPath + L"\\*.*";

	WIN32_FIND_DATA tData = {};
	HANDLE h = (HANDLE)FindFirstFile(strFolderPath.c_str(), &tData);
	UINT err = GetLastError();

	while (true)
	{
		if ((FILE_ATTRIBUTE_DIRECTORY & tData.dwFileAttributes))
		{
			if (wcscmp(tData.cFileName, L".") && wcscmp(tData.cFileName, L".."))
			{
				wstring temp = _strFolderPath + tData.cFileName;
				temp += L'\\';
				LoadResource(temp.c_str());
			}
		}
		else
		{
			const wchar_t* pExt = CPathMgr::GetExt(tData.cFileName);
			wstring strPath = _strFolderPath + tData.cFileName;
			wstring strKey = CPathMgr::GetRelativePath(strPath.c_str());

			if (!wcscmp(pExt, L".png")
				|| !wcscmp(pExt, L".bmp")
				|| !wcscmp(pExt, L".jpg")
				|| !wcscmp(pExt, L".jpeg"))
			{
				CResMgr::GetInst()->Load<CTexture>(strKey, strKey);
			}
			else if (!wcscmp(pExt, L".mp3")
				|| !wcscmp(pExt, L".ogg")
				|| !wcscmp(pExt, L".wav"))
			{
				CResMgr::GetInst()->Load<CSound>(strKey, strKey);
			}
			else if (!wcscmp(pExt, L".mtrl"))
			{
				CResMgr::GetInst()->Load<CMaterial>(strKey, strKey);
			}
			else if (!wcscmp(pExt, L".mdat"))
			{
				//CResMgr::GetInst()->Load<CMeshData>(strKey, strPath);
			}
			/*else if (!wcscmp(pExt, L".pref"))
			{
				CResMgr::GetInst()->Load<CPrefab>(strKey, strKey);
			}*/
		}

		if (false == FindNextFile(h, &tData))
		{
			err = GetLastError();
			break;
		}
	}
}

HTREEITEM ResourceDlg::AddItem(CString _str, HTREEITEM _hParent, DWORD_PTR _dwData, HTREEITEM _hSortop)
{
	TVINSERTSTRUCT tInsert = {};

	tInsert.hParent = _hParent;
	tInsert.hInsertAfter = _hSortop;
	tInsert.item.pszText = _str.GetBuffer();
	tInsert.item.mask = TVIF_TEXT;

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tInsert);
	m_ctrlTree.SetItemData(hItem, _dwData);

	return hItem;
}

void ResourceDlg::MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// 아이템 정보를 얻는다.
	wchar_t szName[255] = {};

	TV_ITEMW item = {};

	item.hItem = _hSrcItem;
	item.pszText = szName;
	item.cchTextMax = 255;
	item.mask = TVIF_TEXT | TVIF_HANDLE;

	m_ctrlTree.GetItem(&item);

	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	// 얻어온 정보로 목적지의 자식으로 넣는다.
	HTREEITEM hCopyItem = AddItem(szName, _hDestItem, dwData, TVI_SORT);

	vector<HTREEITEM> vecChild;
	GetChildItem(_hSrcItem, vecChild);

	for (UINT i = 0; i < vecChild.size(); ++i)
	{
		MoveItem(vecChild[i], hCopyItem);
	}

	// 원본 아이템을 삭제한다.
	m_ctrlTree.DeleteItem(_hSrcItem);

	m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
}

void ResourceDlg::GetChildItem(HTREEITEM _hItem, vector<HTREEITEM>& _vecChild)
{
	// Item 에 자식이 없으면 리턴
	if (!m_ctrlTree.ItemHasChildren(_hItem))
		return;

	HTREEITEM hChildItem = m_ctrlTree.GetChildItem(_hItem);
	_vecChild.push_back(hChildItem);

	while (true)
	{
		hChildItem = m_ctrlTree.GetNextSiblingItem(hChildItem);

		if (nullptr == hChildItem)
			break;

		_vecChild.push_back(hChildItem);
	}
}

void ResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);

	m_bInit = true;
}

void ResourceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_bInit)
	{
		// Tree Control Size 를 Dialog Size 로 맞춘다.
		m_ctrlTree.SetWindowPos(nullptr, 0, 0, cx, cy, 0);
	}
}


BEGIN_MESSAGE_MAP(ResourceDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &ResourceDlg::OnTvnBeginlabeleditTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &ResourceDlg::OnTvnEndlabeleditTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &ResourceDlg::OnNMClickTree1)
END_MESSAGE_MAP()


// ResourceDlg 메시지 처리기


void ResourceDlg::OnOK()
{

}


void ResourceDlg::OnCancel()
{

}


void ResourceDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}


void ResourceDlg::OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	if (m_ctrlTree.GetParentItem(pTVDispInfo->item.hItem))
	{
		*pResult = 0;
	}
	else
	{
		*pResult = 1;
	}

}


void ResourceDlg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString itemName = m_ctrlTree.GetItemText(pTVDispInfo->item.hItem);
	CString changeItemName = pTVDispInfo->item.pszText;

	CResource* pResource = (CResource*)m_ctrlTree.GetItemData(pTVDispInfo->item.hItem);
	pResource->SetName(changeItemName.GetBuffer());

	m_ctrlTree.SetItemText(pTVDispInfo->item.hItem, changeItemName);

	*pResult = 0;
}


void ResourceDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//POINT pt;
	//::GetCursorPos(&pt);
	//m_ctrlTree.ScreenToClient(&pt);

	//HTREEITEM hTargetItem = m_ctrlTree.HitTest(pt);

	//// 부모아이템은 리소스가 아니기 때문에 예외처리
	//if (nullptr == m_ctrlTree.GetParentItem(hTargetItem))
	//{
	//	pResult = 0;
	//	return;
	//}

	//if (nullptr != hTargetItem)
	//{
	//	CResource* pResource = (CResource*)m_ctrlTree.GetItemData(hTargetItem);

	//	// ComponentView 에 알린다.
	//	CComponentView* pComView = (CComponentView*)((CMainFrame*)AfxGetMainWnd())->GetComView();
	//	pComView->SetResoure(pResource);
	//}

	POINT pt;
	::GetCursorPos(&pt);
	m_ctrlTree.ScreenToClient(&pt);

	HTREEITEM selectItem = m_ctrlTree.HitTest(pt);
	

	if (selectItem == nullptr)
	{
		*pResult = 0;
		return;
	}


	if (m_ctrlTree.GetParentItem(selectItem) == nullptr)
	{
		*pResult = 0;
		return;
	}

	CResource* pResource = (CResource*)m_ctrlTree.GetItemData(selectItem);

	// ComponentView 에 알린다.
	CComponentView* pComView = (CComponentView*)((CMainFrame*)AfxGetMainWnd())->GetComView();
	pComView->SetResoure(pResource);


	*pResult = 0;
}



