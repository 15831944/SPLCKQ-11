#pragma once
#include "afxwin.h"


// DlgSaveDebugInfo �Ի���

class DlgSaveDebugInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveDebugInfo)

public:
	DlgSaveDebugInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSaveDebugInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEBUGINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit FileName;
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedOk();
	BOOL OnInitDialog(void);
};
