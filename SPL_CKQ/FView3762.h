#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
#include "SetWriteDataDlg.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "DisplayData.h"
#include "Dlg13762Frame.h"
#include "SetWriteLoopNub.h"
// CFView3762 ������ͼ

class CFView3762 : public CFormView
{
	DECLARE_DYNCREATE(CFView3762)

protected:
	CFView3762();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFView3762();

public:
	enum { IDD = IDD_DIALOG_3762 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

	bool m_bFEF001;
	HTREEITEM m_hTree;
	CString m_strPWData;
	INT16U FileCalculateCRC(INT8U CRCHi,INT8U CRCLo,INT8U* InputData, long DataLen);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nLoopData;
	CString SetBeizhu(int nCishu,CString strBeizhu);
	CString SetGershi(int nCishu,CString strGeshi);
	CSetWriteLoopNub m_setWriteLoop;
	bool m_bZuZhen;
	CDlg13762Frame m_dlg13762Zuzhen;
	void GetZuzhenFrame();
	void ShowZuzhenData(INT8U nType = 0);
public:
	FILE* m_fp;
	CDisplayData m_display;
	CGW13762 m_gw13762;
	CCSG13762 m_nw13762;//NW
	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;
	sPartQCSG376_2CreatFrame m_ptSendQCSG376_2;//NW
	sPartQCSG376_2DeCodeFrame m_ptRecvQCSG376_2;//NW
	CTools m_tools;
	HANDLE m_hThreadsend;
	CRect m_cRect;
	long m_lShowLeft;
	CSetWriteDataDlg m_setWriteDatadlg;
	void KongjianSize(int nID, int cx, int cy, bool bComb = FALSE);
	void SetStruct3762(CString strMessage, CString strAFN_FN , CString strData , CString strDatalen, PartQGDW376_2 & pt3762);
	void UpdataTreeData();
	CPoint m_point; 
	void SetItemCheckState(HTREEITEM item, BOOL bCheck);
public://AFN=15 F001�������
	int m_nYU;
	int m_nCHU;
	int m_nDataLong;
	CString m_strMessageData;//��Ϣ���ַ��
	CStringList m_listStrShengjiData;//���������б�
	BOOL SetUpdataListData();//�������ļ����浽�����б���
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu);
	INT8U SendUpdataData(CString strName, INT8U *F8DataHead, int nChoose = 0);//��������
	INT8U SendSecretData(CString strName , int nChoose = 0);
	void SaveDebugData(INT32U pos, INT8U *recvBuf, INT16U recvLen);//����������־���ļ�
	INT8U RecvDebugData(CString strName, INT8U *F8DataHead , int nChoose = 0);//��������־
	void SaveExtendStaVersion(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // ����STA��չ�汾��
	INT8U RecvExtendStaDevStatus(CString strName , INT8U *F8DataHead, int nChoose = 0); //��STA��չ�汾��
	void SaveExtendStaDevStatus(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // ����STA���豸״̬
	INT8U RecvExtendStaVersion(CString strName, INT8U *F8DataHead, int nChoose = 0); //��STA���豸״̬
	void SaveNodeInfo(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // ����STA�ڵ���Ϣ
	INT8U RecvNodeInfo(CString strName , INT8U *F8DataHead, int nChoose = 0); //��STA�ڵ���Ϣ

	INT32U m_F1F0_TimeOut;//��������ʱʱ��
	
public:
	void SetWindowText(CString strData);
	void GetF8Data(INT8U * SrcDatabuf , INT16U SrcDatalen , INT8U * DstDatabuf , INT16U & DstDatalen);
public:
	int m_nDClick;
	bool m_bDCEditAddr;
	CAccessData m_accessData;
	void StorageListData();
	void DisplayData(CString strName ,CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen , int nType = 0);
public:
	CTreeCtrl m_treeData;
	CEdit m_editShow;
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickTreeData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkTreeData(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_combType;
	CEdit m_editAddress;
	afx_msg void OnEnSetfocusEditMessage();
	afx_msg void OnEnKillfocusEditMessage();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEnSetfocusEditAddress();
	afx_msg void OnEnKillfocusEditAddress();
	afx_msg void OnBnClickedButtonAddress();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonXy();
	afx_msg void OnBnClickedButtonStop();
	CButton m_btnSend;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonClear();
//	CButton m_editZuzhen;
	CButton m_btnZuZhen;
	afx_msg void OnBnClickedButtonZuzhen();

public://�������
	INT32U getNWfn(INT8U GW_AFN , CString GW_Fn);
	CButton button_address;
	afx_msg void OnBnClickedButton1();

	CString m_strFilePath_f0f1;
	void Save_log_File(INT8U* F8DataHead);//����flash �е�log���� 
};


