#pragma once
#include "afxwin.h"


// DlgExtStaVersion �Ի���

class DlgExtStaVersion : public CDialogEx
{
	DECLARE_DYNAMIC(DlgExtStaVersion)

public:
	DlgExtStaVersion(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgExtStaVersion();

// �Ի�������
	enum { IDD = IDD_DIALOG_EXT_STAVERSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit FileName;
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	BOOL OnInitDialog(void);
	afx_msg void OnBnClickedCancel();
	CEdit FileName1;
	afx_msg void OnBnClickedOk();
};
