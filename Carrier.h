#pragma once
#include <QGLWidget>
#include "Matrix4.h"
class Carrier
{

public:
	Carrier();
	Carrier(const Carrier &temp);

	GLuint vertexID;
	GLuint normalID;
	GLuint uvID;
	
	GLint textureLocation;
	GLuint texture;

	float boundingRightX;
	float boundingLeftX;
	float boundingTopY;
	float boundingBottomY;

	int verSize;
	int uvSize;
	int normSize;

	float scale;

	bool sun;

	Matrix4 trans;

private:

};