#pragma once
#include "afxwin.h"


// CDlgCCOTPchange �Ի���

class CDlgCCOTPchange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCCOTPchange)

public:
	CDlgCCOTPchange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCCOTPchange();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editData;
	afx_msg void OnBnClickedOk();
};
