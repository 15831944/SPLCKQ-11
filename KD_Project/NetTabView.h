#pragma once


// CNetTabView ��ͼ

class CNetTabView : public CTabView
{
	DECLARE_DYNCREATE(CNetTabView)

protected:
	CNetTabView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CNetTabView();

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
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


