// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyListCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_itemYes=-1;
	m_nChooseList = -1;
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
//	ON_COMMAND(ID_COPYFRAME, &CMyListCtrl::OnCopyframe)
//	ON_UPDATE_COMMAND_UI(ID_COPYFRAME, &CMyListCtrl::OnUpdateCopyframe)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void   CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT   lpDIS) 
{ 
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
		switch (m_nChooseList)
		{
		case 0://��Ϣ
			return;
		case 1://����
			str = GetItemText(lpDIS->itemID,1);
			if (str == "����>>")
			{
				pDC->SetTextColor(0x792355);
			}
			if (str == "����<<")
			{
				pDC->SetTextColor(0x254738);
			}
			break;
		case 2://����
			return;
		case 3://������
			str = GetItemText(lpDIS->itemID,3);
			if (str == "����")
			{
				pDC->SetTextColor(0x008000);
			}
			if (str == "δ����")
			{
				pDC->SetTextColor(0x0000FF);
			}
			if (str == "δ�ڰ�����")
			{
				pDC->SetTextColor(0x808000);
			}
			break;
		case 4://ģ�����
			str = GetItemText(lpDIS->itemID,3);
			if (str == "����")
			{
				pDC->SetTextColor(0x008000);
			}
			if (str == "δ����")
			{
				pDC->SetTextColor(0x0000FF);
			}
			if (str == "����")
			{
				pDC->SetTextColor(0xC3C3C3);
			}
			if (str == "δ�ڰ�����")
			{
				pDC->SetTextColor(0x808000);
			}
			break;
		}
		
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
		for (int i = 0; i < 10; i++) 
		{ 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDIS->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
			szText = GetItemText( lpDIS->itemID, i ); 
			rcItem.left += 5;
			rcItem.right -= 1; 
			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	}
}



BOOL CMyListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY   *pHDNotify   =   (HD_NOTIFY*)lParam; 
	int item;
	switch(   pHDNotify-> hdr.code   )   
	{ 
	case   HDN_ITEMCHANGINGA: 
	case   HDN_ITEMCHANGINGW: 
	case   HDN_ENDTRACK: 
		{ 
			if(pHDNotify-> iItem   ==   0   )//ѡ�е��ǵ�һ�У��������� 
                //ȡ��item��ֵ��
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			if(pHDNotify-> iItem   ==   1   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			
			if(pHDNotify-> iItem   ==   2   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			
            if(pHDNotify-> iItem   ==   3   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			if(pHDNotify-> iItem   ==   4   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}if(pHDNotify-> iItem   ==   5   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			break;
		} 
	} 
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}


void CMyListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_nChooseList == 1)
	{
		DeleteAllItems();
	}
	*pResult = 0;
}


void CMyListCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;//
	switch (m_nChooseList)
	{
	case 0://��Ϣ�Ҽ��˵�
		return;
	case 1://�����Ҽ��˵�
		VERIFY(menu.LoadMenu(IDR_MENU_COPYFRAME));
		break;
	case 2://�����Ҽ��˵�
		return;
	case 3://�籨�����Ҽ��˵�
		VERIFY(menu.LoadMenu(IDR_RBMENU_METERR));
		break;
	case 4://ģ������Ҽ��˵�
		VERIFY(menu.LoadMenu(IDR_RBMENU_MODERR));
		break;
	}

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}
void CMyListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int item=GetItemCount();
	RedrawItems(0,item-1);
	m_itemYes=HitTest(point,&nFlags);
}

void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RedrawItems(m_itemYes,m_itemYes);
	m_itemYes=HitTest(point,&nFlags);
	
	CListCtrl::OnLButtonDown(nFlags, point);
	if (m_itemYes==(-1))
	{
		int item=GetItemCount();
		RedrawItems(0,item-1);
	}
}