
// KD_ProjectDoc.h : CKD_ProjectDoc ��Ľӿ�
//


#pragma once


class CKD_ProjectDoc : public CDocument
{
protected: // �������л�����
	CKD_ProjectDoc();
	DECLARE_DYNCREATE(CKD_ProjectDoc)

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
	virtual ~CKD_ProjectDoc();
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
