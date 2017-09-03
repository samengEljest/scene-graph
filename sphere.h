#pragma once
#include "Matrix4.h"
#include "Vector4.h"
#include <QtGui/QMainWindow>
#include <QGLWidget>
#include <QtOpenGL>
#include <qapplication.h> 
#include <qimage.h>
#include <qgl.h>
#include <QDebug>

class Sphere
{
public:
	Sphere();  ///< defoult constructor
	Sphere(int size);  ///< constructor
	double getVertex(int vec, int xyz); ///< returns value in vertex
	Vector4 getVector(int vec); ///< returns a vector
	double getNormalP(int vec, int xyz); ///< returns value normal
	float* rotateSph(float theta,string axis, float speed); ///< rotates the sphere
	void setRotate(float speed, string axis); ///< another function for rotate pyramid
	void randGenerator(); ///< ranom numbers for placement and rotation
	float getRotateX(); ///< returns RotateX
	float getRotateY(); ///< returns RotateY
	float getRotateZ(); ///< returns RotateZ
	int getPosX(); ///< returns PosX
	int getPosY(); ///< returns PosY
	int getPosZ(); ///< returns PosZ
	int getRSpeedX();  ///< returns SpeedX
	int getRSpeedY(); ///< returns SpeedY
	int getRSpeedZ(); ///< returns SpeedZ
	float getColor(); ///< returns color
	GLuint getTexHan(); ///< returns TexHan

private:
	Vector4 vertex[12];
	Vector4 normal[12];
	GLuint texHandle;
	float rotateX, rotateY, rotateZ, color;
	int posX,posY,posZ,rotateSpeedX,rotateSpeedY,rotateSpeedZ;

};