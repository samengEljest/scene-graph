//! Vector3.h
#pragma once
#include <iostream>

/*!
	this is the class that handels calculations with vectors in 3D
*/
class Vector3
{
private:
	double vector[3];

public:
	Vector3();
	Vector3(double X, double Y, double Z); //constructor. X,Y,Z is values in those places

	Vector3 operator+(Vector3 tmp); ///< owerloading + operator to work with Vector+Vector
	Vector3 operator-(Vector3 tmp); ///< owerloading - operator to work with Vector-Vector
	double& operator[](int tmp); ///< owerloading the [] operator for easy access

	double dot(Vector3 tmp); ///< used for the dot product between two 3d vectors
	Vector3 cross(Vector3 tmp); ///< used for the cross product between two 3d vectors
	double length(); ///< calculates the lengh of a vector
	Vector3 normal(); ///< returns the normal of a vector

	void getVector(); ///< wriths the vector
	void fillV(double tmp); //fills an metrix with one kind off number on every position
	void fillVRand(); ///< fills the vector with random numbers between 1-5
};