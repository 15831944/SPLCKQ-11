// MyListCtrl_1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "MyListCtrl_1.h"


// MyListCtrl_1

IMPLEMENT_DYNAMIC(MyListCtrl_1, CListCtrl)

MyListCtrl_1::MyListCtrl_1()
{

}

MyListCtrl_1::~MyListCtrl_1()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl_1, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// MyListCtrl_1 ��Ϣ�������




void MyListCtrl_1::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	// TODO:  ������Ĵ����Ի���ָ����

	CDC* pDC = CDC::FromHandle(lpDIS->hDC); 
	
	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDIS->itemID; 
	BOOL bGet = GetItem(&lvi); 
	
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && 
		((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS)))); 
	
	// ���ı����� 
	CRect rcBack = lpDIS->rcItem; 
	pDC->SetBkMode(TRANSPARENT); 
	if( bHighlight ) 
	{ 
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
		
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		CString str = _T("");
		str = GetItemText(lpDIS->itemID,1);
		pDC->SetTextColor(RGB(0, 0, 255));	
	} 
		//����������ɫ 
	CString str; 
	
	//�õ������С 
	CRect rcFocus = lpDIS->rcItem; 
	rcFocus.DeflateRect(1,1,1,1); 
	
	if (lpDIS->itemAction & ODA_DRAWENTIRE) 
	{ 
		//д�ı� 
		CString szText; 
		for (int i = 0; i < 20; i++) 
		{ 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDIS->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
			szText = GetItemText( lpDIS->itemID, i ); 
			rcItem.left += 5;
			rcItem.right -= 1; 

			if(i==4){
				CString str2 = GetItemText(lpDIS->itemID,5);
				if (str2 == "�ɹ�"||str2 == "������ʼ���ɹ�")
				{
					pDC->SetTextColor(RGB(0,255,0));
				}
				if (str2 == "ʧ��"||str2 == "������ʼ��ʧ��")
				{
					pDC->SetTextColor(0x0000FF);
				}
			}

			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
		} 
	}
}


void MyListCtrl_1::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	//CMenu menu;//
 //   VERIFY(menu.LoadMenu(IDR_MENUMSGMET));
	//CMenu* pPopup = menu.GetSubMenu(0);
	//ASSERT(pPopup != NULL);
	//CWnd* pWndPopupOwner = this;

	//while (pWndPopupOwner->GetStyle() & WS_CHILD)
	//	pWndPopupOwner = pWndPopupOwner->GetParent();

	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
	//	pWndPopupOwner);
}
