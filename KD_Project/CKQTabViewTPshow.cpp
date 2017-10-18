// CKQTabViewTPshow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQTabViewTPshow.h"
#include "NetViewTPShow.h"
#include "CKQViewTPShowOldData.h"
// CCKQTabViewTPshow

IMPLEMENT_DYNCREATE(CCKQTabViewTPshow, CTabView)

CCKQTabViewTPshow::CCKQTabViewTPshow()
{

}

CCKQTabViewTPshow::~CCKQTabViewTPshow()
{
}

BEGIN_MESSAGE_MAP(CCKQTabViewTPshow, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCKQTabViewTPshow ���

#ifdef _DEBUG
void CCKQTabViewTPshow::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQTabViewTPshow::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQTabViewTPshow ��Ϣ�������
int CCKQTabViewTPshow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //��ǩ�ö�
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3DЧ��
	GetTabControl().EnableAutoColor( TRUE );//�Զ���ɫ
	GetTabControl().SetTabBorderSize( 5 ); //�߿��С
	GetTabControl().EnableTabSwap( FALSE );    //��ֹ�϶� 

	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("ʵʱ����ͼ"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewTPShowOldData),_T("��ʷ����ͼ"),300,NULL);
	return 0;
}
