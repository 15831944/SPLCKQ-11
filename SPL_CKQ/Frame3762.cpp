// Frame3762.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "Frame3762.h"
#include "MainFrm.h"

// CFrame3762

IMPLEMENT_DYNCREATE(CFrame3762, CMDIChildWnd)

CFrame3762::CFrame3762()
{

}

CFrame3762::~CFrame3762()
{
}


BEGIN_MESSAGE_MAP(CFrame3762, CMDIChildWnd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFrame3762 ��Ϣ�������

void CFrame3762::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bFrame3762 = false;
	CMDIChildWnd::OnClose();
}


BOOL CFrame3762::PreCreateWindow(CREATESTRUCT& cs)
{
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
	cs.lpszName = _T("3762����");
	return CMDIChildWnd::PreCreateWindow(cs);
}