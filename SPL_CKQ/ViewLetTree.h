#pragma once

#include "SPL_CKQDoc.h"
// CViewLetTree ��ͼ

class CViewLetTree : public CTreeView
{
	DECLARE_DYNCREATE(CViewLetTree)

protected:
	CViewLetTree();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CViewLetTree();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CImageList m_ilDrives;//ͼƬ�б�
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


