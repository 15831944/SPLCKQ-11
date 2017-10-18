// Dlg13762Frame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "Dlg13762Frame.h"
#include "afxdialogex.h"


// CDlg13762Frame �Ի���

IMPLEMENT_DYNAMIC(CDlg13762Frame, CDialogEx)

CDlg13762Frame::CDlg13762Frame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg13762Frame::IDD, pParent)
{

}

CDlg13762Frame::~CDlg13762Frame()
{
}

void CDlg13762Frame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_C1, m_combC1);
	DDX_Control(pDX, IDC_COMBO_C2, m_combC2);
	DDX_Control(pDX, IDC_COMBO_C3, m_combC3);
	DDX_Control(pDX, IDC_COMBO_M1, m_combM1);
	DDX_Control(pDX, IDC_COMBO_M2, m_combM2);
	DDX_Control(pDX, IDC_COMBO_M3, m_combM3);
	DDX_Control(pDX, IDC_COMBO_M4, m_combM4);
	DDX_Control(pDX, IDC_COMBO_M5, m_combM5);
	DDX_Control(pDX, IDC_COMBO_M6, m_combM6);
	DDX_Control(pDX, IDC_COMBO_M9, m_combM9);
	DDX_Control(pDX, IDC_COMBOM_7, m_combM7);
	DDX_Control(pDX, IDC_COMBOM_8, m_combM8);
	DDX_Control(pDX, IDC_EDIT_A1, m_editA1);
	DDX_Control(pDX, IDC_EDIT_A2, m_editA2);
	DDX_Control(pDX, IDC_EDIT_A3, m_editA3);
	DDX_Control(pDX, IDC_EDIT_FN, m_editFN);
	DDX_Control(pDX, IDC_EDIT_M1, m_editM1);
	DDX_Control(pDX, IDC_EDIT_M2, m_editM2);
	DDX_Control(pDX, IDC_EDITDATA, m_editData);
	DDX_Control(pDX, IDC_COMBO_AFN, m_combAFN);
}


