#include "StdAfx.h"
#include "Revolution2.h"
#include<math.h>
#define Round(d) int(d+0.5)
//#define NULL 0

CRevolution2::CRevolution2(void)
{
	Vertex=NULL;
	Weight=NULL;
}


CRevolution2::~CRevolution2(void)
{
	RelaseMemory();
}
void CRevolution2::RelaseMemory()
{
	if(NULL!=Vertex)
	{
		delete[]Vertex;
		Vertex=NULL;
	}
	if(NULL!=Weight)
	{
		delete[]Weight;
		Weight=NULL;
	}
}
void CRevolution2::ReadNurbsControlPoint(CP2*ctrlP2,double*vW,int n,int q)
{
	RelaseMemory();
	m=8,p=2;
	this->n=n,this->q=q;
	       Vertex=new CP3[(m+1)*(n+1)];
	CalculateControlGrid(ctrlP2);
	double uW[9];
	double c=sqrt(2.0)/2;
	uW[0]=1.0;
	uW[1]=c;
	uW[2]=1.0;
	uW[3]=c;
	uW[4]=1.0;
	uW[5]=c;
	uW[6]=1.0;
	uW[7]=c;
	uW[8]=1.0;
	Weight=new double[(m+1)*(n+1)];
	for(int j=0;j<n+1;j++)
		for(int i=0;i<m+1;i++)
			Weight[(m+1)*j+i]=vW[j]*uW[i];
}
void CRevolution2::CalculateControlGrid(CP2*pt)
{
	for(int j=0;j<n+1;j++)
	{
		double r=fabs(pt[j].x);
		double a=0;
		int i;
		i=0;
		Vertex[(m+1)*j+i]=CP3(pt[j].x-20,pt[j].y+(i*5),0);
		i=1;
		Vertex[(m+1)*j+i]=CP3(pt[j].x-18,pt[j].y+(i*5),r);
		i=2;
		Vertex[(m+1)*j+i]=CP3(0-8,pt[j].y+(i*5),r);
		i=3;
		Vertex[(m+1)*j+i]=CP3(-pt[j].x-5,pt[j].y+(i*5),r);
		i=4;
		Vertex[(m+1)*j+i]=CP3(-pt[j].x-4,pt[j].y+(i*5),0);
		i=5;
		Vertex[(m+1)*j+i]=CP3(-pt[j].x-3,pt[j].y+(i*5),-r);
		i=6;
		Vertex[(m+1)*j+i]=CP3(0-2,pt[j].y+(i*5),-r);
		i=7;
		Vertex[(m+1)*j+i]=CP3(pt[j].x-1,pt[j].y+(i*5),-r);
		i=8;
		Vertex[(m+1)*j+i]=CP3(pt[j].x,pt[j].y+(i*5),0);
	}

}

void CRevolution2::DrawRevolution2(CDC *pDC)
{
	CP3**P=new CP3*[n+1];
	for(int j=0;j<n+1;j++)
		P[j]=new CP3[m+1];
	for(int j=0;j<n+1;j++)
		for(int i=0;i<m+1;i++)
			P[j][i]=Vertex[(m+1)*j+i];
	double**W=new double*[n+1];

	for(int j=0;j<n+1;j++)
		W[j]=new double[m+1];
	for(int j=0;j<n+1;j++)
		for(int i=0;i<m+1;i++)
			W[j][i]=Weight[(m+1)*j+i];



	NURBS.Initialize(P,W,m,p,n,q);
	NURBS.DrawNurbsSurface(pDC);	
	/*NURBS.DrawControlGrid(pDC);*/




	for(int j=0;j<n+1;j++)
	{
		delete[]P[j];
		P[j]=NULL;
	}
	delete[]P;
	P=NULL;
	for(int j=0;j<n+1;j++)
	{
		delete[]W[j];
		W[j]=NULL;
	}
	delete []W;
	W=NULL;
}
