#pragma once
#include "afxwin.h"


// CDlg13762UpdataConfig �Ի���

class CDlg13762UpdataConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg13762UpdataConfig)

public:
	CDlg13762UpdataConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg13762UpdataConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_3762UPDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_editFile;
	afx_msg void OnBnClickedOk();
	CComboBox m_combBS;
//	CComboBox m_combSX;
	CComboBox m_combZL;
	CEdit m_editFile;
	CEdit m_editFrameSize;
	CStatic m_staticSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpen();
	CButton m_checkDX;
	afx_msg void OnEnChangeEditFile();
};
