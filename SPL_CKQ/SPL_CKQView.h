
// SPL_CKQView.h : CSPL_CKQView ��Ľӿ�
//

#pragma once


class CSPL_CKQView : public CView
{
protected: // �������л�����
	CSPL_CKQView();
	DECLARE_DYNCREATE(CSPL_CKQView)

// ����
public:
	CSPL_CKQDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSPL_CKQView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SPL_CKQView.cpp �еĵ��԰汾
inline CSPL_CKQDoc* CSPL_CKQView::GetDocument() const
   { return reinterpret_cast<CSPL_CKQDoc*>(m_pDocument); }
#endif

