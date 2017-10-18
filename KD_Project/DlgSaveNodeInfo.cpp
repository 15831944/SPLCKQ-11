// DlgSaveNodeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgSaveNodeInfo.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"

// DlgSaveNodeInfo �Ի���

IMPLEMENT_DYNAMIC(DlgSaveNodeInfo, CDialogEx)

DlgSaveNodeInfo::DlgSaveNodeInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSaveNodeInfo::IDD, pParent)
{

}

DlgSaveNodeInfo::~DlgSaveNodeInfo()
{
}

void DlgSaveNodeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, FileName);
}


BEGIN_MESSAGE_MAP(DlgSaveNodeInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &DlgSaveNodeInfo::OnBnClickedButtonOpen)
	ON_EN_CHANGE(IDC_EDIT_FILE, &DlgSaveNodeInfo::OnEnChangeEditFile)
	ON_BN_CLICKED(IDOK, &DlgSaveNodeInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSaveNodeInfo ��Ϣ�������


void DlgSaveNodeInfo::OnBnClickedButtonOpen()
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
		FileName.SetWindowText(OpenFilePathName);
		delete[] pFileName;
	}
	
}


void DlgSaveNodeInfo::OnEnChangeEditFile()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void DlgSaveNodeInfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (FileName.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("��ѡ�������ļ�"));
		return;
	}
	CString strlistName[2] = {_T("ConfigName") ,_T("MessageData")};
	CString strFile;
	CAccessData access;
	FileName.GetWindowTextW(strFile);
	
	CString strlistData = strFile + _T("��");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='�ڵ���Ϣ'");
	//if(!access.UpdataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),strSet , stWhere))
	if(!access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
	{
		AfxMessageBox(_T("���ݱ���ʧ��!"));
		return;
	}

	CDialogEx::OnOK();
}


BOOL DlgSaveNodeInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang= 0;
	CString stWhere = _T("ConfigName='�ڵ���Ϣ'");
	CString strData;
	CString strlist[10];
	int nNumb = 0;
	//if(access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		tools.Split(strData , _T("��") , strlist , nNumb);
		FileName.SetWindowTextW(strlist[0]);
	}
	else
	{
		AfxMessageBox(_T("��ȡ����ʧ��!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
