#pragma once


#include "MyListCtrl.h"
#include "AccessData.h"
#include "Tools.h"
#include "afxwin.h"
// CCKQViewTabErrMet ������ͼ

class CCKQViewTabErrMet : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewTabErrMet)

protected:
	CCKQViewTabErrMet();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCKQViewTabErrMet();

public:
	enum { IDD = IDD_DIALOG_CKQ_ERR_MET };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CFont m_fontStatic;
	void SetNewFont();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void InsertItemToList(CString strAddre , CString strLoca , CString strState , CString strMAC , CString strSendFrames ,CString strRecvFrames , CString strType);
	CAccessData m_access;
	CTools m_tools;
	HANDLE m_hThreadsend;
	CMyListCtrl m_listData;
	virtual void OnInitialUpdate();
//	afx_msg void OnIdrRbmenuMeterr();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeterrUpdata();
	CStatic m_staticInNet;
	CStatic m_staticUnNet;
	CStatic m_staticUnWhite;
};


