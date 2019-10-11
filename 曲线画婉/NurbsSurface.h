#pragma once
#include "P3.h"

class CNurbsSurface
{
public:
	CNurbsSurface(void);
	~CNurbsSurface(void);

	//轮廓线初始化
	void Initialize(CP3** CtrlP3, double** W3, int m, int p, int n, int q);
	void DrawNurbsSurface(CDC* pDC); //绘制曲面
	void DrawControlGrid(CDC* pDC); //绘制控制网格

private:
	void GetKnotVector(double* T, int nCount, int num, int order); //获取节点矢量
	double BasisFunctionValue(double t, int i, int order, double *T); //计算基函数
	CP2 OrthogonalProjection(CP3 pt3); //正交投影
	void ReleaseMemory();

private:
	int m, p; //m:U向的顶点数-1， p为次数
	int n, q; //n:V向的顶点数-1， q为次数
	CP3** P; //三维控制点二维数组表示
	double** W; // 三维控制点P的权因子
	double** U; //u向节点矢量数组
	double** V; //v向节点矢量数组
};
