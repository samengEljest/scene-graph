#pragma once
#include "Vector3.h"
using namespace std;
#include <math.h>

Vector3::Vector3(double X, double Y, double Z)
{
	vector[0] = X;
	vector[1] = Y;
	vector[2] = Z;
}
Vector3::Vector3()
{
	for (int i = 0; i < 3; i++)
	{		
		vector[i] = 0;
	}
}

Vector3 Vector3::operator+(Vector3 tmp)
{
	Vector3 sumAdd(0,0,0);
	for (int i = 0; i < 3; i++)
	{
		sumAdd.vector[i] = vector[i] + tmp.vector[i];
	}
	return sumAdd;
}

Vector3 Vector3::operator-(Vector3 tmp)
{
	Vector3 sumSub(0,0,0);
	for (int i = 0; i < 3; i++)
	{
		sumSub.vector[i] = vector[i] - tmp.vector[i];
	}
	return sumSub;
}

double& Vector3::operator[](int tmp)
{
	return vector[tmp];
}

double Vector3::dot(Vector3 tmp)
{
	double sumDot = 0;
	for(int i = 0; i < 3; i++)
	{
		sumDot += vector[i] * tmp.vector[i];
	}
	return sumDot;
}

Vector3 Vector3::cross(Vector3 tmp)
{
	Vector3 sumCross(0,0,0);
	sumCross.vector[0] = (vector[1] * tmp.vector[2]) - (vector[2] * tmp.vector[1]);
	sumCross.vector[1] = -((vector[0] * tmp.vector[2]) - (vector[2] * tmp.vector[0]));
	sumCross.vector[2] = (vector[0] * tmp.vector[1]) - (vector[1] * tmp.vector[0]);

	return sumCross;
}

double Vector3::length()
{
	double sumLength = 0;
	for (int i = 0; i < 3; i++)
	{
		sumLength += pow(vector[i], 2.0);
	}
	sumLength = sqrt(sumLength);
	return sumLength;
}

Vector3 Vector3::normal()
{
	Vector3 sumNormal(0,0,0);
	double length = this->length();
	for(int i = 0; i < 3; i++)
	{
		sumNormal.vector[i] = vector[i] / length;
	}

	return sumNormal;
}





void Vector3::fillV(double tmp)
{
	for (int i = 0; i < 3; i++)
	{		
		vector[i] = tmp;
	}
}

void Vector3::fillVRand()
{
	for (int i = 0; i < 3; i++)
	{
		vector[i] = rand() % 5;
	}
}

void Vector3::getVector()
{
	for (int i = 0; i < 3; i++) 
	{
		cout<<"  "<<vector[i];
	}
}