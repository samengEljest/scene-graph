//! Vector4.h
#pragma once
#include <iostream>
#include "Vector3.h"

/*!
	this is the class that handels calculations with vectors in 4D
*/
class Vector4
{
private:
	double vector[4];

public:
	Vector4();
	Vector4(double X, double Y, double Z, double W);

	Vector4 operator+(Vector4 tmp); ///< owerloading + operator to work with Vector+Vector
	Vector4 operator-(Vector4 tmp); ///< owerloading - operator to work with Vector-Vector
	Vector4 operator/(double tmp);
	double& operator[](int tmp); ///< owerloading the [] operator fot easy access

	double dot(Vector4 tmp); ///< used for the dot product between two 4d vectors
	double length(); ///< calcultes the length of a vector
	Vector4 normal(); ///< returns the normal of a vector

	Vector3 convert();
	void getVector(); ///< writhes out the vector
	void fillV(double tmp); //fills the vector with one kind off number on every position
	void fillVRand(); ///< fills the vector with random nubers between 1-´5
};