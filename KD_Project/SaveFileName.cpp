// SaveFileName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "SaveFileName.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h

// SaveFileName �Ի���

IMPLEMENT_DYNAMIC(SaveFileName, CDialogEx)

SaveFileName::SaveFileName(CWnd* pParent /*=NULL*/)
	: CDialogEx(SaveFileName::IDD, pParent)
{

}

SaveFileName::~SaveFileName()
{
}

void SaveFileName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_savefilename);
}


BEGIN_MESSAGE_MAP(SaveFileName, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &SaveFileName::OnEnChangeEdit1)
END_MESSAGE_MAP()


// SaveFileName ��Ϣ�������
BOOL SaveFileName::OnInitDialog()
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
	
	//if(access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		m_savefilename.SetWindowTextW(strlist[0]);
	}
	else
	{
		AfxMessageBox(_T("��ȡ����ʧ��!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void SaveFileName::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
