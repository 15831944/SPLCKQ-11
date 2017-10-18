
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "ViewLetTree.h"
#include "RightTabView.h"
#include "KD_ProjectView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style   =   WS_CHILD|

		WS_VISIBLE|

		WS_OVERLAPPED|

		WS_CAPTION|

		WS_SYSMENU|

		// FWS_ADDTOTITLE|

		WS_THICKFRAME|

		WS_MINIMIZEBOX|

		WS_MAXIMIZEBOX|

		WS_MAXIMIZE;
	cs.lpszName = _T("�������");
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	
	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bNetWork = false;
	CMDIChildWndEx::OnClose();
}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//SetMenu(NULL);
	return 0;
}


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	return TRUE;
}