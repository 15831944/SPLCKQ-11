#pragma once


// CCKQTabViewTPshow ��ͼ

class CCKQTabViewTPshow : public CTabView
{
	DECLARE_DYNCREATE(CCKQTabViewTPshow)

protected:
	CCKQTabViewTPshow();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCKQTabViewTPshow();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


