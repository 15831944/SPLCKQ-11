// FrameShowWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "FrameShowWnd.h"


// CFrameShowWnd

IMPLEMENT_DYNAMIC(CFrameShowWnd, CDockablePane)

CFrameShowWnd::CFrameShowWnd()
{

}

CFrameShowWnd::~CFrameShowWnd()
{
}


BEGIN_MESSAGE_MAP(CFrameShowWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
//	ON_COMMAND(ID_COPYFRAME, &CFrameShowWnd::OnCopyframe)
END_MESSAGE_MAP()



// CFrameShowWnd ��Ϣ�������




int CFrameShowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	CRect rectDummy;
	rectDummy.SetRectEmpty();  
	m_myTabCtrl.Create(TCS_TABS|WS_CHILD|WS_VISIBLE,rectDummy,this,IDC_TABLE_MYSHOWFRAME);
	m_myTabCtrl.InsertItem(0,_T("��Ϣ"));  
	m_myTabCtrl.InsertItem(1,_T("����")); 
	return 0;
}


void CFrameShowWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (GetSafeHwnd() == NULL)  
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient); 
	m_myTabCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 1, rectClient.Width() - 2, rectClient.Height()  - 2, SWP_NOACTIVATE | SWP_NOZORDER);

}


