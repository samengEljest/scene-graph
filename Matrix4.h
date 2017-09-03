//! Matrix4.h
#pragma once
#include <iostream>
#include "Vector4.h"
#include <string>
using namespace std;

/*!
	this is the class that handels calculations with matrixes in 4D
*/
class Matrix4
{

private:
	double matrix[4][4];
	float matrix16[16];
	int rows, columns;
	int getRow(); ///< returns rows
	int getCol(); ///< returns columns

public:
	Matrix4(int x, int y);
	Matrix4();

	Matrix4 operator+(Matrix4 tmp); ///< owerloading + operator to work with matrix+matrix
	Matrix4 operator-(Matrix4 tmp); ///< owerloading - operator to work with matrix-matrix
	Matrix4 operator*(Matrix4 tmp); ///< owerloading * operator to work with matrix*matrix
	Vector4 operator*(Vector4 tmp); ///< owerloading * operator to work with matrix*vector
	Matrix4 operator~(); ///< owerloading ~ operator to transpos matrix
	double* operator[](int tmp); ///< owerloading [] operator for easy access

	Matrix4 rotateAxis(double theta, string axis);
	Matrix4 rotateVector(double theta, Vector4 tmp); ///<rotats the matrix around a vector
	Matrix4 persProj(double fovy, double aspect, double zNear, double zFar);//perspective projection
	Matrix4 orthProj();///< orthogonal projection matrix
	float* getMatrix16();

	Matrix4 Invert();///< the inverse of a 4d matrix
	void FillM(double tmp); ///<fills an metrix with one kind off number on every position
	void FillMRand(); ///< fills the matrix with random nummbers between 1-5

	void getmatrix(); ///<writhts out the matrix
};