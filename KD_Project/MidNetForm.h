#pragma once

#include "DlgNetTP.h"
#include "TPShowFindList.h"
// CMidNetForm ��ͼ

class CMidNetForm : public CView
{
	DECLARE_DYNCREATE(CMidNetForm)

protected:
	CMidNetForm();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMidNetForm();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CTPShowFindList m_TPShowFindList;
	CDlgNetTP * m_pdlgNetTP;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	virtual void OnInitialUpdate();
};


