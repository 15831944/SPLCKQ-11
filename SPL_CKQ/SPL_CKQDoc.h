
// SPL_CKQDoc.h : CSPL_CKQDoc ��Ľӿ�
//


#pragma once


class CSPL_CKQDoc : public CDocument
{
protected: // �������л�����
	CSPL_CKQDoc();
	DECLARE_DYNCREATE(CSPL_CKQDoc)

// ����
public:

// ����
public:
	int m_nTreeChoose;
	CString m_strTreeName;

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CSPL_CKQDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
