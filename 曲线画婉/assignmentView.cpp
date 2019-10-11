
// assignmentView.cpp : CassignmentView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CassignmentView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CassignmentView ����/����

CassignmentView::CassignmentView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CassignmentView ����

void CassignmentView::OnDraw(CDC* pDC)
{
	CassignmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DoubleBuffer(pDC);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CassignmentView ��ӡ


void CassignmentView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CassignmentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CassignmentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CassignmentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CassignmentView ���

#ifdef _DEBUG
void CassignmentView::AssertValid() const
{
	CView::AssertValid();
}

void CassignmentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CassignmentDoc* CassignmentView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CassignmentDoc)));
	return (CassignmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CassignmentView ��Ϣ�������

void CassignmentView::DoubleBuffer(CDC*pDC)
{
	CRect rect;//�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������Χ,x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//�ͻ�������Ϊԭ��
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
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	ReleaseDC(&memDC);//�ͷ��ڴ�
}
void CassignmentView::Draw(CDC*pDC)
{
	//revolution.DrawRevolution(pDC);
	revolution44.DrawRevolution1(pDC);
}
void CassignmentView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
