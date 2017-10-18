// CKQViewConfig.1cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewConfig.h"
#include "RightTabView.h"
#include "MainFrm.h"
#include "wingdi.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;
#pragma comment(lib, "Uxtheme.lib")
#include "Uxtheme.h"
// CCKQViewConfig

IMPLEMENT_DYNCREATE(CCKQViewConfig, CFormView)

CCKQViewConfig::CCKQViewConfig()
	: CFormView(CCKQViewConfig::IDD)
{

}

CCKQViewConfig::~CCKQViewConfig()
{
}

void CCKQViewConfig::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TYPE, m_listType);
	DDX_Control(pDX, IDC_EDIT101, m_edit101);
	DDX_Control(pDX, IDC_EDIT11, m_edit11);
	DDX_Control(pDX, IDC_EDIT12, m_edit12);
	DDX_Control(pDX, IDC_EDIT21, m_edit21);
	DDX_Control(pDX, IDC_EDIT22, m_edit22);
	DDX_Control(pDX, IDC_EDIT31, m_edit31);
	DDX_Control(pDX, IDC_EDIT32, m_edit32);
	DDX_Control(pDX, IDC_EDIT33, m_edit33);
	DDX_Control(pDX, IDC_EDIT51, m_edit51);
	DDX_Control(pDX, IDC_COMBO11, m_comb11);
	DDX_Control(pDX, IDC_COMBO31, m_comb31);
	DDX_Control(pDX, IDC_COMBO41, m_comb41);
	DDX_Control(pDX, IDC_COMBO42, m_comb42);
	DDX_Control(pDX, IDC_COMBO61, m_comb61);
	DDX_Control(pDX, IDC_COMBO71, m_comb71);
	DDX_Control(pDX, IDC_COMBO81, m_comb81);
	DDX_Control(pDX, IDC_COMBO91, m_comb91);
	DDX_Control(pDX, IDC_EDIT_MMAC, m_editMMAC);
	DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
	DDX_Control(pDX, IDC_BUTTON_CLIAN, m_btnClear);
	DDX_Control(pDX, IDC_BUTTON_READ, m_btnRead);
	DDX_Control(pDX, IDC_BUTTON_WRITE, m_btnWrite);
	DDX_Control(pDX, IDC_PICTURE, m_pictureMap);
}

BEGIN_MESSAGE_MAP(CCKQViewConfig, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST_TYPE, &CCKQViewConfig::OnSelchangeListType)
//	ON_CBN_SELCHANGE(IDC_COMBO2, &CCKQViewConfig::OnCbnSelchangeCombo2)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON_CLIAN, &CCKQViewConfig::OnBnClickedButtonClian)
ON_BN_CLICKED(IDC_BUTTON_READ, &CCKQViewConfig::OnBnClickedButtonRead)
ON_BN_CLICKED(IDC_BUTTON_WRITE, &CCKQViewConfig::OnBnClickedButtonWrite)
END_MESSAGE_MAP()


// CCKQViewConfig ���

#ifdef _DEBUG
void CCKQViewConfig::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewConfig::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

HBRUSH CCKQViewConfig::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_LIST_TYPE:
		pDC->SetTextColor(RGB(128, 128, 192));
		pDC->SetBkMode(TRANSPARENT); 
		break;
	case IDC_GROUP1:case IDC_GROUP2:case IDC_GROUP3:case IDC_GROUP4:case IDC_GROUP5:
	case IDC_GROUP6:case IDC_GROUP7:case IDC_GROUP8:case IDC_GROUP9:case IDC_GROUP10:
		pDC->SetTextColor(RGB(180, 0, 180));
		pDC->SetBkMode(TRANSPARENT); 
		if(m_listType.GetCurSel() == 3)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP6) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 4)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP2) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 5)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP3) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 6)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP4) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 7)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP5) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 8)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP9) hbr =  CreateSolidBrush(RGB(152,217,234));
		if(m_listType.GetCurSel() == 9)
			if (pWnd->GetDlgCtrlID() == IDC_GROUP10) hbr =  CreateSolidBrush(RGB(152,217,234));
		break;
	case IDC_STATIC11:case IDC_STATIC12:case IDC_STATIC13:case IDC_STATIC21:case IDC_STATIC22:
	case IDC_STATIC31:case IDC_STATIC32:case IDC_STATIC33:case IDC_STATIC34:case IDC_STATIC41:case IDC_STATIC42:
		pDC->SetTextColor(RGB(0, 128, 0));
		pDC->SetBkMode(TRANSPARENT);
		switch(m_listType.GetCurSel())
		{
		case 4:
			switch(pWnd->GetDlgCtrlID())
			{
			case IDC_STATIC21:case IDC_STATIC22:
				hbr =  CreateSolidBrush(RGB(152,217,234));
				break;
			}
			break;
		case 5:
			switch(pWnd->GetDlgCtrlID())
			{
			case IDC_STATIC31:case IDC_STATIC32:case IDC_STATIC33:case IDC_STATIC34:
				hbr =  CreateSolidBrush(RGB(152,217,234));
				break;
			}
			break;
		case 6:
			switch(pWnd->GetDlgCtrlID())
			{
			case IDC_STATIC41:case IDC_STATIC42:
				hbr =  CreateSolidBrush(RGB(152,217,234));
				break;
			}
			break;
		}
		
		break;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CCKQViewConfig::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CImage image;  
	HBITMAP hBmpGroup;
	image.Load(_T("res/GroupBackColor.png"));
	
	hBmpGroup = image.Detach();




	m_pictureMap.SetBitmap(hBmpGroup);


	Updata();
	SetItemEnableF();
}

