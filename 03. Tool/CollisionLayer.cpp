// CollisionLayer.cpp: 구현 파일
//

#include "stdafx.h"
#include "CollisionLayer.h"
#include "afxdialogex.h"

#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>
#include <CollisionMgr.h>

// CollisionLayer 대화 상자

IMPLEMENT_DYNAMIC(CollisionLayer, CDialogEx)

CollisionLayer::CollisionLayer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLLISIONLAYERDLG, pParent)
{

}

CollisionLayer::~CollisionLayer()
{
}

void CollisionLayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, collisionLayerList);
	DDX_Control(pDX, IDC_LIST2, checkCollisionLayerList);
}

BOOL CollisionLayer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int insertIndex = 0;
	for (int index = 0; index < MAX_LAYER; index++)
	{
		CLayer* layer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(index);
		if (layer == nullptr)
		{
			continue;
		}

		collisionLayerList.InsertItem(insertIndex, layer->GetName().c_str());
		insertIndex++;
	}

	checkCollisionLayerList.SetExtendedStyle(LVS_EX_CHECKBOXES);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CollisionLayer, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CollisionLayer::OnNMClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CollisionLayer::OnNMClickList2)
END_MESSAGE_MAP()


// CollisionLayer 메시지 처리기


void CollisionLayer::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	if (pNMItemActivate->iItem == -1)
	{
		return;
	}

	checkCollisionLayerList.DeleteAllItems();

	CString standardCollisionLayer = collisionLayerList.GetItemText(pNMItemActivate->iItem, 0);
	clickedCollisionLayerName = standardCollisionLayer;

	int insertIndex = 0;
	for (int index = pNMItemActivate->iItem; index < collisionLayerList.GetItemCount(); index++)
	{
		CString checkCollisionLayer = collisionLayerList.GetItemText(index, 0);
		checkCollisionLayerList.InsertItem(insertIndex, checkCollisionLayer);

		if (CCollisionMgr::GetInst()->IsCollisionLayers(standardCollisionLayer.GetBuffer(), checkCollisionLayer.GetBuffer()))
		{
			checkCollisionLayerList.SetCheck(insertIndex, true);
		}
		else
		{
			checkCollisionLayerList.SetCheck(insertIndex, false);
		}
		insertIndex++;
	}
}


void CollisionLayer::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (pNMItemActivate->iItem == -1)
	{
		return;
	}

	CString checkCollisionLayerName = checkCollisionLayerList.GetItemText(pNMItemActivate->iItem, 0);

	if (checkCollisionLayerList.GetCheck(pNMItemActivate->iItem) == true)
	{
		//to collision uncheck
		checkCollisionLayerList.SetCheck(pNMItemActivate->iItem, false);

		CCollisionMgr::GetInst()->CollisionUnCheck(
			clickedCollisionLayerName.GetBuffer(),
			checkCollisionLayerName.GetBuffer()
		);
	}
	else
	{
		//to collision check
		checkCollisionLayerList.SetCheck(pNMItemActivate->iItem, true);

		CCollisionMgr::GetInst()->CollisionCheck(
			clickedCollisionLayerName.GetBuffer(),
			checkCollisionLayerName.GetBuffer()
		);
	}
}
