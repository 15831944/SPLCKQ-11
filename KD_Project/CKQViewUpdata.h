#pragma once

#include "MyListCtrl.h"
#include "afxcmn.h"
#include "Tools.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
// CCKQViewUpdata ������ͼ

class CCKQViewUpdata : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewUpdata)

protected:
	CCKQViewUpdata();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCKQViewUpdata();

public:
	enum { IDD = IDD_DIALOG_CKQ_UPDATA };
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
	int m_nDataLong , m_nYU , m_nCHU;
	CAccessData m_accessData;
	HANDLE m_hThreadsend;
	CStringList m_listStrShengjiData;//���������б�
	void SetUpdataListData();
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu = TRUE);
//#ifdef _STD_CSG  //������׼
	int m_FileSize, m_NrOfSectors;
//#endif
public:
	CTools m_tools;
	CMyListCtrl m_listData;
	afx_msg void OnBnClickedBtnChoosefile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnRefresh();
	CButton m_radioUpType;
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnBeginupdata();
	CButton m_btnSend;
};