void CCKQViewConfig::Updata()
{
	m_pictureMap.ShowWindow(SW_HIDE);
	m_btnRead.EnableWindow(FALSE);
	m_btnWrite.EnableWindow(FALSE);

	CFont fontlist;
	fontlist.CreatePointFont(150 , _T(""));
	m_listType.SetFont(&fontlist);
	m_listType.AddString(_T(""));
	m_listType.AddString(_T(""));
	m_listType.AddString(_T("ģ������"));
	m_listType.AddString(_T("������"));
	m_listType.AddString(_T("����״̬"));
	m_listType.AddString(_T("�豸��ַ����Ʒ״̬"));
	m_listType.AddString(_T("����·"));
	m_listType.AddString(_T("ģ������ʱ��"));
	m_listType.AddString(_T("˥��ģʽ"));
	m_listType.AddString(_T("ģ��汾��ѯ"));

	m_comb11.AddString(_T("2M-12M"));
	m_comb11.AddString(_T("2.5M-5.7M"));
	m_comb11.AddString(_T("1.5M-4.7M"));
	m_comb11.AddString(_T("500K-3.7M"));
	m_comb11.SetCurSel(-1);

	m_comb41.AddString(_T("0"));
	m_comb41.AddString(_T("1"));
	m_comb41.AddString(_T("2"));
	m_comb41.AddString(_T("3"));
	m_comb41.AddString(_T("4"));
	m_comb41.AddString(_T("5"));
	m_comb41.AddString(_T("6"));
	m_comb41.AddString(_T("7"));
	m_comb41.AddString(_T("8"));
	m_comb41.AddString(_T("9"));
	m_comb41.AddString(_T("10"));
	m_comb41.AddString(_T("11"));
	m_comb41.AddString(_T("12"));
	m_comb41.AddString(_T("13"));
	m_comb41.AddString(_T("14"));
	m_comb41.AddString(_T("15"));
	m_comb41.SetCurSel(-1);

	m_comb42.AddString(_T("��"));
	m_comb42.AddString(_T("�ر�"));
	m_comb42.SetCurSel(-1);

	m_comb91.AddString(_T("����"));
	m_comb91.AddString(_T("�ر�"));
	m_comb91.SetCurSel(-1);

	m_comb61.AddString(_T("�ر�"));
	m_comb61.AddString(_T("����������"));
	m_comb61.AddString(_T("������������"));
	m_comb61.SetCurSel(-1);

	m_comb81.AddString(_T("1017"));
	m_comb81.AddString(_T("1018"));
	m_comb81.AddString(_T("1019"));
	m_comb81.AddString(_T("1020"));
	m_comb81.SetCurSel(-1);

	m_comb71.AddString(_T("����Ƶ������"));
	m_comb71.AddString(_T("��ֹƵ������"));
	m_comb71.AddString(_T("ʹ��Ƶ������"));
	m_comb71.AddString(_T("����Ƶ������"));
	m_comb71.AddString(_T("���Ƶ��������ʷ"));
	m_comb71.SetCurSel(-1);


	SetWindowTheme(GetDlgItem(IDC_GROUP1)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP2)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP3)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP4)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP5)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP6)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP7)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP8)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP9)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP10)->GetSafeHwnd(), _T(""), _T(""));

	SetWindowTheme(GetDlgItem(IDC_STATIC11)->GetSafeHwnd(), _T("1"), _T("2"));
	SetWindowTheme(GetDlgItem(IDC_STATIC12)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC13)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC21)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC22)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC31)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC32)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC33)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC34)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC41)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC42)->GetSafeHwnd(), _T(""), _T(""));
}

