#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

// ���в������ CFrameSetNet ���

class CFrameSetNet : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CFrameSetNet)
protected:
	CFrameSetNet();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFrameSetNet();

protected:
	//virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:

	CSplitterWnd m_wndSplitter;
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
//	afx_msg void OnIdrRbmenuMeterr();
};


