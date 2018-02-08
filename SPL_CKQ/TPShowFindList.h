#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Tools.h"

// CTPShowFindList �Ի���

class CTPShowFindList : public CDialogEx
{
	DECLARE_DYNAMIC(CTPShowFindList)

public:
	CTPShowFindList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTPShowFindList();

// �Ի�������
	enum { IDD = IDD_DIALOG_FINDLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTools m_tools;
	CRect m_cRect;
	void SetTPdataToAccess(CString strTPdata);
	void KongjianSize(int nID, int cx, int cy, bool bComb = false);
	CStatic m_staticPMessage;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_listFindList;
	CListCtrl m_listTPList;
};
