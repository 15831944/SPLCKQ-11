
// SPL_CKQ.h : SPL_CKQ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "User_gDefine.h"

// CSPL_CKQApp:
// �йش����ʵ�֣������ SPL_CKQ.cpp
//

class CSPL_CKQApp : public CWinAppEx
{
public:
	CSPL_CKQApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CMultiDocTemplate * m_pDocTemplate;
	CMultiDocTemplate * m_pDocTemp3762;
	CMultiDocTemplate * m_pDocTemp698;
// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSPL_CKQApp theApp;
