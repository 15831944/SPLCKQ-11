#pragma once
#include "afxwin.h"


// SaveFileName �Ի���

class SaveFileName : public CDialogEx
{
	DECLARE_DYNAMIC(SaveFileName)

public:
	SaveFileName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SaveFileName();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_savefilename;
};