void CCKQViewConfig::SetItemEnableF()
{
	m_pictureMap.ShowWindow(SW_HIDE);

	m_btnRead.EnableWindow(FALSE);
	m_btnWrite.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC11)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC12)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC13)->EnableWindow(FALSE);
	m_edit11.EnableWindow(FALSE);
	m_edit12.EnableWindow(FALSE);
	m_comb11.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC21)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC22)->EnableWindow(FALSE);
	m_edit21.EnableWindow(FALSE);
	m_edit22.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP3)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC31)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC32)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC33)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC34)->EnableWindow(FALSE);
	m_edit31.EnableWindow(FALSE);
	m_edit32.EnableWindow(FALSE);
	m_edit33.EnableWindow(FALSE);
	m_comb31.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP4)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC41)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC42)->EnableWindow(FALSE);
	m_comb41.EnableWindow(FALSE);
	m_comb42.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP5)->EnableWindow(FALSE);
	m_edit51.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP6)->EnableWindow(FALSE);
	m_comb61.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP7)->EnableWindow(FALSE);
	m_comb71.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP8)->EnableWindow(FALSE);
	m_comb81.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP9)->EnableWindow(FALSE);
	m_comb91.EnableWindow(FALSE);

	GetDlgItem(IDC_GROUP10)->EnableWindow(FALSE);
	m_edit101.EnableWindow(FALSE);
}

void CCKQViewConfig::MoveMap(int nID)
{
	CRect rect;
	GetDlgItem(nID)->GetWindowRect(&rect); 
	ScreenToClient(&rect);
	rect.top += 8;
	m_pictureMap.ShowWindow(SW_SHOW);
	m_pictureMap.MoveWindow(&rect);
}

void CCKQViewConfig::OnSelchangeListType()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	SetItemEnableF();
	switch(m_listType.GetCurSel())
	{
	case 2://ģ������
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTCCO:
		case CONNECTSTA:
			m_btnWrite.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		break;
	case 3://������
		switch (pMain->m_nConnectType)
		{
		case CONNECTCCO:
			m_btnWrite.EnableWindow(TRUE);
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("������CCO"));
			#if (0==LOOPTEST)
			 return;
			#endif
		}
		GetDlgItem(IDC_GROUP6)->EnableWindow(TRUE);
		m_comb61.EnableWindow(TRUE);
		MoveMap(IDC_GROUP6);
		break;
	case 4://����״̬
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTCCO:
		case CONNECTSTA:
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC21)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC22)->EnableWindow(TRUE);
		m_edit21.EnableWindow(TRUE);
		m_edit22.EnableWindow(TRUE);
		MoveMap(IDC_GROUP2);
		break;
	case 5://�豸��ַ����Ʒ״̬
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTCCO:
		case CONNECTSTA:
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP3)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC31)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC32)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC33)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC34)->EnableWindow(TRUE);
		m_edit31.EnableWindow(TRUE);
		m_edit32.EnableWindow(TRUE);
		m_edit33.EnableWindow(TRUE);
		m_comb31.EnableWindow(TRUE);
		MoveMap(IDC_GROUP3);
		break;
	case 6://����·
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTSTA:
			m_btnRead.EnableWindow(TRUE);
			break;
		case CONNECTCCO:
			m_btnRead.EnableWindow(TRUE);
			m_btnWrite.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP4)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC41)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC42)->EnableWindow(TRUE);
		m_comb41.EnableWindow(TRUE);
		m_comb42.EnableWindow(TRUE);
		MoveMap(IDC_GROUP4);
		break;
	case 7://ģ������ʱ��
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTCCO:
		case CONNECTSTA:
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP5)->EnableWindow(TRUE);
		m_edit51.EnableWindow(TRUE);
		MoveMap(IDC_GROUP5);
		break;
	case 8://˥��ģʽ
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
			m_btnWrite.EnableWindow(TRUE);
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP9)->EnableWindow(TRUE);
		m_comb91.EnableWindow(TRUE);
		MoveMap(IDC_GROUP9);
		break;
	case 9://ģ��汾��ѯ
		switch (pMain->m_nConnectType)
		{
		case CONNECTCKQ:
		case CONNECTCCO:
		case CONNECTSTA:
			m_btnRead.EnableWindow(TRUE);
			break;
		default:
			AfxMessageBox(_T("�����ӳ�����"));
			return;
		}
		GetDlgItem(IDC_GROUP10)->EnableWindow(TRUE);
		m_edit101.EnableWindow(TRUE);
		MoveMap(IDC_GROUP10);
		break;
	}
}

