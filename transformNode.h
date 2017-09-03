#pragma once
#include <QGLWidget>
#include <GL/glu.h>
#include "Matrix4.h"
#include "Vector4.h"
#include "node.h"

class TransformNode:
	public Node
{
private:
	float rotateX, rotateY, rotateY2, rotateZ;
	float rotateSpeedX,rotateSpeedY,rotateSpeedZ,rotateSpeedY2;
	bool tilt;
	bool ship;
	float posX,posY,posZ;
	Matrix4 matrixTrans;
	Matrix4 tmp;

public:
	TransformNode(float posX1, float posY1, float posZ1,float rotateOrbit, float rotateAxis);  ///< constructor
	void update(Matrix4 matrix, std::vector<Carrier> &carrier);  ///< calls rotate, sets positon and calls its children to update
	float getRotateX(); ///< returns RotateX
	float getRotateY(); ///< returns RotateY
	float getRotateZ(); ///< returns RotateZ
	int getPosX(); ///< returns PosX
	int getPosY(); ///< returns PosY
	int getPosZ(); ///< returns PosZ
	int getRSpeedX();  ///< returns SpeedX
	int getRSpeedY(); ///< returns SpeedY
	int getRSpeedZ(); ///< returns SpeedZ
	void setRotateZ(float z); ///< sets rotation on the z axis so the third planet can be tilted
	Matrix4 rotateObject(float theta,string axis, float speed,string what); ///< rotates the object
	void setRotate(float speed, string axis,string what); ///< another function for rotate object
};