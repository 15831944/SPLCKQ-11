// TPShowFindList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TPShowFindList.h"
#include "afxdialogex.h"


// CTPShowFindList �Ի���

IMPLEMENT_DYNAMIC(CTPShowFindList, CDialogEx)

CTPShowFindList::CTPShowFindList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTPShowFindList::IDD, pParent)
{

}

CTPShowFindList::~CTPShowFindList()
{
}

void CTPShowFindList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PMESSAGE, m_staticPMessage);
	DDX_Control(pDX, IDC_LIST_FINDLIST, m_listFindList);
	DDX_Control(pDX, IDC_LIST_TPLIST, m_listTPList);
}


BEGIN_MESSAGE_MAP(CTPShowFindList, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTPShowFindList ��Ϣ�������


BOOL CTPShowFindList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listFindList.InsertColumn(0 , _T("�豸MAC��ַ") , LVCFMT_CENTER , 100);
	m_listFindList.InsertColumn(1 , _T("TEI") , LVCFMT_CENTER , 100);
	m_listFindList.InsertColumn(2 , _T("������TEI") , LVCFMT_CENTER , 100);
	m_listFindList.InsertColumn(3 , _T("��ɫ") , LVCFMT_CENTER , 100);
	m_listFindList.InsertColumn(4 , _T("�㼶") , LVCFMT_CENTER , 100);
	m_listFindList.InsertColumn(5 , _T("����ɹ���") , LVCFMT_CENTER , 100);
	m_listFindList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_listTPList.InsertColumn(0 , _T("�豸MAC��ַ") , LVCFMT_CENTER , 100);
	m_listTPList.InsertColumn(1 , _T("TEI") , LVCFMT_CENTER , 100);
	m_listTPList.InsertColumn(2 , _T("������TEI") , LVCFMT_CENTER , 100);
	m_listTPList.InsertColumn(3 , _T("��ɫ") , LVCFMT_CENTER , 100);
	m_listTPList.InsertColumn(4 , _T("�㼶") , LVCFMT_CENTER , 100);
	m_listTPList.InsertColumn(5 , _T("����ɹ���") , LVCFMT_CENTER , 100);
	m_listTPList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CTPShowFindList::KongjianSize(int nID, int cx, int cy, bool bComb)
{
	CWnd *pWnd;  
	pWnd = GetDlgItem(nID);     //��ȡ�ؼ���� 
	int fcx=0,fcy=0;
	int nBottom = 0;
	if (bComb == true)
	{
		nBottom = 100;
	}
	if(pWnd)    
	{ 
		CRect rect;   //��ȡ�ؼ��仯ǰ��С 
		pWnd->GetWindowRect(&rect); 
		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е��������� 
		fcx=m_cRect.right;
		fcy=m_cRect.bottom;
		rect.left=(int)(rect.left*((float)cx/(float)fcx));//�����ؼ���С 
		rect.right=(int)(rect.right*((float)cx/(float)fcx)); 
		rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy)) + nBottom;
		pWnd->MoveWindow(rect);//���ÿؼ�λ�� 
	}
}

void CTPShowFindList::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	KongjianSize(IDC_STATIC_PMESSAGE,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC1,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC2,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC3,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC4,rect.right,rect.bottom);
	KongjianSize(IDC_LIST_FINDLIST,rect.right,rect.bottom);
	KongjianSize(IDC_LIST_TPLIST,rect.right,rect.bottom);
	GetClientRect(m_cRect);
}
void CTPShowFindList::SetTPdataToAccess(CString strTPdata)
{
	CString  strMAC ,strTEI ,strPTEI, strRole , strLayer , strSuccess;
	CTools tools;
	m_listFindList.DeleteAllItems();
	int nNumb = strTPdata.GetLength()/28;
	for(int n = 0 ; n < nNumb ; n++)
	{
		strMAC = strTPdata.Mid(0 , 12);
		m_listFindList.InsertItem(n , tools._strDaoxu(strMAC));

		strTEI = strTPdata.Mid(12 , 4);
		m_listFindList.SetItemText(n , 1 ,tools._str16tostr10(tools._strDaoxu(strTEI)));

		strPTEI = strTPdata.Mid(16 , 4);
		m_listFindList.SetItemText(n , 2 ,tools._str16tostr10(tools._strDaoxu(strPTEI)));

		strRole = strTPdata.Mid(20 , 2);
		m_listFindList.SetItemText(n , 3 ,tools._str16tostr10(strRole.Mid(0 ,1)));
		m_listFindList.SetItemText(n , 4 ,tools._str16tostr10(strRole.Mid(1 ,1)));

		strSuccess = m_tools._str16tostr10(strTPdata.Mid(22 , 2));
		m_listFindList.SetItemText(n , 5 ,strSuccess + _T("%"));

		strTPdata = strTPdata.Mid(28);
	}
}