#pragma once



// CNetViewRepeat ������ͼ

class CNetViewRepeat : public CFormView
{
	DECLARE_DYNCREATE(CNetViewRepeat)

protected:
	CNetViewRepeat();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CNetViewRepeat();

public:
	enum { IDD = IDD_DIALOG_REPEAT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


