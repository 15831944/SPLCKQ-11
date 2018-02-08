// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "MyListCtrl.h"
#include "MainFrm.h"
#include "RightTabView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl
int sort_column; // ��¼�������
bool method; // ��¼�ȽϷ���
bool check=false;
CMyListCtrl::CMyListCtrl()
{
	m_itemYes=-1;
	m_nChooseList = -1;
	method = false;
	vector<ITEM_CHECK>      m_itemVector;
	
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
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CMyListCtrl::OnLvnColumnclick)
ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl::OnNMClick)
ON_NOTIFY_REFLECT(LVN_INSERTITEM, &CMyListCtrl::OnLvnInsertitem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers


//int CMyListCtrl::InsertItem(int nItem,LPCTSTR lpszItem)
//{
//	CMyListCtrl::InsertItem(nItem,lpszItem);
//	ITEM_CHECK m_itemCheck;
//
//	m_itemCheck.item=nItem;
//	m_itemCheck.flag=0;
//	m_itemVector.push_back(m_itemCheck);
//	return 0;
//}



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
	DWORD dwStype = GetExtendedStyle();

	if( bHighlight ) 
	{ 
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
		
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		CString str = _T("");
		CString str1 = _T("");
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
			str = GetItemText(lpDIS->itemID,3);
			if (str == "����")
			{
				pDC->SetTextColor(RGB(0,0,255));
			}
			else if (str == "δ����")
			{
				pDC->SetTextColor(RGB(255,97,0));
			}
			else if (str == "δ�ڰ�����")
			{
				pDC->SetTextColor(0x808000);
			}
			else{
				pDC->SetTextColor(RGB(0,0,255));
			}
			str1 = GetItemText(lpDIS->itemID,6);
			if (str1 == "ʧ��")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(0x0000FF);
			}
			else if (str1 == "�ɹ�")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(0x008000);
			}
			else if (str1 == "���汾����...")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(RGB(0, 255, 150));
				//pDC->SetBkColor(RGB(255, 97, 3)); 
			} 
			break;
		case 3://������
			str = GetItemText(lpDIS->itemID,3);
			if (str == "����")
			{
				pDC->SetTextColor(RGB(0,0,255));
			}
			else if (str == "δ����")
			{
				pDC->SetTextColor(RGB(255,97,0));
			}
			else if (str == "δ�ڰ�����")
			{
				pDC->SetTextColor(0x808000);
			}
			else{
				pDC->SetTextColor(RGB(0,0,255));
			}
			str1 = GetItemText(lpDIS->itemID,6);
			if (str1 == "ʧ��")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(0x0000FF);
			}
			else if (str1 == "�ɹ�")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(0x008000);
			}
			else if (str1 == "������...")
			{
				//pDC->SetBkColor(RGB(255, 97, 3));       //������ɫ 
				pDC->SetTextColor(RGB(0, 255, 150));
				//pDC->SetBkColor(RGB(255, 97, 3)); 
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
		for (int i = 0; i < 20; i++) 
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
	if((dwStype&LVS_EX_CHECKBOXES)==LVS_EX_CHECKBOXES)
	{
	  int nSize = GetSystemMetrics(9);
	  CRect CheckRect(lpDIS->rcItem.left + 3,lpDIS->rcItem.top + 3, 0, 0);
	  CheckRect.right = CheckRect.left + nSize-2,
	  CheckRect.bottom = CheckRect.top + nSize-2;
	  if((GetAsyncKeyState(VK_SHIFT) & 0x8000)==0){//δ��סshift
		 if(m_itemVector.at(lvi.iItem).flag==0)              
		 {
			pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_BUTTONCHECK);

		 }else if(m_itemVector.at(lvi.iItem).flag==1)
		 {
			pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_CHECKED);
		 }else
		 {
			pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_INACTIVE);
		 }
	  }
	  else{
		 if(m_itemVector.at(lvi.iItem).flag==0)              
		 {
			m_itemVector.at(lvi.iItem).flag=1;
			pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_CHECKED);

		 }else if(m_itemVector.at(lvi.iItem).flag==1)
		 {
			 pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_CHECKED);
			//pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_BUTTONCHECK);
		 }else
		 {
			pDC->DrawFrameControl(&CheckRect,DFC_BUTTON,DFCS_INACTIVE);
		 }
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
			if(pHDNotify-> iItem   ==   6   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}if(pHDNotify-> iItem   ==   7   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			if(pHDNotify-> iItem   ==   8  ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}if(pHDNotify-> iItem   ==   9  ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			if(pHDNotify-> iItem   ==  10 ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			if(pHDNotify-> iItem   ==   11  ) 
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
	if (m_nChooseList == 3){

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
		VERIFY(menu.LoadMenu(IDR_RBMENU_METERR));
		break;
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
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE >(pNMHDR);
	// TODO: Add your message handler code here and/or call default
	RedrawItems(m_itemYes,m_itemYes);
	m_itemYes=HitTest(point,&nFlags);
	CListCtrl::OnLButtonDown(nFlags, point);
	LVHITTESTINFO lvinfo;
    lvinfo.pt = point;
    lvinfo.flags = LVHT_ABOVE;
	int item=GetItemCount();
	if (m_itemYes==(-1))
	{
		//RedrawItems(0,item);
	     //SetItemState(item, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		//SetItemState(item, 0, LVIS_SELECTED|LVIS_FOCUSED);
		//SetItemState(lvinfo.iItem, (LVIS_SELECTED == GetItemState(lvinfo.iItem, LVIS_SELECTED) ? 0 : LVIS_SELECTED), LVIS_SELECTED);
	}

}

int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    //�Ӳ�������ȡ����Ƚ�lc����������
    int row1 = (int)lParam1;
    int row2 = (int)lParam2;
    CListCtrl*lc = (CListCtrl*)lParamSort;
    CString lp1 = lc->GetItemText(row1, sort_column);
    CString lp2 = lc->GetItemText(row2, sort_column);
    //�Ƚϣ��Բ�ͬ���У���ͬ�Ƚϣ�ע���¼ǰһ����������һ��Ҫ�෴����
    if (sort_column!=3&&sort_column!=6)
    {
        //int�ͱȽ�
        int a = _wtoi(lp1.GetBuffer());
        int b = _wtoi(lp2.GetBuffer());
        if (method)
        {
            return a - b;
        }
        else
            return b - a;
    }
    else
    {
        // �����ͱȽ�
        if (method)
            return lp1.CompareNoCase(lp2);
        else
            return lp2.CompareNoCase(lp1);
    }
    return 0;
	//return lp1 - lp2; 
}
 


void CMyListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
     // TODO: Add your control notification handler code here
    method=!method;
	int count,count2,i,i2;
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFrameSetNet * pChildFrm =  ( CFrameSetNet *) pMain->GetActiveFrame();
	CRightTabView *  pTabView =( CRightTabView *) pChildFrm->m_wndSplitter.GetPane(0 , 1);
	CCKQViewUpdata * pViewTUpdata=NULL;
	switch (m_nChooseList)
	{
	case 0://��Ϣ�˵�
		return;
	case 2://�����˵�
		//pTabView->SetActiveView(2);
		pViewTUpdata = (CCKQViewUpdata *)pTabView->GetActiveView();
		sort_column=pNMListView->iSubItem; // ȡ����������к�
		count2=pViewTUpdata->m_listData.GetItemCount();
		i2=0;
        //AfxMessageBox(_T("�б���û�м�¼��Ҫ���棡"));
        for(i2=0;i2<count2;i2++)
         pViewTUpdata->m_listData.SetItemData(i2,i2); // ���ñȽϹؼ���
     
         pViewTUpdata->m_listData.SortItems(MyCompareProc,(DWORD_PTR)&(pViewTUpdata->m_listData));
		break;
	case 3://���ϲ˵�
		//pTabView->SetActiveView(2);
		CCKQViewTabErrMet * pViewTabErrMet = (CCKQViewTabErrMet *)pTabView->GetActiveView();
		sort_column=pNMListView->iSubItem; // ȡ����������к�
		count=pViewTabErrMet->m_listData.GetItemCount();
		i=0;
 
        for(i=0;i<count;i++)
         pViewTabErrMet->m_listData.SetItemData(i,i); // ���ñȽϹؼ���
     
         pViewTabErrMet->m_listData.SortItems(MyCompareProc,(DWORD_PTR)&(pViewTabErrMet->m_listData));
 
    
		break;
	}
 
    *pResult = 0;
}


void CMyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{

	 //SetItemState(iItem, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//*pResult = 0;
	//	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//CFrameSetNet * pChildFrm =  ( CFrameSetNet *) pMain->GetActiveFrame();
	//CRightTabView *  pTabView =( CRightTabView *) pChildFrm->m_wndSplitter.GetPane(0 , 1);


	//CCKQViewTabErrMet * pViewTabErrMet = (CCKQViewTabErrMet *)pTabView->GetActiveView();

	//DWORD dwPos = GetMessagePos();    
 //   CPoint point( LOWORD(dwPos), HIWORD(dwPos) );    
 //  pViewTabErrMet->m_listData.ScreenToClient(&point);    
 // 
 //   //����ṹ��     
 //   LVHITTESTINFO lvinfo;    
 //   lvinfo.pt = point;      
 //   int itemSel =pViewTabErrMet->m_listData.HitTest(&lvinfo);  

	pResult = 0;
}


BOOL CMyListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if((WM_LBUTTONDOWN == pMsg->message)&& (GetSafeHwnd() == pMsg->hwnd))
    {	
        CPoint pt;
        GetCursorPos(&pt);
		SetFocus();
        ScreenToClient(&pt);
        LVHITTESTINFO info = {0};
        info.pt = pt;
        info.flags = LVHT_ONITEMLABEL;
        if(-1 != SubItemHitTest(&info))
        {
            CString str;
            str.Format(_T("%d, %d"), info.iItem, info.iSubItem);
            SetWindowText(str);
			if(info.iSubItem==0){
				//int nSelect = GetSelectedCount();
				//POSITION pos = GetFirstSelectedItemPosition();
				//int nSelItem=GetNextSelectedItem(pos);
				//int NUM=nSelItem+nSelect;
				//for(nSelItem;nSelItem<NUM;nSelItem++)
				//{
				//	
				//	if(m_itemVector.at(nSelItem).flag == 1)
				//	{
				//		m_itemVector.at(nSelItem).flag = 0;
				//	}else if(m_itemVector.at(nSelItem).flag == 0)
				//	{
				//		m_itemVector.at(nSelItem).flag = 1;
				//	}
				//	SetItemState(nSelItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
				//	//nSelect--;
				//}


					if(m_itemVector.at(info.iItem).flag == 1)
					{
						m_itemVector.at(info.iItem).flag = 0;
					}else if(m_itemVector.at(info.iItem).flag == 0)
					{
						m_itemVector.at(info.iItem).flag = 1;
					}

				//SetCheck(info.iItem,TRUE);
            //SetItemState(info.iItem, (LVIS_SELECTED == GetItemState(info.iItem, LVIS_SELECTED) ? 0 : LVIS_SELECTED), LVIS_SELECTED);
			}
			else{
				//ITEM_CHECK  &itemCheck = m_itemVector.at(info.iItem);
				 //itemCheck.flag=N;
				//SetItemState(info.iItem, (LVIS_SELECTED == GetItemState(info.iItem, LVIS_SELECTED) ? 0 : LVIS_SELECTED), LVIS_SELECTED);
			}
			//if(GetKeyState(VK_SHIFT)!=0){
				//return true;
			//}
			//else {
			return CListCtrl::PreTranslateMessage(pMsg);
			//}
        }       
    }
	return CListCtrl::PreTranslateMessage(pMsg);
}






void CMyListCtrl::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ITEM_CHECK m_itemCheck;
	int item=GetItemCount();
	CString str;
    str.Format(_T("%d"), item);
	//AfxMessageBox(str);
	m_itemCheck.item=item;
	m_itemCheck.flag=0;
	m_itemVector.push_back(m_itemCheck);
	*pResult = 0;
}