void CCKQViewConfig::OnBnClickedButtonClian()
{
	m_comb11.SetCurSel(-1);
	m_comb31.SetCurSel(-1);
	m_comb41.SetCurSel(-1);
	m_comb42.SetCurSel(-1);
	m_comb61.SetCurSel(-1);
	m_comb71.SetCurSel(-1);
	m_comb81.SetCurSel(-1);
	m_comb91.SetCurSel(-1);
	m_edit11.SetWindowText(_T(""));
	m_edit12.SetWindowText(_T(""));
	m_edit21.SetWindowText(_T(""));
	m_edit22.SetWindowText(_T(""));
	m_edit31.SetWindowText(_T(""));
	m_edit32.SetWindowText(_T(""));
	m_edit33.SetWindowText(_T(""));
	m_edit51.SetWindowText(_T(""));
	m_edit101.SetWindowText(_T(""));
}
//#ifdef _STD_CSG  //������׼
void CCKQViewConfig::DisplayDataToView(sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2)
{
	m_edit101.SetWindowText(_T(""));
	switch (m_listType.GetCurSel())
	{
	case 2://ģ������
		break;
	case 3://������
		if (m_nRorW == 1)
		{
			if (ptRecvQCSG376_2.s_RcvDataBuf[0] == 0x55)
			{
				m_comb61.SetCurSel(1);
			}
			else
			{
				m_comb61.SetCurSel(0);
			}
			m_edit101.SetWindowText(_T("��ѯ�������ɹ�"));
		}
		else if(m_nRorW == 2)
		{
			m_edit101.SetWindowText(_T("���ð������ɹ�"));
		}
		break;
	case 4://����״̬
		break;
	case 5://�豸��ַ�����Ʒ״̬
		break;
	case 6://������
		break;
	case 7://ģ������ʱ��
		break;
	case 8://˥��ģʽ
		break;
	case 9://ģ��汾��ѯ
		m_edit101.SetWindowText(m_display.DisplayShowMessage(_T("ascii,f,2;ascii,f,2;char,r,3,0;char,r,2,0;") , _T("���̴���:%&&;оƬ����:%&&;�汾���ڣ������գ�:%&;�汾:%&;") , ptRecvQCSG376_2.s_RcvDataBuf , ptRecvQCSG376_2.s_RcvDataLen ));
		break;
	}
}
//#endif
void CCKQViewConfig::DisplayDataToView(sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2)
{
	m_edit101.SetWindowText(_T(""));
	switch (m_listType.GetCurSel())
	{
	case 2://ģ������
		m_edit101.SetWindowText(_T("·�������ɹ�"));
		break;
	case 3://������
		if (m_nRorW == 1)
		{
			if (ptRecvQGDW376_2.s_RcvDataBuf[0] == 0x55)
			{
				m_comb61.SetCurSel(1);
			}
			else
			{
				m_comb61.SetCurSel(0);
			}
			m_edit101.SetWindowText(_T("��ѯ�������ɹ�"));
		}
		else if(m_nRorW == 2)
		{
			m_edit101.SetWindowText(_T("���ð������ɹ�"));
		}
		break;
	case 4://����״̬
		break;
	case 5://�豸��ַ�����Ʒ״̬
		break;
	case 6://������
		break;
	case 7://ģ������ʱ��
		break;
	case 8://˥��ģʽ
		break;
	case 9://ģ��汾��ѯ
		m_edit101.SetWindowText(m_display.DisplayShowMessage(_T("ascii,f,2;ascii,f,2;char,r,3,0;char,r,2,0;") , _T("���̴���:%&&;оƬ����:%&&;�汾���ڣ������գ�:%&;�汾:%&;") , ptRecvQGDW376_2.s_RcvDataBuf , ptRecvQGDW376_2.s_RcvDataLen ));
		break;
	}
}

