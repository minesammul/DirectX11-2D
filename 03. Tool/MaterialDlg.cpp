// MaterialDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MaterialDlg.h"
#include "afxdialogex.h"

#include "ListDlg.h"
#include <ResMgr.h>
#include <Shader.h>
// CMaterialDlg 대화 상자

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialogEx)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=nullptr*/)
	: CResInfoDlg(IDD_MTRLDLG, pParent)
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editShaderName);
	DDX_Control(pDX, IDC_LIST1, listShaderParameterType);
	DDX_Control(pDX, IDC_LIST2, listctrlShaderParameterValue);
	DDX_Control(pDX, IDC_LIST3, listctrlShaderTextureParameter);
	DDX_Control(pDX, IDC_EDIT2, editShaderTextureValue);
}

void CMaterialDlg::SetResource(CResource * _pRes)
{
	CResInfoDlg::SetResource(_pRes);

	listShaderParameterType.ResetContent();
	listctrlShaderParameterValue.DeleteAllItems();
	listctrlShaderTextureParameter.DeleteAllItems();

	CResPtr<CShader> pShader = ((CMaterial*)_pRes)->GetShader();
	if (nullptr == pShader)
	{
		m_editShaderName.SetWindowTextW(L"");
		return;
	}
	else
	{
		m_editShaderName.SetWindowTextW(pShader->GetName().c_str());
	}

	editShaderTextureValue.SetWindowTextW(L"");

	vector<tPramInfo> shaderParameterData = pShader->GetParamInfo();
	int searchTypeCount = shaderParameterData.size();
	int insertListShaderTextureIndex = 0;
	int insertListShaderParameterIndex = 0;
	for (int index = 0; index < searchTypeCount; index++)
	{
		if (shaderParameterData[index].eType == SHADER_PARAM::TEX_0 ||
			shaderParameterData[index].eType == SHADER_PARAM::TEX_1 ||
			shaderParameterData[index].eType == SHADER_PARAM::TEX_2 ||
			shaderParameterData[index].eType == SHADER_PARAM::TEX_3
			)
		{
			CString inputTextureStr;
			inputTextureStr.Format(L"%s", shaderParameterData[index].szName);
			listctrlShaderTextureParameter.InsertItem(insertListShaderTextureIndex, inputTextureStr);

			
			switch (shaderParameterData[index].eType)
			{
			case SHADER_PARAM::TEX_0:
				inputTextureStr = L"TEX_0";
				break;
			case SHADER_PARAM::TEX_1:
				inputTextureStr = L"TEX_1";
				break;
			case SHADER_PARAM::TEX_2:
				inputTextureStr = L"TEX_2";
				break;
			case SHADER_PARAM::TEX_3:
				inputTextureStr = L"TEX_3";
				break;
			}

			listctrlShaderTextureParameter.SetItemText(insertListShaderTextureIndex, 1, inputTextureStr);
			
			insertListShaderTextureIndex++;
			continue;
		}

		listShaderParameterType.InsertString(insertListShaderParameterIndex, shaderParameterData[index].szName);
		insertListShaderParameterIndex++;
	}

}

BOOL CMaterialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	listctrlShaderParameterValue.InsertColumn(0, L"Value", LVCFMT_CENTER, 50);
	listctrlShaderParameterValue.InsertColumn(1, L"Parameter", LVCFMT_CENTER, 65);

	listctrlShaderTextureParameter.InsertColumn(0, L"Name", LVCFMT_CENTER, 190);
	listctrlShaderTextureParameter.InsertColumn(1, L"Parameter", LVCFMT_CENTER, 80);
	return 0;
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMaterialDlg::OnSelShader)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMaterialDlg::OnLbnSelchangeList1)
ON_NOTIFY(NM_CLICK, IDC_LIST2, &CMaterialDlg::OnNMClickList2)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST2, &CMaterialDlg::OnLvnEndlabeleditList2)
ON_NOTIFY(NM_CLICK, IDC_LIST3, &CMaterialDlg::OnNMClickList3)
ON_BN_CLICKED(IDC_BUTTON3, &CMaterialDlg::OnBnClickedButtonShaderTextureChange)
END_MESSAGE_MAP()


