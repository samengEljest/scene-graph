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
#include <string>

class Pyramid
{
public:
	Pyramid(); ///< defoult constructor
	Pyramid(double size);///< constructor
	double getVertex(int vec, int xyz); ///< returns value in vertex
	Vector4 getVector(int vec); ///< returns a vector
	double getNormalP(int vec, int xyz); ///< returns value normal
	float* rotatePyr(float theta,string axis, float speed); ///< rotates the Pyramid
	void scalingPyr(double scale); ///< scale the pyramid
	float* transPyr(double x, double y, double z); ///< move the pyramid
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
	Vector4 vertex[5];
	Vector4 normal[5];
	float rotateX, rotateY, rotateZ, color;
	GLuint texHandle;
	int posX,posY,posZ,rotateSpeedX,rotateSpeedY,rotateSpeedZ;
	
};