// Form698.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "Form698.h"
#include "MainFrm.h"

// CForm698

IMPLEMENT_DYNCREATE(CForm698, CMDIChildWnd)

CForm698::CForm698()
{

}

CForm698::~CForm698()
{
}


BEGIN_MESSAGE_MAP(CForm698, CMDIChildWnd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CForm698 ��Ϣ�������


void CForm698::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bFrame698 = false;
	CMDIChildWnd::OnClose();
}


BOOL CForm698::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	//cs.style   =   WS_CHILD|

	//	WS_VISIBLE|

	//	WS_OVERLAPPED|

	//	WS_CAPTION|

	//	WS_SYSMENU|

	//	// FWS_ADDTOTITLE|

	//	WS_THICKFRAME|

	//	WS_MINIMIZEBOX|

	//	WS_MAXIMIZEBOX|

	//	WS_MAXIMIZE;
	//cs.lpszName = _T("698����");
	return CMDIChildWnd::PreCreateWindow(cs);
}
