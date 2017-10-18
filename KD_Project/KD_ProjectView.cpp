
// KD_ProjectView.cpp : CKD_ProjectView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "KD_Project.h"
#endif

#include "KD_ProjectDoc.h"
#include "KD_ProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKD_ProjectView

IMPLEMENT_DYNCREATE(CKD_ProjectView, CView)

BEGIN_MESSAGE_MAP(CKD_ProjectView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKD_ProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CKD_ProjectView ����/����

CKD_ProjectView::CKD_ProjectView()
{
	// TODO: �ڴ˴���ӹ������

}

CKD_ProjectView::~CKD_ProjectView()
{
}

BOOL CKD_ProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKD_ProjectView ����

void CKD_ProjectView::OnDraw(CDC* /*pDC*/)
{
	CKD_ProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKD_ProjectView ��ӡ


void CKD_ProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKD_ProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKD_ProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CKD_ProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CKD_ProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKD_ProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKD_ProjectView ���

#ifdef _DEBUG
void CKD_ProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CKD_ProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKD_ProjectDoc* CKD_ProjectView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKD_ProjectDoc)));
	return (CKD_ProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CKD_ProjectView ��Ϣ�������
