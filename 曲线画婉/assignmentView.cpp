
// assignmentView.cpp : CassignmentView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "assignment.h"
#endif
#include<math.h>
#include "assignmentDoc.h"
#include "assignmentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CassignmentView

IMPLEMENT_DYNCREATE(CassignmentView, CView)

BEGIN_MESSAGE_MAP(CassignmentView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CassignmentView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CassignmentView 构造/析构

CassignmentView::CassignmentView()
{
	// TODO: 在此处添加构造代码
	Alpha=0;
	Beta=0;
	X=0;
	Y=0;
	ReadPoint1();
	//ReadPoint2();
}

CassignmentView::~CassignmentView()
{
}
void CassignmentView::ReadPoint1(void)
{
	double r=200,R=100;
	int n,q;
	n=9;q=3;
	CP2 P2[10];
	P2[0]=CP2(0,-188);
	P2[1]=CP2(163,-188);
	P2[2]=CP2(163,-162);
	P2[3]=CP2(163,-162);
	P2[4]=CP2(469,-43);
	P2[5]=CP2(469,-43);
	P2[6]=CP2(283,-88);
	P2[7]=CP2(174,-134);
	P2[8]=CP2(0,-123);
	P2[9]=CP2(0,-123);
	double W2[10];
	W2[0]=1.0;
	W2[1]=2.0;
	W2[2]=2.0;
	W2[3]=2.0;
	W2[4]=2.0;
	W2[5]=2.0;
	W2[6]=2.0;
	W2[7]=2;
	W2[8]=2;
	W2[9]=1;
	revolution44.ReadNurbsControlPoint(P2,W2,n,q);
	tran.SetMat(revolution44.Vertex,9*(n+1));
}
void CassignmentView::ReadPoint2(void)
{
	double r=200,R=100;
	int n,q;
	n=4;q=3;
	CP2 P2[10];
	P2[0]=CP2(0,0);
	P2[1]=CP2(60*2,0);
	P2[2]=CP2(60*2,20*2);
	P2[3]=CP2(60*2,40*2);
	P2[4]=CP2(0,40*2);
	/*P2[5]=CP2(50,-80);
	P2[6]=CP2(0,-90);
	P2[7]=CP2(50,-100);
	P2[8]=CP2(0,-110);
	P2[9]=CP2(0,-120);*/
	double W2[10];
	W2[0]=1.0;
	W2[1]=4.0;
	W2[2]=4.0;
	W2[3]=4.0;
	W2[4]=1.0;
	/*W2[5]=2.0;
	W2[6]=2.0;
	W2[7]=2;
	W2[8]=2;
	W2[9]=1;*/
	revolution44.ReadNurbsControlPoint(P2,W2,n,q);
	tran1.SetMat(revolution44.Vertex,9*(n+1));
}


BOOL CassignmentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CassignmentView 绘制

void CassignmentView::OnDraw(CDC* pDC)
{
	CassignmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DoubleBuffer(pDC);
	// TODO: 在此处为本机数据添加绘制代码
}

// CassignmentView 打印


void CassignmentView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CassignmentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CassignmentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CassignmentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CassignmentView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CassignmentView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CassignmentView 诊断

#ifdef _DEBUG
void CassignmentView::AssertValid() const
{
	CView::AssertValid();
}

void CassignmentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CassignmentDoc* CassignmentView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CassignmentDoc)));
	return (CassignmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CassignmentView 消息处理程序

void CassignmentView::DoubleBuffer(CDC*pDC)
{
	CRect rect;//定义矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//客户区中心为原点
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap,*pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap=memDC.SelectObject(&NewBitmap);
	memDC.FillSolidRect(rect,RGB(255,255,225));
	memDC.SetMapMode(MM_ANISOTROPIC);
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	Draw(&memDC);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	ReleaseDC(&memDC);//释放内存
}
void CassignmentView::Draw(CDC*pDC)
{
	//revolution.DrawRevolution(pDC);
	revolution44.DrawRevolution1(pDC);
}
void CassignmentView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
		{
		case VK_UP:
			Alpha=+25;
			tran.RotateX(Alpha);
			//tran1.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha=-25;
			tran.RotateX(Alpha);
			//tran1.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta=-25;
			tran.RotateY(Beta);
			//tran1.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta=25;
			tran.RotateY(Beta);
			//tran1.RotateY(Beta);
			break;
		default:
			break;			
		}
		Invalidate(false);	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
