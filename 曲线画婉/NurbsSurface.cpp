#include "StdAfx.h"
#include "NurbsSurface.h"
#include<math.h>
#define ROUND(d) int(d+0.5)
const double PI = 3.1415926;

CNurbsSurface::CNurbsSurface(void)
{
	P = NULL;
	W = NULL;
	U = NULL;
	V = NULL;
}


CNurbsSurface::~CNurbsSurface(void)
{
	ReleaseMemory();
}

//�����߳�ʼ��
void CNurbsSurface::Initialize(CP3** CtrlP3, double** W3, int m, int p, int n, int q)
{
	ReleaseMemory();
	this->m = m;	this->p = p; //U��
	this->n = n;	this->q = q; //V��

	P = new CP3*[n+1]; //���ƶ����ά����
	for(int i = 0; i < n+1; i++)
	{
		P[i] = new CP3[m+1];
	}

	W = new double*[n+1]; //����Ȩ���ӵĶ�̬��ά����
	for (int i = 0; i < n+1; i++)
	{
			W[i] = new double[m+1];
	}
	
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
				P[i][j] = CtrlP3[i][j];
		}
	}

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
				W[i][j] = W3[i][j];
		}
	}

	U = new double*[n+1]; //����u��ڵ�ʸ����̬����
	for (int i = 0; i < n + 1; i++)
		U[i] = new double[m + p + 2];

	for (int i = 0; i < n + 1; i++) //u��ڵ�ʸ�����Բ���Ҫ���㣬ֱ�Ӹ�ֵ
	{
		U[i][0] = 0.0; U[i][1] = 0.0; U[i][2] = 0.0; U[i][3] = 0.25; U[i][4] = 0.25; U[i][5] = 0.5;
		U[i][6] = 0.5; U[i][7] = 0.75; U[i][8] = 0.75; U[i][9] = 1.0; U[i][10] = 1.0; U[i][11] = 1.0;
	}

	V = new double*[m+1]; //����V��ڵ�ʸ����̬���飬V��ڵ�ʸ��ʹ�ù������㷨��Ļ��
	for(int i = 0; i < m + 1; i++)
		V[i] = new double[n+ 1 + q + 1];
}


