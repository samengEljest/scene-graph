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

class Cube
{
public:
	Cube(); ///< defoult constructor
	Cube(double size); ///< constructor
	double getVertex(int vec, int xyz); ///< returns value in vertex
	double getNormalP(int vec, int xyz); ///< returns value normal
	float* rotateCube(float theta,string axis, float speed); ///< rotates the cube
	void scalingCube(double scale); ///< scale the cube
	void transCube(double x, double y, double z); ///< move cube
	void setRotate(float speed, string axis); ///< another function for rotate cube
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
	GLint getTexHan(); ///< returns TexHan
	

private:
	Vector4 vertex[8];
	Vector4 normal[8];
	float rotateX, rotateY, rotateZ, color;
	GLuint texHandle;
	int posX,posY,posZ,rotateSpeedX,rotateSpeedY,rotateSpeedZ;
	
};