BEGIN_MESSAGE_MAP(CDlg13762Frame, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlg13762Frame ��Ϣ�������


BOOL CDlg13762Frame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpDataData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlg13762Frame::UpDataData()
{
	m_combC1.AddString(_T("0:����"));
	m_combC1.AddString(_T("1:����"));
	m_combC1.SetCurSel(0);

	m_combC2.AddString(_T("0:�Ӷ�"));
	m_combC2.AddString(_T("1:����"));
	m_combC2.SetCurSel(1);

	m_combC3.AddString(_T("1:����ʽ·���ز�"));
	m_combC3.AddString(_T("2:�ֲ�ʽ·���ز�"));
	m_combC3.AddString(_T("3:����ز�"));
	m_combC3.AddString(_T("10:΢��������"));
	m_combC3.AddString(_T("20:��̫��"));
	m_combC3.SetCurSel(2);

	m_combM1.AddString(_T("0:��"));
	m_combM1.AddString(_T("1:��"));
	m_combM1.SetCurSel(0);

	m_combM2.AddString(_T("0:��"));
	m_combM2.AddString(_T("1:��"));
	m_combM2.SetCurSel(0);

	m_combM3.AddString(_T("0:��"));
	m_combM3.AddString(_T("1:��"));
	m_combM3.SetCurSel(0);

	m_combM4.AddString(_T("0:��"));
	m_combM4.AddString(_T("1:��"));
	m_combM4.SetCurSel(0);

	m_combM5.AddString(_T("0:��"));
	m_combM5.AddString(_T("1:"));
	m_combM5.AddString(_T("2:"));
	m_combM5.AddString(_T("3:"));
	m_combM5.AddString(_T("4:"));
	m_combM5.AddString(_T("5:"));
	m_combM5.AddString(_T("6:"));
	m_combM5.AddString(_T("7:"));
	m_combM5.AddString(_T("8:"));
	m_combM5.AddString(_T("9:"));
	m_combM5.AddString(_T("10:"));
	m_combM5.AddString(_T("11:"));
	m_combM5.AddString(_T("12:"));
	m_combM5.AddString(_T("13:"));
	m_combM5.AddString(_T("14:"));
	m_combM5.AddString(_T("15:"));
	m_combM5.SetCurSel(0);

	m_combM6.AddString(_T("0:��"));
	m_combM6.AddString(_T("1:"));
	m_combM6.AddString(_T("2:"));
	m_combM6.AddString(_T("3:"));
	m_combM6.AddString(_T("4:"));
	m_combM6.AddString(_T("5:"));
	m_combM6.AddString(_T("6:"));
	m_combM6.AddString(_T("7:"));
	m_combM6.AddString(_T("8:"));
	m_combM6.AddString(_T("9:"));
	m_combM6.AddString(_T("10:"));
	m_combM6.AddString(_T("11:"));
	m_combM6.AddString(_T("12:"));
	m_combM6.AddString(_T("13:"));
	m_combM6.AddString(_T("14:"));
	m_combM6.AddString(_T("15:"));
	m_combM6.SetCurSel(0);

	m_combM7.AddString(_T("0:��"));
	m_combM7.AddString(_T("1:RS"));
	m_combM7.SetCurSel(0);

	m_editM1.SetWindowTextW(_T("0"));
	
	m_combM8.AddString(_T("0:Ĭ��"));
	m_combM8.SetCurSel(0);

	m_combM9.AddString(_T("0:bit/s"));
	m_combM9.AddString(_T("1:kbit/s"));
	m_combM9.SetCurSel(0);

	m_editM2.SetWindowTextW(_T("0"));

	m_editA1.SetWindowTextW(_T("BEBEBEBEBE01"));
	m_editA1.SetLimitText(12);
	m_editA3.SetWindowTextW(_T("0F0E0D0C0B0A "));
	m_editA3.SetLimitText(12);
	m_editData.SetWindowTextW(_T(""));

	m_combAFN.AddString(_T("00:ȷ�Ϸ���"));
	m_combAFN.AddString(_T("01:��ʼ��"));
	m_combAFN.AddString(_T("02:����ת��"));
	m_combAFN.AddString(_T("03:��ѯ����"));
	m_combAFN.AddString(_T("04:��·�ӿڼ��"));
	m_combAFN.AddString(_T("05:��������"));
	m_combAFN.AddString(_T("06:�����ϱ�"));
	m_combAFN.AddString(_T("10:·�ɲ�ѯ"));
	m_combAFN.AddString(_T("11:·������"));
	m_combAFN.AddString(_T("12:·�ɿ���"));
	m_combAFN.AddString(_T("13:·������ת��"));
	m_combAFN.AddString(_T("14:·�����ݳ���"));
	m_combAFN.AddString(_T("15:�ļ�����"));
	m_combAFN.AddString(_T("F0:��չ����"));
	m_combAFN.SetCurSel(3);

	m_editFN.SetWindowTextW(_T("F4"));
}


void CDlg13762Frame::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	KongjianSize(IDC_STATIC1,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC2,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC3,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC4,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC5,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC6,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC7,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC8,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC9,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC10,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC11,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC12,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC13,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC14,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC15,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC16,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC17,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC18,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC19,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC20,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC21,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC22,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC23,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC24,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_C1,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_C2,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_C3,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_M1,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M2,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M3,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M4,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M5,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M6,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBOM_7,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBOM_8,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M9,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_M1,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_M2,rect.right,rect.bottom); 

	KongjianSize(IDC_EDIT_A1,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_A2,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_A3,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_AFN,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_FN,rect.right,rect.bottom); 
	KongjianSize(IDC_EDITDATA,rect.right,rect.bottom); 

	GetClientRect(m_cRect);
	// TODO: �ڴ˴������Ϣ����������
}
void CDlg13762Frame::KongjianSize(int nID, int cx, int cy, bool bComb)
{
	CWnd *pWnd;  
	pWnd = GetDlgItem(nID);     //��ȡ�ؼ���� 
	int fcx=0,fcy=0;
	int nBottom = 0;
	if (bComb == true)
	{
		nBottom = 100;
	}
	if(pWnd)    
	{ 
		CRect rect;   //��ȡ�ؼ��仯ǰ��С 
		pWnd->GetWindowRect(&rect); 
		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е��������� 
		fcx=m_cRect.right;
		fcy=m_cRect.bottom;
		rect.left=(int)(rect.left*((float)cx/(float)fcx));//�����ؼ���С 
		rect.right=(int)(rect.right*((float)cx/(float)fcx)); 
		rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy)) + nBottom;
		pWnd->MoveWindow(rect);//���ÿؼ�λ�� 
	}
}