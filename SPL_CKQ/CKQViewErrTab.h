#pragma once



class CCKQViewErrTab : public CTabView
{
	DECLARE_DYNCREATE(CCKQViewErrTab)

protected:
	CCKQViewErrTab();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCKQViewErrTab();

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
//	afx_msg void OnIdrRbmenuMeterr();
};


