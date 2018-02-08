
// SPL_CKQView.cpp : CSPL_CKQView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SPL_CKQ.h"
#endif

#include "SPL_CKQDoc.h"
#include "SPL_CKQView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSPL_CKQView

IMPLEMENT_DYNCREATE(CSPL_CKQView, CView)

BEGIN_MESSAGE_MAP(CSPL_CKQView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSPL_CKQView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSPL_CKQView ����/����

CSPL_CKQView::CSPL_CKQView()
{
	// TODO: �ڴ˴���ӹ������

}

CSPL_CKQView::~CSPL_CKQView()
{
}

BOOL CSPL_CKQView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSPL_CKQView ����

void CSPL_CKQView::OnDraw(CDC* /*pDC*/)
{
	CSPL_CKQDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSPL_CKQView ��ӡ


void CSPL_CKQView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSPL_CKQView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSPL_CKQView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSPL_CKQView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSPL_CKQView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSPL_CKQView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSPL_CKQView ���

#ifdef _DEBUG
void CSPL_CKQView::AssertValid() const
{
	CView::AssertValid();
}

void CSPL_CKQView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSPL_CKQDoc* CSPL_CKQView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSPL_CKQDoc)));
	return (CSPL_CKQDoc*)m_pDocument;
}
#endif //_DEBUG


// CSPL_CKQView ��Ϣ�������
