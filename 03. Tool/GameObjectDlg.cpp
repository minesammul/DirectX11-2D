// GameObjectDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "GameObjectDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ComponentView.h"

#include <EventMgr.h>
#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>
#include <GameObject.h>
#include <ResPtr.h>
#include <ResMgr.h>
#include <Prefab.h>


// CGameObjectDlg 대화 상자

IMPLEMENT_DYNAMIC(CGameObjectDlg, CDialogEx)


CGameObjectDlg::CGameObjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOBJECTDLG, pParent)
	, m_hDragItem(nullptr)
	, m_bInit(false)	
{
}

CGameObjectDlg::~CGameObjectDlg()
{
}

void CGameObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);

	m_bInit = true;
}

void CGameObjectDlg::init()
{
	// Scene 에서 GameObject 정보를 가져와서
	// TreeControl 에 추가한다.
	m_ctrlTree.DeleteAllItems();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurScene->GetLayer(i);

		if (nullptr == pLayer)
			continue;

		const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

		for (UINT i = 0; i < vecParentObj.size(); ++i)
		{
			AddGameObject(vecParentObj[i], nullptr);			
		}
	}
}

void CGameObjectDlg::AddGameObject(CGameObject * _pObject, HTREEITEM _hParent)
{
	HTREEITEM hItem = AddItem(_pObject->GetName().c_str(), _hParent, (DWORD_PTR)_pObject);
	
	const vector<CGameObject*>& vecChild = _pObject->GetChild();

	for (UINT i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(vecChild[i], hItem);
	}
}

HTREEITEM CGameObjectDlg::AddItem(CString _str, HTREEITEM _hParent, DWORD_PTR _dwData)
{
	TVINSERTSTRUCT tInsert = {};

	tInsert.hParent = _hParent;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.pszText = _str.GetBuffer();
	tInsert.item.mask = TVIF_TEXT;

	
	HTREEITEM hItem = m_ctrlTree.InsertItem(&tInsert);
	m_ctrlTree.SetItemData(hItem, _dwData);

	return hItem;
}

void CGameObjectDlg::MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
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
	HTREEITEM hCopyItem = AddItem(szName, _hDestItem, dwData);

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

void CGameObjectDlg::GetChildItem(HTREEITEM _hItem, vector<HTREEITEM>& _vecChild)
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


BEGIN_MESSAGE_MAP(CGameObjectDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CGameObjectDlg::OnTvnSelchangedTree)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CGameObjectDlg::OnTvnBegindrag)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &CGameObjectDlg::OnTvnBeginlabeleditTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CGameObjectDlg::OnTvnEndlabeleditTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CGameObjectDlg::OnNMRClickTreeCreatePrefab)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE1, &CGameObjectDlg::OnTvnKeydownTreeDeleteObject)
END_MESSAGE_MAP()


// CGameObjectDlg 메시지 처리기


void CGameObjectDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;

	CDialogEx::PostNcDestroy();
}


void CGameObjectDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CGameObjectDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CGameObjectDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_bInit)
	{
		// Tree Control Size 를 Dialog Size 로 맞춘다.
		m_ctrlTree.SetWindowPos(nullptr, 0, 0, cx, cy, 0);
	}
}

BOOL CGameObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return TRUE;  
}


void CGameObjectDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	CGameObject* pTargetObj = (CGameObject*)m_ctrlTree.GetItemData(pNMTreeView->itemNew.hItem);

	CComponentView* pComView = (CComponentView*) ((CMainFrame*)AfxGetMainWnd())->GetComView();

	pComView->SetTarget(pTargetObj);
	pComView->init();

	*pResult = 0;
}

void CGameObjectDlg::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	SetCapture();

	// 드래그 시작한 Item Handle
	m_hDragItem = pNMTreeView->itemNew.hItem;


	*pResult = 0;
}

void CGameObjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nullptr != m_hDragItem)
	{
		// 마우스 좌표를 TreeContrl 기준 좌표로 변경
		::ClientToScreen(m_hWnd, &point);
		m_ctrlTree.ScreenToClient(&point);
		
		// 현재 마우스 좌표에 있는 아이템을 드래드 드롭 타겟으로 설정
		m_hTargetItem = m_ctrlTree.HitTest(point);

		if (nullptr != m_hTargetItem)
		{
			m_ctrlTree.SelectDropTarget(m_hTargetItem);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CGameObjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	ReleaseCapture();

	// 드래그, 타겟 아이템이 없는 경우
	if (nullptr == m_hDragItem)
	{
		CDialogEx::OnLButtonUp(nFlags, point);
		return;
	}

	// 변경되는 아이템의 관계에 대응하는 GameObject 들의 실제 관계도 변경되어야 한다.
	
	// 예외처리
	// 1. 자기 자신의 자식으로 들어가는 경우
	// 2. 부모가 자식 아이템의 자식으로 들어가는 경우

	CGameObject* pSrcObj = (CGameObject*)m_ctrlTree.GetItemData(m_hDragItem);
	CGameObject* pDestObj = nullptr;

	if(nullptr != m_hTargetItem)
		pDestObj = (CGameObject*)m_ctrlTree.GetItemData(m_hTargetItem);

	// 목적지가 가장 밖이다(최상위 부모오브젝트로 만든다.)
	if (nullptr == pDestObj )
	{
		if (nullptr != pSrcObj->GetParent())
		{
			tEvent event{};
			event.eType = EVENT_TYPE::CLEAR_PARANT;
			event.lParam = (DWORD_PTR)pSrcObj;
			CEventMgr::GetInst()->AddEvent(event);

			MoveItem(m_hDragItem, m_hTargetItem);
		}
	}
	else // 목적지가 있다.
	{
		// 예외가 발생하지 않은 경우에만 드래그 드롭
		if (m_hDragItem != m_hTargetItem && !pDestObj->IsAncestor(pSrcObj))
		{
			MoveItem(m_hDragItem, m_hTargetItem);
			pDestObj->AddChild(pSrcObj);
		}
	}
		
	m_hTargetItem = nullptr;
	m_hDragItem = nullptr;
	m_ctrlTree.SelectDropTarget(nullptr);	

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameObjectDlg::OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CGameObjectDlg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString changeObjectName = pTVDispInfo->item.pszText;

	CGameObject* selectObject = (CGameObject*)m_ctrlTree.GetItemData(pTVDispInfo->item.hItem);

	vector<CGameObject*> changeObject;

	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(selectObject->GetName(), changeObject);

	changeObject[0]->SetName(changeObjectName.GetBuffer());

	init();

	*pResult = 0;
}


void CGameObjectDlg::OnNMRClickTreeCreatePrefab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
		POINT pt;
	::GetCursorPos(&pt);
	m_ctrlTree.ScreenToClient(&pt);

	HTREEITEM selectItem = m_ctrlTree.HitTest(pt);
	*/
	POINT pt;
	::GetCursorPos(&pt);

	m_ctrlTree.ScreenToClient(&pt);

	HTREEITEM selectItem = m_ctrlTree.HitTest(pt);
	
	if (selectItem == nullptr)
	{
		return;
	}

	CString itemText = m_ctrlTree.GetItemText(selectItem);
	
	vector<CGameObject*> prefabTargetObject;
	CSceneMgr::GetInst()->FindGameObject(itemText.GetBuffer(), prefabTargetObject);

	CResPtr<CPrefab> prefab = new CPrefab(prefabTargetObject[0]);
	prefab->SetName(itemText.GetBuffer());

	//CResMgr::GetInst()->AddRes<CPrefab>(prefabTargetObject[0]->GetName(), prefab);

	prefab->Save();

	*pResult = 0;
}


void CGameObjectDlg::OnTvnKeydownTreeDeleteObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (pTVKeyDown->wVKey == VK_DELETE)
	{
		HTREEITEM selectedItem = m_ctrlTree.GetSelectedItem();
		if (selectedItem != nullptr)
		{
			CString selectedItemName = m_ctrlTree.GetItemText(selectedItem);
			CGameObject* selectedGameObject = (CGameObject*)m_ctrlTree.GetItemData(selectedItem);

			tEvent e = {};
			e.eType = EVENT_TYPE::DELETE_OBJECT;
			e.lParam = (INT_PTR)selectedGameObject;
			CEventMgr::GetInst()->AddEvent(e);

			m_ctrlTree.DeleteItem(selectedItem);
		}
	}
	
	*pResult = 0;
}
