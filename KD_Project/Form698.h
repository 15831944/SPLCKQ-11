#pragma once


// CForm698 ���

class CForm698 : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CForm698)
protected:
	CForm698();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CForm698();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


