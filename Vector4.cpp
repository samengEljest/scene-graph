#pragma once
#include "Vector4.h"
using namespace std;
#include <math.h>

Vector4::Vector4(double X, double Y, double Z, double W)
{
	vector[0] = X;
	vector[1] = Y;
	vector[2] = Z;
	vector[3] = W;
}

Vector4::Vector4()
{
	for (int i = 0; i < 4; i++)
	{		
		vector[i] = 0;
	}
}

Vector4 Vector4::operator+(Vector4 tmp)
{
	Vector4 sumAdd(0,0,0,0);
	for (int i = 0; i < 4; i++)
	{
		sumAdd.vector[i] = vector[i] + tmp.vector[i];
	}
	return sumAdd;
}

Vector4 Vector4::operator/(double tmp)
{
	Vector4 sumDiv(0,0,0,0);
	for (int i = 0; i < 4; i++)
	{
		sumDiv[i] = vector[i]/tmp;
	}
	return sumDiv;
}

Vector4 Vector4::operator-(Vector4 tmp)
{
	Vector4 sumSub(0,0,0,0);
	for (int i = 0; i < 4; i++)
	{
		sumSub.vector[i] = vector[i] - tmp.vector[i];
	}
	return sumSub;
}

double& Vector4::operator[](int tmp)
{
	return vector[tmp];
}

double Vector4::dot(Vector4 tmp)
{
	double sumDot = 0;
	for(int i = 0; i < 4; i++)
	{
		sumDot += vector[i] * tmp.vector[i];
	}
	return sumDot;
}

Vector3 Vector4::convert()
{
	Vector3 V3(0,0,0);
	for (int i = 0; i < 3; i++)
	{
		V3[i] = vector[i];
	}
	return V3;

}

double Vector4::length()
{
	double sumLength = 0;
	for (int i = 0; i < 4; i++)
	{
		sumLength += pow(vector[i], 2.0);
	}
	sumLength = sqrt(sumLength);
	return sumLength;
}

Vector4 Vector4::normal()
{
	Vector4 sumNormal(0,0,0,0);
	double length = Vector4::length();
	for(int i = 0; i < 4; i++)
	{
		sumNormal.vector[i] = vector[i] / length;
	}
	return sumNormal;
}


void Vector4::fillV(double tmp)
{
	for (int i = 0; i < 4; i++)
	{		
		vector[i] = tmp;
	}
}

void Vector4::fillVRand()
{
	for (int i = 0; i < 4; i++)
	{
		vector[i] = rand() % 5;
	}
}

void Vector4::getVector()
{
	for (int i = 0; i < 4; i++) 
	{
		cout<<"  "<<vector[i];
	}
}