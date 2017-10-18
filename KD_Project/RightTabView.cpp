// RightTabView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "KD_ProjectDoc.h"
#include "RightTabView.h"
#include "FormTabView1.h"
#include "NetViewTPShow.h"
#include "NetViewPToP.h"
#include "NetViewRepeat.h"
#include "CKQViewConfig.h"
#include "FView3762.h"
#include "CKQViewUpdata.h"
#include "CKQViewErrTab.h"
#include "CKQTabViewTPshow.h"
#include "DlgExtReadMeter.h"


// CRightTabView

IMPLEMENT_DYNCREATE(CRightTabView, CTabView)

CRightTabView::CRightTabView()
{
	m_nFindNet = -1;
	m_nTPShow = -1;
	m_nPointToPoint = -1;
	m_nOpenNumb = -1;
}

CRightTabView::~CRightTabView()
{
}

BEGIN_MESSAGE_MAP(CRightTabView, CTabView)
	ON_WM_CREATE()
//	ON_WM_CLOSE()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRightTabView ���

#ifdef _DEBUG
void CRightTabView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightTabView ��Ϣ�������

int CRightTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //��ǩ�ö�
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3DЧ��
	GetTabControl().EnableAutoColor( TRUE );//�Զ���ɫ
	GetTabControl().SetTabBorderSize( 10 ); //�߿��С
	GetTabControl().EnableTabSwap( FALSE );    //��ֹ�϶� 

	//GetTabControl().HideSingleTab( TRUE );   //����Tabʱ����ʾTab��ǩ
	/*CCreateContext context;
	context.m_pCurrentDoc = GetDocument();
	context.m_pNewViewClass = RUNTIME_CLASS(CFormTabView1);*/
	AddView(RUNTIME_CLASS(CFormTabView1),_T("��������"),200,NULL);
	AddView(RUNTIME_CLASS(CCKQTabViewTPshow),_T("������ʾ"),200,NULL);
	AddView(RUNTIME_CLASS(CNetViewPToP),_T("��Ե�ͨѶ"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewConfig),_T("���ò�ѯ���趨"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewUpdata),_T("ģ������"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewErrTab),_T("������Ϣ"),300,NULL);
	AddView(RUNTIME_CLASS(CFView3762),_T("������ת��"),300,NULL);

	
	
	return 0;
}


BOOL CRightTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CTabView::PreCreateWindow(cs);
}

void CRightTabView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();
	//
}
void CRightTabView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	SetActiveView(lHint);

}
