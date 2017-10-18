
// KD_ProjectView.h : CKD_ProjectView ��Ľӿ�
//

#pragma once


class CKD_ProjectView : public CView
{
protected: // �������л�����
	CKD_ProjectView();
	DECLARE_DYNCREATE(CKD_ProjectView)

// ����
public:
	CKD_ProjectDoc* GetDocument() const;

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
	virtual ~CKD_ProjectView();
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

#ifndef _DEBUG  // KD_ProjectView.cpp �еĵ��԰汾
inline CKD_ProjectDoc* CKD_ProjectView::GetDocument() const
   { return reinterpret_cast<CKD_ProjectDoc*>(m_pDocument); }
#endif

