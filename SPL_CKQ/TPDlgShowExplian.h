#pragma once
#include "afxwin.h"


// CTPDlgShowExplian �Ի���

class CTPDlgShowExplian : public CDialogEx
{
	DECLARE_DYNAMIC(CTPDlgShowExplian)

public:
	CTPDlgShowExplian(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTPDlgShowExplian();

// �Ի�������
	enum { IDD = IDD_DIALOG_TPSHOW_EXPLIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void GetNumb(int * nNumb);
	int m_nList[10];
	CBrush m_BrushAll[10];
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CStatic m_staticCCO;
	CStatic m_staticUCCO;
	CStatic m_staticSTA;
	CStatic m_staticUSTA;
	CStatic m_staticPCO;
	CStatic m_staticOUT;
};
