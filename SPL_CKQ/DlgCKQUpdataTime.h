#pragma once


// CDlgCKQUpdataTime �Ի���

class CDlgCKQUpdataTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCKQUpdataTime)

public:
	CDlgCKQUpdataTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCKQUpdataTime();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTime;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
