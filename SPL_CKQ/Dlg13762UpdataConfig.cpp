// Dlg13762UpdataConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "Dlg13762UpdataConfig.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"

// CDlg13762UpdataConfig �Ի���

IMPLEMENT_DYNAMIC(CDlg13762UpdataConfig, CDialogEx)

CDlg13762UpdataConfig::CDlg13762UpdataConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg13762UpdataConfig::IDD, pParent)
{

}

CDlg13762UpdataConfig::~CDlg13762UpdataConfig()
{
}

void CDlg13762UpdataConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_SIZE, m_editFile);
	DDX_Control(pDX, IDC_COMBO_BS, m_combBS);
	//  DDX_Control(pDX, IDC_COMBO_SX, m_combSX);
	DDX_Control(pDX, IDC_COMBO_ZL, m_combZL);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_EDIT_FRAMESIZE, m_editFrameSize);
	DDX_Control(pDX, IDC_STATIC_SIZE, m_staticSize);
	DDX_Control(pDX, IDC_CHECK_DX, m_checkDX);
}


BEGIN_MESSAGE_MAP(CDlg13762UpdataConfig, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg13762UpdataConfig::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CDlg13762UpdataConfig::OnBnClickedButtonOpen)
	ON_EN_CHANGE(IDC_EDIT_FILE, &CDlg13762UpdataConfig::OnEnChangeEditFile)
END_MESSAGE_MAP()


// CDlg13762UpdataConfig ��Ϣ�������


void CDlg13762UpdataConfig::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (m_editFile.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("��ѡ�������ļ�"));
		return;
	}
	CString strlistName[2] = {_T("ConfigName") ,_T("MessageData")};
	CString strFile , strFrameSize , strBS , strZL , strDX;
	CAccessData access;
	m_editFile.GetWindowTextW(strFile);
	m_editFrameSize.GetWindowTextW(strFrameSize);
	m_combBS.GetWindowTextW(strBS);
	strBS.Mid(0,2);
	m_combZL.GetWindowTextW(strZL);
	strZL.Mid(0,2);
	if(m_checkDX.GetCheck())
	{
		strDX = _T("1");
	}
	else
	{
		strDX = _T("0");
	}
	CString strlistData = strFile + _T("��") + strFrameSize + _T("��") + strBS + _T("��") + strZL + _T("��") + strDX + _T("��");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='������Ϣ'");
	//if(!access.UpdataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),strSet , stWhere))
	if(!access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
	{
		AfxMessageBox(_T("���ݱ���ʧ��!"));
		return;
	}
	CDialogEx::OnOK();
}


BOOL CDlg13762UpdataConfig::OnInitDialog()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang= 0;
	CString stWhere = _T("ConfigName='������Ϣ'");
	CString strData;
	CString strlist[10];
	int nNumb = 0;
	m_combBS.AddString(_T("00H:�����װ�ļ�"));
	m_combBS.AddString(_T("03H:����ͨѶģ�������ļ�"));
	m_combBS.AddString(_T("07H:���ڵ���ӽڵ�ģ������"));
	m_combBS.AddString(_T("08H:�ӽڵ�ģ������"));

	m_combZL.AddString(_T("00H:���ķ�ʽ��װ"));
	//m_combZL.AddString(_T("01H��FTP��ʽ����"));
	//m_combZL.AddString(_T("02���������ַ����"));

	//if(access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		tools.Split(strData , _T("��") , strlist , nNumb);
		m_editFile.SetWindowTextW(strlist[0]);
		m_editFrameSize.SetWindowTextW(strlist[1]);
		m_combBS.SetWindowTextW(strlist[2]);
		m_combZL.SetWindowTextW(strlist[3]);
		m_checkDX.SetCheck(_ttoi(strlist[4]));
	}
	else
	{
		AfxMessageBox(_T("��ȡ����ʧ��!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlg13762UpdataConfig::OnBnClickedButtonOpen()
{
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
		m_editFile.SetWindowText(OpenFilePathName);
		FILE* fp = NULL;
		fp = fopen(pFileName, "rb");
		fseek(fp,0,SEEK_END);
		long nLen = ftell(fp);
		CString strlong;
		strlong.Format(_T("%d"),nLen);
		m_staticSize.SetWindowText(strlong);
		delete[] pFileName;
	}
	
}


void CDlg13762UpdataConfig::OnEnChangeEditFile()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
