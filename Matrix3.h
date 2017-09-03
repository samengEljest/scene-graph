//! Matrix3.h
#pragma once
#include <string>
#include <iostream>
#include "Vector3.h"
using namespace std;

/*!
	this is the class that handels calculations with matrixes in 3D
*/
class Matrix3
{

private:
	double matrix[4][4];
	int rows, columns;
	int getRow();
	int getCol();

public:
	Matrix3();
	Matrix3(int x, int y); ///< the constructor

	Matrix3 operator+(Matrix3 tmp); ///< owerloading + operator to work with matrix+matrix
	Matrix3 operator-(Matrix3 tmp); ///< owerloading - operator to work with matrix-matrix
	Matrix3 operator*(Matrix3 tmp); ///< owerloading * operator to work with matrix*matrix
	Vector3 operator*(Vector3 tmp); ///< owerloading * operator to work with matrix*vector
	Matrix3 operator~(); ///< owerloading ~ operator to transpos matrix
	double* operator[](int tmp);///< owerloading [] operator for easy access

	Matrix3 rotateVector(double theta, Vector3 tmp); ///< rotate matrix around a vector
	Matrix3 rotateAxis(double theta, string axis); ///< rotat matrix around an axis
	Matrix3 Convert(); ///< converts a 3x3 to 4x4 matrix
	Matrix3 Invert(); ///< the inverse of an matrix
	void FillM(double tmp); ///< fills an metrix with one kind off number on every position
	void FillMRand(); ///< fills the matrix with random numbers between 1-5

	void getmatrix(); ///< wriths the matrix
};