// CMaterialDlg 메시지 처리기


void CMaterialDlg::OnSelShader()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources(RES_TYPE::SHADER);

	vector<CString> vecFileName;
	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecFileName.push_back(CPathMgr::GetFileName(pair.second->GetName().c_str()));
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Shader", vecFileName);
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();
		CResPtr<CShader> pShader = CResMgr::GetInst()->FindRes<CShader>(strSelect.GetBuffer());

		CResPtr<CMaterial> pMtrl = (CMaterial*)GetRes();
		pMtrl->SetShader(pShader);

		if (nullptr == pShader)
			m_editShaderName.SetWindowTextW(L"");
		else
			m_editShaderName.SetWindowTextW(pShader->GetName().c_str());
	}
}


void CMaterialDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	   
	int selectIndex = listShaderParameterType.GetCurSel();

	if (selectIndex == -1)
	{
		return;
	}

	CString selectItemName;
	listShaderParameterType.GetText(selectIndex, selectItemName);

	CResPtr<CShader> pShader = ((CMaterial*)CResInfoDlg::GetRes())->GetShader();
	vector<tPramInfo> selectParameter = pShader->GetParamInfo();
	tPramInfo selectParameterData;
	for (UINT index = 0; index < selectParameter.size(); index++)
	{
		if (selectItemName.Compare(selectParameter[index].szName) == 0)
		{
			selectParameterData = selectParameter[index];
			break;
		}
	}

	listctrlShaderParameterValue.DeleteAllItems();
	//tShaderParam

	CString parameterName = L"";
	int paramterValueCount = 0;


	bool isFloat = true;
	switch (selectParameterData.eType)
	{
	case SHADER_PARAM::INT_0:
		parameterName = L"INT_0";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_1:
		parameterName = L"INT_1";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_2:
		parameterName = L"INT_2";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::INT_3:
		parameterName = L"INT_3";
		paramterValueCount = 1;
		isFloat = false;
		break;
	case SHADER_PARAM::FLOAT_0:
		parameterName = L"FLOAT_0";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_1:
		parameterName = L"FLOAT_1";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_2:
		parameterName = L"FLOAT_2";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::FLOAT_3:
		parameterName = L"FLOAT_3";
		paramterValueCount = 1;
		break;
	case SHADER_PARAM::VEC2_0:
		parameterName = L"VEC2_0";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_1:
		parameterName = L"VEC2_1";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_2:
		parameterName = L"VEC2_2";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC2_3:
		parameterName = L"VEC2_3";
		paramterValueCount = 2;
		break;
	case SHADER_PARAM::VEC4_0:
		parameterName = L"VEC4_0";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_1:
		parameterName = L"VEC4_1";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_2:
		parameterName = L"VEC4_2";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::VEC4_3:
		parameterName = L"VEC4_3";
		paramterValueCount = 4;
		break;
	case SHADER_PARAM::MAT_0:
		parameterName = L"MAT_0";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_1:
		parameterName = L"MAT_1";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_2:
		parameterName = L"MAT_2";
		paramterValueCount = 16;
		break;
	case SHADER_PARAM::MAT_3:
		parameterName = L"MAT_3";
		paramterValueCount = 16;
		break;
	default:
		break;
	}


	if (isFloat == true)
	{
		vector<float> inputShaderParameterValue;
		int iIdx;
		switch (selectParameterData.eType)
		{
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::FLOAT_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrFloat[iIdx]);
			//inputShaderParameterValueStr.Format(L"%f", ((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrFloat[iIdx]);
			break;
		case SHADER_PARAM::VEC2_0:
		case SHADER_PARAM::VEC2_1:
		case SHADER_PARAM::VEC2_2:
		case SHADER_PARAM::VEC2_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC2_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec2[iIdx].x);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec2[iIdx].y);
			//m_param.arrVec2[iIdx] = *((Vec2*)_pSrc);
			break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC4_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].x);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].y);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].z);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrVec4[iIdx].w);
			//m_param.arrVec4[iIdx] = *((Vec4*)_pSrc);
			break;
		case SHADER_PARAM::MAT_0:
		case SHADER_PARAM::MAT_1:
		case SHADER_PARAM::MAT_2:
		case SHADER_PARAM::MAT_3:
			iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::MAT_0;
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._11);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._12);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._13);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._14);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._21);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._22);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._23);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._24);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._31);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._32);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._33);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._34);

			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._41);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._42);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._43);
			inputShaderParameterValue.push_back(((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrMat[iIdx]._44);

			//m_param.arrMat[iIdx] = *((Matrix*)_pSrc);
			break;
		}

		for (UINT index = 0; index < inputShaderParameterValue.size(); index++)
		{
			CString inputShaderParameterValueStr;
			inputShaderParameterValueStr.Format(L"%f", inputShaderParameterValue[index]);
			//listctrlShaderParameterValue.SetItemText(index, 1, inputShaderParameterValueStr);
			listctrlShaderParameterValue.InsertItem(index, inputShaderParameterValueStr);
		}
	}
	else
	{
		int iIdx = (UINT)selectParameterData.eType - (UINT)SHADER_PARAM::INT_0;
		CString inputShaderParameterValueStr;
		inputShaderParameterValueStr.Format(L"%d", ((CMaterial*)CResInfoDlg::GetRes())->GetParamData().arrInt[iIdx]);
		//listctrlShaderParameterValue.SetItemText(0, 1, inputShaderParameterValueStr);
		listctrlShaderParameterValue.InsertItem(0, inputShaderParameterValueStr);
	}

	//
	for (int index = 0; index < paramterValueCount; index++)
	{
		CString inputParameterName = parameterName;
		CString inputParameterNumber;

		int digits10 = 0;
		int digits1 = 0;
		if (index != 0)
		{
			digits10 = (index) / 4;
			digits1 = (index - (digits10*4)) % 4;
		}

		inputParameterNumber.Format(L" %d%d", digits10, digits1);
		inputParameterName += inputParameterNumber;
		listctrlShaderParameterValue.SetItemText(index, 1, inputParameterName);
	}

	
}


void CMaterialDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO hitItem;
	hitItem.pt = pNMItemActivate->ptAction;
	listctrlShaderParameterValue.HitTest(&hitItem);
	if (hitItem.iItem != -1)
	{
		listctrlShaderParameterValue.EditLabel(hitItem.iItem);
	}
	*pResult = 0;
}



void CMaterialDlg::OnLvnEndlabeleditList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selectIndex = listShaderParameterType.GetCurSel();

	if (selectIndex == -1)
	{
		return;
	}

	CString selectItemName;
	listShaderParameterType.GetText(selectIndex, selectItemName);

	CResPtr<CShader> pShader = ((CMaterial*)CResInfoDlg::GetRes())->GetShader();
	vector<tPramInfo> selectParameter = pShader->GetParamInfo();
	tPramInfo selectParameterData;
	for (UINT index = 0; index < selectParameter.size(); index++)
	{
		if (selectItemName.Compare(selectParameter[index].szName) == 0)
		{
			selectParameterData = selectParameter[index];
			break;
		}
	}


	CString strInputData;
	listctrlShaderParameterValue.GetEditControl()->GetWindowTextW(strInputData);

	int selectParameterValueIndex = pDispInfo->item.iItem;


	switch (selectParameterData.eType)
	{
	case SHADER_PARAM::INT_0:
	case SHADER_PARAM::INT_1:
	case SHADER_PARAM::INT_2:
	case SHADER_PARAM::INT_3:
	{
		int inputData = _wtoi(strInputData);
		((CMaterial*)CResInfoDlg::GetRes())->SetData(selectParameterData.eType, &inputData);
	}
		break;
	case SHADER_PARAM::FLOAT_0:
	case SHADER_PARAM::FLOAT_1:
	case SHADER_PARAM::FLOAT_2:
	case SHADER_PARAM::FLOAT_3:
	{
		float inputData = static_cast<float>(_wtof(strInputData));
		((CMaterial*)CResInfoDlg::GetRes())->SetData(selectParameterData.eType, &inputData);
	}
		break;
	case SHADER_PARAM::VEC2_0:
	case SHADER_PARAM::VEC2_1:
	case SHADER_PARAM::VEC2_2:
	case SHADER_PARAM::VEC2_3:
	{
		tShaderParam paramData = ((CMaterial*)CResInfoDlg::GetRes())->GetParamData();
		Vec2 inputData = paramData.arrVec2[(UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC2_0];

		if (selectParameterValueIndex == 0)
		{
			
			inputData.x = static_cast<float>(_wtof(strInputData));
		}
		else
		{
			inputData.y = static_cast<float>(_wtof(strInputData));
		}

		((CMaterial*)CResInfoDlg::GetRes())->SetData(selectParameterData.eType, &inputData);
	}
		break;
	case SHADER_PARAM::VEC4_0:
	case SHADER_PARAM::VEC4_1:
	case SHADER_PARAM::VEC4_2:
	case SHADER_PARAM::VEC4_3:
	{
		tShaderParam paramData = ((CMaterial*)CResInfoDlg::GetRes())->GetParamData();
		Vec4 inputData = paramData.arrVec4[(UINT)selectParameterData.eType - (UINT)SHADER_PARAM::VEC4_0];

		if (selectParameterValueIndex == 0)
		{
			inputData.x = static_cast<float>(_wtof(strInputData));
		}
		else if(selectParameterValueIndex == 1)
		{
			inputData.y = static_cast<float>(_wtof(strInputData));
		}
		else if (selectParameterValueIndex == 2)
		{
			inputData.z = static_cast<float>(_wtof(strInputData));
		}
		else if (selectParameterValueIndex == 3)
		{
			inputData.w = static_cast<float>(_wtof(strInputData));
		}

		((CMaterial*)CResInfoDlg::GetRes())->SetData(selectParameterData.eType, &inputData);
	}
		break;
	case SHADER_PARAM::MAT_0:
	case SHADER_PARAM::MAT_1:
	case SHADER_PARAM::MAT_2:
	case SHADER_PARAM::MAT_3:
	{
		tShaderParam paramData = ((CMaterial*)CResInfoDlg::GetRes())->GetParamData();
		Matrix inputData = paramData.arrMat[(UINT)selectParameterData.eType - (UINT)SHADER_PARAM::MAT_0];

		int digit10 = 0;
		if (selectParameterValueIndex != 0)
		{
			int digit10 = selectParameterValueIndex / 4;
		}
		int digit1 = selectParameterValueIndex % 4;

		inputData.m[digit10][digit1] = static_cast<float>(_wtof(strInputData));

		((CMaterial*)CResInfoDlg::GetRes())->SetData(selectParameterData.eType, &inputData);
	}
		break;
	}

	OnLbnSelchangeList1();
	*pResult = 0;
}


void CMaterialDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO hitItem;
	hitItem.pt = pNMItemActivate->ptAction;
	listctrlShaderTextureParameter.HitTest(&hitItem);
	if (hitItem.iItem != -1)
	{
		CString inputStr;
		CResPtr<CTexture>* m_arrTexParam = ((CMaterial*)CResInfoDlg::GetRes())->GetTexData();
		inputStr = m_arrTexParam[hitItem.iItem]->GetName().c_str();
		editShaderTextureValue.SetWindowTextW(inputStr);
	}

	*pResult = 0;
}


void CMaterialDlg::OnBnClickedButtonShaderTextureChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	const map<wstring, CResource*>& mapRes = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

	vector<CString> vecFileName;
	vector<CString> vecResName;

	for (const auto& pair : mapRes)
	{
		vecFileName.push_back(CPathMgr::GetFileName(pair.second->GetName().c_str()));
		vecResName.push_back(pair.second->GetName().c_str());
	}

	CListDlg dlg(L"Texture", vecResName);
	int iRet = dlg.DoModal();

	if (IDOK == iRet)
	{
		CString strSelect = dlg.GetSelectItem();
		CResPtr<CTexture> pTexture = CResMgr::GetInst()->FindRes<CTexture>(strSelect.GetBuffer());

		listctrlShaderTextureParameter.GetSelectionMark();
		SHADER_PARAM eType = (SHADER_PARAM)(listctrlShaderTextureParameter.GetSelectionMark() + (int)SHADER_PARAM::TEX_0);
		((CMaterial*)CResInfoDlg::GetRes())->SetData(eType, &pTexture);

		editShaderTextureValue.SetWindowTextW(strSelect);
	}
}
