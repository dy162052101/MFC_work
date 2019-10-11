#pragma once
#include "P3.h"
#include "NurbsSurface.h"
class CRevolution
{
public:
	CRevolution(void);
	~CRevolution(void);
	void ReadNurbsControlPoint(CP2*ctrlP2,double*W2,int n,int q);//读入二维轮廓
	void CalculateControlGrid(CP2*pt);//计算回转体控制网格
	void CalculateWeight(double*wt);//计算曲面上的权因子
	void DrawRevolution(CDC*pDC);//绘制旋转体
	void RelaseMemory();//释放内存
public:
	int m,p;
	int n,q;
	CP3*Vertex;
	double*Weight;
	CNurbsSurface NURBS;
};

