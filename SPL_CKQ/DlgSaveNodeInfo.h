#pragma once
#include "afxwin.h"


// DlgSaveNodeInfo �Ի���

class DlgSaveNodeInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveNodeInfo)

public:
	DlgSaveNodeInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSaveNodeInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_NODEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedOk();
	CEdit FileName;
	virtual BOOL OnInitDialog();
};