void CNurbsSurface::DrawNurbsSurface(CDC* pDC) //��������
{
	for(int i=0;i<m+1;i++)
		GetKnotVector(V[i],i,n,q);//��ȡ�ڵ�ʸ��V	

	CPen NewPen(PS_SOLID,2,RGB(255,0,0));//������ɫ
	CPen* pOldPen=pDC->SelectObject(&NewPen);
	double Step=0.05;//����
	for(double u=0.0;u<=1.0;u+=Step)
	{
		for(double v=0.0;v<=1.0;v+=Step)
		{
			u=int(u*1000)/1000.0;
			v=int(v*1000)/1000.0;
			CP3 point(0,0,0);
			double weight=0.0;
			for(int i=0;i<n+1;i++)
			{
				for(int j=0;j<m+1;j++)
				{
					double BValueU=BasisFunctionValue(u,j,p,U[i]);
					double BValueV=BasisFunctionValue(v,i,q,V[j]);
					point+=P[i][j]*W[i][j]*BValueU*BValueV;
					weight+=W[i][j]*BValueU*BValueV;
				}
			}
			point/=weight;
			CP2 Point2=OrthogonalProjection(point);//����ͶӰ
			if (v==0.0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
	}
	for(double v=0.0;v<=1.0;v+=Step)
	{
		for(double u=0.0;u<=1.0;u+=Step)
		{
			u=int(u*1000)/1000.0;
			v=int(v*1000)/1000.0;
			CP3 point(0,0,0);
			double weight=0.0;
			for(int i=0;i<n+1;i++)
			{
				for(int j=0;j<m+1;j++)
				{
					
					double BValueU=BasisFunctionValue(u,j,p,U[i]);
					double BValueV=BasisFunctionValue(v,i,q,V[j]);
					point+=P[i][j]*W[i][j]*BValueU*BValueV;
					weight+=W[i][j]*BValueU*BValueV;
				}
			}
			point/=weight;
			CP2 Point2=OrthogonalProjection(point);//бͶӰ
			if (u==0.0)
				pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
			else
				pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
		}
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}

void CNurbsSurface::DrawControlGrid(CDC* pDC) //���ƿ�������
{
	CP2** P2=new CP2*[n+1];
	for(int i=0;i<n+1;i++)
		P2[i]=new CP2[m+1];
	for(int i=0;i<n+1;i++)
		for(int j=0;j<m+1;j++)
			P2[i][j]=OrthogonalProjection(P[i][j]);
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&NewPen);
	CBrush NewBrush(RGB(0,0,0));
	CBrush* pOldBrush=pDC->SelectObject(&NewBrush);
	for(int i=0;i<n+1;i++)//����v���������
	{
		pDC->MoveTo(ROUND(P2[i][0].x),ROUND(P2[i][0].y));
		pDC->Ellipse(ROUND(P2[i][0].x)-5,ROUND(P2[i][0].y)-5,ROUND(P2[i][0].x)+5,ROUND(P2[i][0].y)+5);
		for(int j=1;j<m+1;j++)
		{
			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
			pDC->Ellipse(ROUND(P2[i][j].x)-5,ROUND(P2[i][j].y)-5,ROUND(P2[i][j].x)+5,ROUND(P2[i][j].y)+5);
		}
	}
	for(int j=0;j<m+1;j++)//����u���������
	{
		pDC->MoveTo(ROUND(P2[0][j].x),ROUND(P2[0][j].y));
		for(int i=1;i<n+1;i++)
			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	if(NULL!=P2)
	{
		for(int i=0;i<n+1;i++)
		{
			delete []P2[i];
			P2[i]=NULL;
		}
		delete []P2;
		P2=NULL;
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);	
}
void CNurbsSurface::GetKnotVector(double* T, int nCount, int num, int order) //��ȡ�ڵ�ʸ��
{
	for(int i=0;i<=order;i++) //С�ڵ������ߴ���order�Ľڵ�ֵΪ0
		T[i]=0.0;
	for(int i=num+1;i<=num+order+1;i++)//���ڶ�������1��n���Ľڵ�ֵΪ1
		T[i]=1.0;
	//����num-order���ڽڵ�
	for (int i = order + 1; i <= num; i++)
	{ 
		double sum = 0.0;
		for (int j = order + 1; j <= i; j++)
		{
			double numerator = 0.0; //�������
			for (int loop = j - order; loop <= j-1; loop++)
				numerator += (P[loop][nCount].x - P[loop -1][nCount].x) * (P[loop][nCount].x - P[loop -1][nCount].x)
				 +(P[loop][nCount].y - P[loop -1][nCount].y) * (P[loop][nCount].y - P[loop -1][nCount].y);

			double denumerator = 0.0; //�����ĸ
			for(int loop1=order+1;loop1<=num+1;loop1++)
			{
				for (int loop2 = loop1-order;loop2<=loop1- 1;loop2++)
				{
					denumerator+= (P[loop2][nCount].x - P[loop2 -1][nCount].x) * (P[loop2][nCount].x - 
						P[loop2 -1][nCount].x)+(P[loop2][nCount].y - P[loop2 -1][nCount].y) * (P[loop2][nCount].y-P[loop2 -1][nCount].y);
				}
			}

			if (denumerator < 1e-6)
				denumerator = 1.0;

			sum += numerator /denumerator;

		}

		T[i] = sum;
	}
}

double CNurbsSurface::BasisFunctionValue(double t, int i, int order, double *T) //���������
{
double value1,value2,value;
	if(order==0)
	{
		if(t>=T[i] && t<T[i+1])
			return 1.0;
		else
			return 0.0;
	}
	if(order>0)
	{
		if(t<T[i]||t>T[i+order+1])
			return 0.0;
		else
		{
			double coffcient1,coffcient2;//͹���ϵ��1��͹���ϵ��2
			double denominator=0.0;//��ĸ
			denominator=T[i+order]-T[i];//���ƹ�ʽ��һ���ĸ
			if(denominator==0.0)//Լ��0/0
				coffcient1=0.0;
			else
				coffcient1=(t-T[i])/denominator;
			denominator=T[i+order+1]-T[i+1];//���ƹ�ʽ�ڶ����ĸ
			if(0.0==denominator)//Լ��0/0
				coffcient2=0.0;
			else
				coffcient2=(T[i+order+1]-t)/denominator;
			value1=coffcient1*BasisFunctionValue(t,i,order-1,T);//���ƹ�ʽ��һ���ֵ
			value2=coffcient2*BasisFunctionValue(t,i+1,order-1,T);//���ƹ�ʽ�ڶ����ֵ
			value=value1+value2;//��������ֵ
		}
	}
	return value;

}

CP2 CNurbsSurface::OrthogonalProjection(CP3 pt3) //����ͶӰ
{
	CP2 Point2;
	Point2.x = pt3.x;
	Point2.y = pt3.y;
	
	return Point2;
}

void CNurbsSurface::ReleaseMemory()
{
	if(NULL!=P)
	{
		for(int i=0;i<n+1;i++)
		{
			delete []P[i];
			P[i]=NULL;
		}
		delete []P;
		P=NULL;
	}
	if(NULL!=W)
	{
		for(int i=0;i<n+1;i++)
		{
			delete []W[i];
			W[i]=NULL;
		}
		delete []W;
		W = NULL;
	}
	if(NULL!=U)
	{
		for(int i=0;i<n+1;i++)
		{
			delete []U[i];
			U[i] = NULL;
		}
		delete []U;
		U=NULL;
	}
	if(NULL!=V)
	{
		for(int i=0;i<m+1;i++)
		{
			delete []V[i];
			V[i]=NULL;
		}
		delete []V;
		V=NULL;
	}
}