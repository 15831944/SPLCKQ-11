#pragma once


// CDlgNetTP �Ի���

class CDlgNetTP : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNetTP)

public:
	CDlgNetTP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNetTP();

// �Ի�������
	enum { IDD = IDD_DIALOG_TP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
