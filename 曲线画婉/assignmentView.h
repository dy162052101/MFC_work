
// assignmentView.h : CassignmentView ��Ľӿ�
//

#pragma once
#include"Revolution.h"
#include"Transform.h"
#include"NurbsSurface.h"
#include"Revolution1.h"
#include"Revolution2.h"
class CassignmentView : public CView
{
protected: // �������л�����
	CassignmentView();
	DECLARE_DYNCREATE(CassignmentView)

// ����
public:
	CassignmentDoc* GetDocument() const;

// ����
public:
	void DoubleBuffer(CDC*pDC);
	void Draw(CDC*pDC);
	void ReadPoint1(void);
	void ReadPoint2(void);
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
	virtual ~CassignmentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double Alpha,Beta;
	double X,Y,Z;
	double **W;
	double a;
	int m,n;
	int q,p;
	CRevolution revolution,revolution1,revolution2,revolution3;
	CTransform tran,tran1,tran2,tran3;
	CRevolution1 revolution44;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // assignmentView.cpp �еĵ��԰汾
inline CassignmentDoc* CassignmentView::GetDocument() const
   { return reinterpret_cast<CassignmentDoc*>(m_pDocument); }
#endif

