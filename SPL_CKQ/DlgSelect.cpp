// DlgSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "DlgSelect.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// DlgSelect �Ի���

IMPLEMENT_DYNAMIC(DlgSelect, CDialogEx)

DlgSelect::DlgSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSelect::IDD, pParent)
{

}

DlgSelect::~DlgSelect()
{
}

void DlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NW_GW, m_NW_GW);
}




BEGIN_MESSAGE_MAP(DlgSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSelect ��Ϣ�������
BOOL DlgSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	AddData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void DlgSelect::AddData()
{
	m_NW_GW.AddString(_T("����"));
	m_NW_GW.AddString(_T("����"));
	m_NW_GW.SetCurSel(0);
}

void DlgSelect::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(m_NW_GW.GetCurSel()==0)
	{
	pMain->NW_OR_GW=0;
	}
	if(m_NW_GW.GetCurSel()==1)
	{
	pMain->NW_OR_GW=1;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
