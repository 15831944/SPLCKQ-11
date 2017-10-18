// ViewLetTree.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ViewLetTree.h"
#include "KD_ProjectView.h"
#include "ChildFrm.h"
#include "RightTabView.h"
#include "MainFrm.h"


// CViewLetTree

IMPLEMENT_DYNCREATE(CViewLetTree, CTreeView)

CViewLetTree::CViewLetTree()
{

}

CViewLetTree::~CViewLetTree()
{
}

BEGIN_MESSAGE_MAP(CViewLetTree, CTreeView)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewLetTree::OnNMClick)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CViewLetTree ���

#ifdef _DEBUG
void CViewLetTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewLetTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewLetTree ��Ϣ�������


void CViewLetTree::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	// TODO: �ڴ����ר�ô����/����û���
	m_ilDrives.Create(IDB_BITMAP1,15,2,RGB(255,0,255));
	this->GetTreeCtrl().SetImageList(&m_ilDrives,TVSIL_NORMAL);

	HTREEITEM hEagles = GetTreeCtrl().InsertItem(_T("��������"),4,5);
	hEagles = GetTreeCtrl().InsertItem(_T("��������"),4,5);
	GetTreeCtrl().InsertItem(_T("������ʾ"),4,5,hEagles);

	hEagles = GetTreeCtrl().InsertItem(_T("ģ����"),4,5);
	GetTreeCtrl().InsertItem(_T("��Ե�ͨѶ"),4,5,hEagles);
	GetTreeCtrl().InsertItem(_T("������Ϣ"),4,5,hEagles);

	hEagles = GetTreeCtrl().InsertItem(_T("ģ�⼯����"),4,5);
	GetTreeCtrl().InsertItem(_T("����������"),4,5,hEagles);
	GetTreeCtrl().InsertItem(_T("�����ɼ�"),4,5,hEagles);
	hEagles = GetTreeCtrl().InsertItem(_T("���ò�ѯ���趨"),4,5);
	hEagles = GetTreeCtrl().InsertItem(_T("������ת��"),4,5);
	hEagles = GetTreeCtrl().InsertItem(_T("ģ������"),4,5);
	hEagles = GetTreeCtrl().InsertItem(_T("���ô���"),4,5);
	hEagles = GetTreeCtrl().InsertItem(_T("һ�����"),4,5);


	
}


BOOL CViewLetTree::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!CTreeView::PreCreateWindow (cs))  
	return FALSE;  
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |  
	TVS_SHOWSELALWAYS;
	return TRUE;
}


void CViewLetTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame* pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	NM_TREEVIEW* pHdr = (NM_TREEVIEW*)pNMHDR;
	CString strTreeName = _T("");
	CPoint point;
	UINT uFlag = 0 ;
	GetCursorPos(&point);
	GetTreeCtrl().ScreenToClient(&point);
	HTREEITEM item = GetTreeCtrl().HitTest(point, &uFlag);
	if (GetTreeCtrl().GetChildItem(item) == NULL)
	{
		CChildFrame * pChild = (CChildFrame *)GetParent();
		strTreeName = GetTreeCtrl().GetItemText(item);
		if (strTreeName == _T("��������"))
		{
			GetDocument()->UpdateAllViews(this,0,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("������ʾ"))
		{
			GetDocument()->UpdateAllViews(this,1,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("��Ե�ͨѶ"))
		{
			GetDocument()->UpdateAllViews(this,2,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("���ò�ѯ���趨"))
		{
			GetDocument()->UpdateAllViews(this,3,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("ģ������"))
		{
			GetDocument()->UpdateAllViews(this,4,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("������Ϣ"))
		{
			GetDocument()->UpdateAllViews(this,5,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("������ת��"))
		{
			GetDocument()->UpdateAllViews(this,6,(CObject *)(LPCTSTR) strTreeName);
		}
	
	
	
		/*if (strTreeName == _T("�����ɼ�"))
		{
			GetDocument()->UpdateAllViews(this,6,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("ģ������"))
		{
			GetDocument()->UpdateAllViews(this,7,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("���ô���"))
		{
			GetDocument()->UpdateAllViews(this,8,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("һ�����"))
		{
			GetDocument()->UpdateAllViews(this,9,(CObject *)(LPCTSTR) strTreeName);
		}*/
	}
	
	*pResult = 0;
}