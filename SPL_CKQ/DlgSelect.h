#pragma once
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"

// DlgSelect �Ի���

class DlgSelect : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSelect)

public:
	DlgSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSelect();

// �Ի�������
	enum { IDD = IDD_DIALOG_NW };
protected:
	void AddData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_NW_GW;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
