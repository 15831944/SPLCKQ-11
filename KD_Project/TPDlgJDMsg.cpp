// TPDlgJDMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TPDlgJDMsg.h"
#include "afxdialogex.h"


// CTPDlgJDMsg �Ի���

IMPLEMENT_DYNAMIC(CTPDlgJDMsg, CDialogEx)

CTPDlgJDMsg::CTPDlgJDMsg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTPDlgJDMsg::IDD, pParent)
{

}

CTPDlgJDMsg::~CTPDlgJDMsg()
{
}

void CTPDlgJDMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG, m_editMsg);
}


BEGIN_MESSAGE_MAP(CTPDlgJDMsg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTPDlgJDMsg ��Ϣ�������


void CTPDlgJDMsg::KongjianSize(int nID, int cx, int cy, bool bComb)
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
		rect.left=0;//�����ؼ���С 
		rect.right=cx; 
		rect.top=0; 
		rect.bottom = cy;
		pWnd->MoveWindow(rect);//���ÿؼ�λ�� 
	}
}

void CTPDlgJDMsg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	KongjianSize(IDC_EDIT_MSG , rect.right,rect.bottom , false);
}
