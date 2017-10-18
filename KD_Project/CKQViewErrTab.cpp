// CKQViewErrTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewErrTab.h"
#include "CKQViewTabErrMet.h"
#include "CKQViewTabErrMod.h"

// CCKQViewErrTab

IMPLEMENT_DYNCREATE(CCKQViewErrTab, CTabView)

CCKQViewErrTab::CCKQViewErrTab()
{

}

CCKQViewErrTab::~CCKQViewErrTab()
{
}

BEGIN_MESSAGE_MAP(CCKQViewErrTab, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCKQViewErrTab ���

#ifdef _DEBUG
void CCKQViewErrTab::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewErrTab::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewErrTab ��Ϣ�������


int CCKQViewErrTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //��ǩ�ö�
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3DЧ��
	GetTabControl().EnableAutoColor( TRUE );//�Զ���ɫ
	GetTabControl().SetTabBorderSize( 5 ); //�߿��С
	GetTabControl().EnableTabSwap( FALSE );    //��ֹ�϶� 

	AddView(RUNTIME_CLASS(CCKQViewTabErrMod),_T("ģ�������Ϣ"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewTabErrMet),_T("��������Ϣ"),300,NULL);
	return 0;
}


//void CCKQViewErrTab::OnIdrRbmenuMeterr()
//{
//	// TODO: �ڴ���������������
//}
