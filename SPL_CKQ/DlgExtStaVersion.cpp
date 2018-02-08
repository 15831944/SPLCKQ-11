// DlgExtStaVersion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "DlgExtStaVersion.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"

// DlgExtStaVersion �Ի���

IMPLEMENT_DYNAMIC(DlgExtStaVersion, CDialogEx)

DlgExtStaVersion::DlgExtStaVersion(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgExtStaVersion::IDD, pParent)
{

}

DlgExtStaVersion::~DlgExtStaVersion()
{
}

void DlgExtStaVersion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, FileName1);
}


BEGIN_MESSAGE_MAP(DlgExtStaVersion, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &DlgExtStaVersion::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDCANCEL, &DlgExtStaVersion::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &DlgExtStaVersion::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgExtStaVersion ��Ϣ�������


void DlgExtStaVersion::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString OpenFilePathName;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR);
	int nOK=dlg.DoModal();
	if (nOK == IDOK)
	{
		OpenFilePathName = dlg.GetPathName();
		int len =WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len] ='\0';
		FileName1.SetWindowText(OpenFilePathName);
/*		FILE* fp = NULL;
		fp = fopen(pFileName, "rb");
		fseek(fp,0,SEEK_END);
		long nLen = ftell(fp);
		CString strlong;
		strlong.Format(_T("%d"),nLen);*/
		delete[] pFileName;
	}

}
BOOL DlgExtStaVersion::OnInitDialog(void)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang= 0;
	CString stWhere = _T("ConfigName='��չ�汾��Ϣ'");
	CString strData;
	CString strlist[10];
	int nNumb = 0;
	//if(access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		tools.Split(strData , _T("��") , strlist , nNumb);
		FileName1.SetWindowTextW(strlist[0]);
	}
	else
	{
		AfxMessageBox(_T("��ȡ����ʧ��!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}


void DlgExtStaVersion::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void DlgExtStaVersion::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (FileName1.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("��ѡ�������ļ�"));
		return;
	}
	CString strlistName[2] = {_T("ConfigName") ,_T("MessageData")};
	CString strFile;
	CAccessData access;
	FileName1.GetWindowTextW(strFile);
	
	CString strlistData = strFile + _T("��");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='��չ�汾��Ϣ'");
	//if(!access.UpdataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),strSet , stWhere))
	if(!access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
	{
		AfxMessageBox(_T("���ݱ���ʧ��!"));
		return;
	}
	CDialogEx::OnOK();
}
