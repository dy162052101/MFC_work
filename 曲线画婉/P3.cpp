#include "StdAfx.h"
#include "P3.h"
#include <math.h>

CP3::CP3(void)
{
	z=0.0;
}


CP3::~CP3(void)
{
}

CP3::CP3(double x,double y,double z):CP2(x,y)
{
	this->z=z;
}

CP3 operator +(const CP3 &p0, const CP3 &p1)//和
{	
	CP3 result;
	result.x = p0.x + p1.x;
	result.y = p0.y + p1.y;
	result.z = p0.z + p1.z;
	return result;
}

CP3 operator -(const CP3 &p0, const CP3 &p1)//差
{
	CP3 result;
	result.x = p0.x - p1.x;
	result.y = p0.y - p1.y;
	result.z = p0.z - p1.z;
	return result;
}

CP3 operator *(const CP3 &p, double scalar)//点和常量的积
{	
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}

CP3 operator *(double scalar, const CP3 &p)//点和常量的积
{	
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}

CP3 operator /(const CP3 &p, double scalar)//数除
{
	if(fabs(scalar)<1e-6)
		scalar = 1.0;
	CP3 result;
	result.x = p.x / scalar;
	result.y = p.y / scalar;
	result.z = p.z / scalar;
	return result;
}

CP3 operator+=(CP3 &p0,const CP3 &p1)
{
	p0.x=p0.x+p1.x;
	p0.y=p0.y+p1.y;
	p0.z=p0.z+p1.z;
	return p0;
}

CP3 operator-=(CP3 &p0,const CP3 &p1)
{
	p0.x=p0.x-p1.x;
	p0.y=p0.y-p1.y;
	p0.z=p0.z-p1.z;
	return p0;
}

CP3 operator*=(CP3 &p0,double scalar)
{
	p0.x=p0.x*scalar;
	p0.y=p0.y*scalar;
	p0.z=p0.z*scalar;
	return p0;
}

CP3 operator/=(CP3 &p0,double scalar)
{
	if(fabs(scalar)<1e-6)
		scalar=1.0;
	p0.x=p0.x/scalar;
	p0.y=p0.y/scalar;
	p0.z=p0.z/scalar;
	return p0;
}
