#if !defined(AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_)
#define AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayData.h : header file
//
#include "Tools.h"
/////////////////////////////////////////////////////////////////////////////
// CDisplayData window

class CDisplayData
{
// Construction
public:
	CDisplayData();

// Attributes
public:
	int m_nstrN;
	int m_nOldRecvCi;
	int m_RecvOldCishu[5000];
	int m_RecvCishu[1000];
	int m_nRecvCi;
	int m_nZondDataLen;
	CTools m_tools;
	bool m_bBits;
	int m_nBits;
	int m_nBit;
	int m_njiexi;
	int m_nXiaoshu;
	CString GetGeshi(CString strXunhuan,CString strGeshi,int m,int n);//�����ʾ����
	CString GetBeizhu(CString strXunhuan,CString strBeizhu);//�����ʾ����
	CString DisplayShowMessage(CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen);
	CString DisplayJiexiData(CString str,INT8U *DstBuf,int * RecvCishu,int nCishu);  //��ʾ������
	CString DisplayDatabin(CString strShuxingname,INT8U *DstBuf); //bin��ʽ��ʾ
	CString Bin(INT8U *buf,int nJiexi,int zijielen,bool ForR);
	CString DisplayDatabin_n(CString strShuxingname,INT8U *DstBuf); //bin_n��ʽ��ʾ
	CString DisplayDatabit(CString strShuxingname,INT8U *DstBuf);//bit ��ʽ��ʾ
	void Bit(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,int *fanhuidata,bool ForR);
	void Bits(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,CString * strshujulen,int *fanhuidata,bool ForR);
	CString DisplayDatabits(CString strShuxingname,INT8U *DstBuf);//bits��ʽ��ʾ
	CString DisplayDataascll(CString strShuxingname,INT8U *DstBuf);//ascll��ʽ��ʾ
	CString Char(INT8U *buf,int nJiexi,int zijielen,bool ForR);
	CString DisplayDatachar(CString strShuxingname,INT8U *DstBuf);//����С��������ָ�ʽ��ʾ
	//CString DisplayDataA01(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA02(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA99(INT8U *DstBuf);
	//CString DisplayDataA03(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA04(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA05(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA06(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA07(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA08(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA09(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA10(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA11(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA12(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA13(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA14(INT8U *DstBuf);//A01��ʽ��ʾ  ������ ʱ���� ����
	//CString DisplayDataA15(INT8U *DstBuf);//A15��ʽ��ʾ  ������ ʱ��
	//CString DisplayDataA16(INT8U *DstBuf);//A16��ʽ��ʾ  ����ʱ����
	//CString DisplayDataA17(INT8U *DstBuf);//A17��ʽ��ʾ  ���� ʱ��
	//CString DisplayDataA18(INT8U *DstBuf);//A18��ʽ��ʾ  ��ʱ��
	//CString DisplayDataA19(INT8U *DstBuf);//A19��ʽ��ʾ  ʱ��
	//CString DisplayDataA20(INT8U *DstBuf);//A20��ʽ��ʾ  ������ 
	//CString DisplayDataA21(INT8U *DstBuf);//A21��ʽ��ʾ  ����
	//CString DisplayDataA22(INT8U *DstBuf);
	//CString DisplayDataA23(INT8U *DstBuf);
	//CString DisplayDataA24(INT8U *DstBuf);
	//CString DisplayDataA25(INT8U *DstBuf);
	//CString DisplayDataA26(INT8U *DstBuf);
	//CString DisplayDataA27(INT8U *DstBuf);
	//CString DisplayDataA28(INT8U *DstBuf);

	//CString DisplayDataA29(INT8U *DstBuf);
	//CString DisplayDataA30(INT8U *DstBuf);
	//CString DisplayDataA31(INT8U *DstBuf);
	//CString DisplayDataA32(INT8U *DstBuf);
	//CString DisplayDataA33(INT8U *DstBuf);
	//CString DisplayDataA35(INT8U *DstBuf);
	//CString DisplayDataA36(INT8U *DstBuf);
	//CString DisplayDataA37(INT8U *DstBuf);
	//CString DisplayDataA40(INT8U *DstBuf);//������
	//CString DisplayDataTdc(INT8U *DstBuf);
	//CString DisplayDataTdh(INT8U *DstBuf);
	//CString DisplayDataDADT(INT8U *DstBuf);
	//CString DisplayDataTIME(INT8U *DstBuf);
	//CString DisTdh(int n); 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisplayData();

	// Generated message map functions
protected:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_)