//#ifdef _STD_CSG  //������׼
bool CCKQViewConfig::GetDataToSturt(INT8U &DstAFN , INT32U &DstFN , INT8U * DstBuf , INT16U & DstBuflen)
{
	switch (m_listType.GetCurSel())
	{
	case 2://ģ������
//		DstAFN = 0x12;
//		DstFN = FN_F0_F1;
//		DstBuf = NULL;
//		DstBuflen = 0;
		break;
	case 3://������
		if (m_nRorW == 1)
		{
			DstAFN = 0xF0;
			DstFN = FN_F0_F17;
			DstBuf = NULL;
			DstBuflen = 0;
		}
		else if(m_nRorW == 2)
		{
			DstAFN = 0xF0;
			DstFN = FN_F0_F16;
			switch(m_comb61.GetCurSel())
			{
			case 0:
				DstBuf[0] = 0xAA;
				break;
			case 1:
			case 2:
				DstBuf[0] = 0x55;
				break;
			default:
				AfxMessageBox(_T("��ѡ���������������!"));
				return false;
			}
			DstBuflen = 1;
		}
		break;
	case 4://����״̬
		break;
	case 5://�豸��ַ�����Ʒ״̬
		break;
	case 6://������
		break;
	case 7://ģ������ʱ��
		break;
	case 8://˥��ģʽ
		break;
	case 9://ģ��汾��ѯ
		DstAFN = 0x03;
		DstFN = FN_03_F1;
		DstBuf = NULL;
		DstBuflen = 0;
		break;
	}
	return true;
}
//#endif
bool CCKQViewConfig::GetDataToSturt(INT8U &DstAFN , INT16U &DstFN , INT8U * DstBuf , INT16U & DstBuflen)
{
	switch (m_listType.GetCurSel())
	{
	case 2://ģ������
		DstAFN = 0x12;
		DstFN = F1;
		DstBuf = NULL;
		DstBuflen = 0;
		break;
	case 3://������
		if (m_nRorW == 1)
		{
			DstAFN = 0xF0;
			DstFN = F17;
			DstBuf = NULL;
			DstBuflen = 0;
		}
		else if(m_nRorW == 2)
		{
			DstAFN = 0xF0;
			DstFN = F16;
			switch(m_comb61.GetCurSel())
			{
			case 0:
				DstBuf[0] = 0xAA;
				break;
			case 1:
			case 2:
				DstBuf[0] = 0x55;
				break;
			default:
				AfxMessageBox(_T("��ѡ���������������!"));
				return false;
			}
			DstBuflen = 1;
		}
		break;
	case 4://����״̬
		break;
	case 5://�豸��ַ�����Ʒ״̬
		break;
	case 6://������
		break;
	case 7://ģ������ʱ��
		break;
	case 8://˥��ģʽ
		break;
	case 9://ģ��汾��ѯ
		DstAFN = 0x03;
		DstFN = F1;
		DstBuf = NULL;
		DstBuflen = 0;
		break;
	}
	return true;
}

DWORD WINAPI ThreadSendConfig (PVOID pParam) 
{
	//CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	//if(pMain->NW_OR_GW==1)
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewConfig * pView = (CCKQViewConfig *)pParam;


	if (pMain->NW_OR_GW==1){ //������׼
		sPartQCSG376_2CreatFrame ptSendQCSG376_2;
		sPartQCSG376_2DeCodeFrame ptRecvQCSGF0376_2;
		sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;
		INT16U u16temp = 0 , u16BeginNumb = 0 ,SendDatalen = 0 ,temp16 = 0 ;
		INT16U u32FN = 0;
		INT8U SendDatabuf[10] , ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0 , u8AFN = 0;
		pView->GetDataToSturt(u8AFN , u32FN , SendDatabuf , SendDatalen);
		switch (pMain->m_nConnectType)
		{
		case 1:
			break;
		case 2:
			pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , u8AFN , u32FN , SendDatabuf , SendDatalen , ptSendQCSG376_2 , ptRecvQCSGF0376_2 , ptRecvQCSG376_2);
			switch (ack)
			{
			case 0:
				pView->DisplayDataToView(ptRecvQCSG376_2);
				break;
			}
			break;
		case 3:
			break;
		}
	}
    else if (pMain->NW_OR_GW==0){
		sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
		INT16U u16temp = 0 , u16BeginNumb = 0 ,SendDatalen = 0 ,temp16 = 0 , u16FN = 0;
		INT8U SendDatabuf[10] , ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0 , u8AFN = 0;
		pView->GetDataToSturt(u8AFN , u16FN , SendDatabuf , SendDatalen);
		switch (pMain->m_nConnectType)
		{
		case 1:
			break;
		case 2:
			pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , u8AFN , u16FN , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDWF0376_2 , ptRecvQGDW376_2);
			switch (ack)
			{
			case 0:
				pView->DisplayDataToView(ptRecvQGDW376_2);
				break;
			}
			break;
		case 3:
			break;
		}
	}
	return 0;
}
void CCKQViewConfig::OnBnClickedButtonRead()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected == TRUE)
	{
		m_nRorW = 1;
		m_hThreadsend = CreateThread (NULL,0,ThreadSendConfig,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("�������ӳ�������"));
	}
}

void CCKQViewConfig::OnBnClickedButtonWrite()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected == TRUE)
	{
		m_nRorW = 2;
		m_hThreadsend = CreateThread (NULL,0,ThreadSendConfig,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("�������ӳ�������"));
	}
}
