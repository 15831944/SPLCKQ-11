// NetTabView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "NetTabView.h"
#include "FormTabView1.h"
#include "NetViewTPShow.h"
#include "NetViewRepeat.h"

// CNetTabView

IMPLEMENT_DYNCREATE(CNetTabView, CTabView)

CNetTabView::CNetTabView()
{

}

CNetTabView::~CNetTabView()
{
}

BEGIN_MESSAGE_MAP(CNetTabView, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CNetTabView ���

#ifdef _DEBUG
void CNetTabView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNetTabView ��Ϣ�������


void CNetTabView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();
}


int CNetTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //��ǩ�ö�
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3DЧ��
	GetTabControl().EnableAutoColor( TRUE );//�Զ���ɫ
	GetTabControl().SetTabBorderSize( 5 ); //�߿��С
	GetTabControl().EnableTabSwap( FALSE );    //��ֹ�϶� 
	CCreateContext context;
	//AddView(RUNTIME_CLASS(CFormTabView1),_T("��������"),200,&m_context);
	context.m_pNewViewClass = RUNTIME_CLASS(CFormTabView1);
	context.m_pCurrentDoc = GetDocument();
	AddView(RUNTIME_CLASS(CFormTabView1),_T("��������"),200,&context);

	context.m_pNewViewClass = RUNTIME_CLASS(CNetViewTPShow);
	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("������ʾ"),200,&context);

	context.m_pNewViewClass = RUNTIME_CLASS(CNetViewTPShow);
	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("������ʾ"),200,&context);

	
	return 0;
}
