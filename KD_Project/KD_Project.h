
// KD_Project.h : KD_Project Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "User_gDefine.h"

// CKD_ProjectApp:
// �йش����ʵ�֣������ KD_Project.cpp
//

class CKD_ProjectApp : public CWinAppEx
{
public:
	CKD_ProjectApp();


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

extern CKD_ProjectApp theApp;
