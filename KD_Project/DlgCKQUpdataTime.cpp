// DlgCKQUpdataTime.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgCKQUpdataTime.h"
#include "afxdialogex.h"


// CDlgCKQUpdataTime �Ի���

IMPLEMENT_DYNAMIC(CDlgCKQUpdataTime, CDialogEx)

CDlgCKQUpdataTime::CDlgCKQUpdataTime(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCKQUpdataTime::IDD, pParent)
{

}

CDlgCKQUpdataTime::~CDlgCKQUpdataTime()
{
}

void CDlgCKQUpdataTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCKQUpdataTime, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCKQUpdataTime::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCKQUpdataTime ��Ϣ�������


void CDlgCKQUpdataTime::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT_TIME)->GetWindowText(m_strTime);
	CDialogEx::OnOK();
}


BOOL CDlgCKQUpdataTime::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT_TIME)->SetWindowText(_T("10"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
