#pragma once
#include "afxwin.h"
#include "CKQViewTabErrMet.h"
#include "CKQViewUpdata.h"
// addmactest �Ի���

class addmactest : public CDialogEx
{
	DECLARE_DYNAMIC(addmactest)

public:
	addmactest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~addmactest();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int n_ChooseDlg;
	CString m_MAC;
	CString m_TYPE;
	CString m_TEI;
	afx_msg void OnBnClickedOk();
	CButton m_ch;
};
