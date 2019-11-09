#pragma once

#include <resource.h>


class CResInfoDlg : public CDialogEx
{
private:
	CResource*		m_pResource;

public:
	virtual void SetResource(CResource* _pRes) { m_pResource = _pRes; }
	CResource* GetRes() { return m_pResource; }

public:
	CResInfoDlg(UINT _iResID, CWnd* pParent);
	virtual ~CResInfoDlg();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
};
