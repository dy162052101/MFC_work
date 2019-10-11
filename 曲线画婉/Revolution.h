#pragma once
#include "P3.h"
#include "NurbsSurface.h"
class CRevolution
{
public:
	CRevolution(void);
	~CRevolution(void);
	void ReadNurbsControlPoint(CP2*ctrlP2,double*W2,int n,int q);//�����ά����
	void CalculateControlGrid(CP2*pt);//�����ת���������
	void CalculateWeight(double*wt);//���������ϵ�Ȩ����
	void DrawRevolution(CDC*pDC);//������ת��
	void RelaseMemory();//�ͷ��ڴ�
public:
	int m,p;
	int n,q;
	CP3*Vertex;
	double*Weight;
	CNurbsSurface NURBS;
};

