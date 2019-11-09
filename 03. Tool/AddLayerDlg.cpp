// AddLayerDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "AddLayerDlg.h"
#include "afxdialogex.h"

#include <SceneMgr.h>
#include <Scene.h>
#include <Layer.h>


// AddLayerDlg 대화 상자

IMPLEMENT_DYNAMIC(AddLayerDlg, CDialogEx)

AddLayerDlg::AddLayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDLAYERDLG, pParent)
{

}

AddLayerDlg::~AddLayerDlg()
{
}

BOOL AddLayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//int insertIndex = 0;
	for (int index = 0; index < MAX_LAYER; index++)
	{
		CLayer* layer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(index);
		if (layer == nullptr)
		{
			continue;
		}

		listboxExistLayer.AddString(layer->GetName().c_str());

		//collisionLayerList.InsertItem(insertIndex, layer->GetName().c_str());
		//insertIndex++;
	}

	return TRUE;
}

void AddLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listboxExistLayer);
	DDX_Control(pDX, IDC_EDIT1, editAddLayerName);
}


BEGIN_MESSAGE_MAP(AddLayerDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddLayerDlg::OnBnClickedOkAddLayer)
END_MESSAGE_MAP()


// AddLayerDlg 메시지 처리기


void AddLayerDlg::OnBnClickedOkAddLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();

	CString inputStr;
	editAddLayerName.GetWindowTextW(inputStr);

	for (int index = 0; index < MAX_LAYER; index++)
	{
		CLayer* layer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(index);
		if (layer == nullptr)
		{
			CSceneMgr::GetInst()->GetCurScene()->AddLayer(inputStr.GetBuffer(), index);
			break;
		}
	}

}
