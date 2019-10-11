#pragma once
#include "P3.h"

class CNurbsSurface
{
public:
	CNurbsSurface(void);
	~CNurbsSurface(void);

	//�����߳�ʼ��
	void Initialize(CP3** CtrlP3, double** W3, int m, int p, int n, int q);
	void DrawNurbsSurface(CDC* pDC); //��������
	void DrawControlGrid(CDC* pDC); //���ƿ�������

private:
	void GetKnotVector(double* T, int nCount, int num, int order); //��ȡ�ڵ�ʸ��
	double BasisFunctionValue(double t, int i, int order, double *T); //���������
	CP2 OrthogonalProjection(CP3 pt3); //����ͶӰ
	void ReleaseMemory();

private:
	int m, p; //m:U��Ķ�����-1�� pΪ����
	int n, q; //n:V��Ķ�����-1�� qΪ����
	CP3** P; //��ά���Ƶ��ά�����ʾ
	double** W; // ��ά���Ƶ�P��Ȩ����
	double** U; //u��ڵ�ʸ������
	double** V; //v��ڵ�ʸ������
};
