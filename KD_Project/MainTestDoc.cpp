// MainTestDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MainTestDoc.h"


// CMainTestDoc

IMPLEMENT_DYNCREATE(CMainTestDoc, CDocument)

CMainTestDoc::CMainTestDoc()
{
}

BOOL CMainTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMainTestDoc::~CMainTestDoc()
{
}


BEGIN_MESSAGE_MAP(CMainTestDoc, CDocument)
END_MESSAGE_MAP()


// CMainTestDoc ���

#ifdef _DEBUG
void CMainTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CMainTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CMainTestDoc ���л�

void CMainTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CMainTestDoc ����
