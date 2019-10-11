
// assignmentView.h : CassignmentView 类的接口
//

#pragma once
#include"Revolution.h"
#include"Transform.h"
#include"NurbsSurface.h"
#include"Revolution1.h"
#include"Revolution2.h"
class CassignmentView : public CView
{
protected: // 仅从序列化创建
	CassignmentView();
	DECLARE_DYNCREATE(CassignmentView)

// 特性
public:
	CassignmentDoc* GetDocument() const;

// 操作
public:
	void DoubleBuffer(CDC*pDC);
	void Draw(CDC*pDC);
	void ReadPoint1(void);
	void ReadPoint2(void);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // assignmentView.cpp 中的调试版本
inline CassignmentDoc* CassignmentView::GetDocument() const
   { return reinterpret_cast<CassignmentDoc*>(m_pDocument); }
#endif

