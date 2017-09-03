#pragma once
#include "pyramid.h"
#include "Vector4.h"
#include "Matrix4.h"

Pyramid::Pyramid()
{
}

Pyramid::Pyramid(double size)
{
	Vector4 V1(0,size/2,0,1);
	Vector4 V2(-size/2,-size/2,-size/2,1);
	Vector4 V3(size/2,-size/2,-size/2,1);
	Vector4 V4(-size/2,-size/2,size/2,1);
	Vector4 V5(size/2,-size/2,size/2,1);

	vertex[0] = V1;
	vertex[1] = V2;
	vertex[2] = V3;
	vertex[3] = V4;
	vertex[4] = V5;

	normal[0] = V1.normal();
	normal[1] = V2.normal();
	normal[2] = V3.normal();
	normal[3] = V4.normal();
	normal[4] = V5.normal();

	randGenerator();

	QString filename("texture3.png");
	QImage tex = QImage(filename,"PNG");

	QImage texture = QGLWidget::convertToGLFormat(tex);

	int tw = texture.width();
	int th = texture.height();

	//This texture will be number 1 
	glGenTextures(1,&texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);

	//Wrap tetxure coordinates for repeating. ex: (1.1,1.2) == (0.1,0.2)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//CLAMP/REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Texture minification, texture magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//How the texture will react with the environment. (Lighting etc)
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//MODULATE/REPLACE

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0 ,GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) texture.bits());
}

void Pyramid::randGenerator()
{
	rotateX = 0; rotateY = 0; rotateZ = 0;
	posX = rand() % 200;
	posX -= 100;
	posY = rand() % 200;
	posY -= 100;
	posZ = rand() % 200;
	posZ -= 100;
	rotateSpeedX = rand() % 4;
	rotateSpeedY = rand() % 4;
	rotateSpeedZ = rand() % 4;
	color = rand() % 10;
	color /= 10;
}

double Pyramid::getVertex(int vec, int xyz)
{
	return vertex[vec][xyz];
}
Vector4 Pyramid::getVector(int vec)
{
	return vertex[vec];
}
double Pyramid::getNormalP(int vec,int xyz)
{
	return normal[vec][xyz];
}

void Pyramid::setRotate(float speed, string axis)
{
	if (axis == "X" || axis == "x")
	{
		rotateX += speed;
	}
	else if (axis == "Y" || axis == "y")
	{
		rotateY += speed;
	}
	else if (axis == "Z" || axis == "z")
	{
		rotateZ += speed;
	}

}

float* Pyramid::rotatePyr(float theta, string axis, float speed)
{
	Matrix4 M1(4,4);
	M1 = M1.rotateAxis(theta,axis);
	float* matrix16 = new float[16];
	matrix16 = M1.getMatrix16();
	setRotate(speed, axis);
	return matrix16;
}

void Pyramid::scalingPyr(double scale)
{
	Matrix4 M1(4,4);
	M1.FillM(0);
	M1[3][3] = 1;
	int j = 0;
	for (int i = 0; i < 3; i++)
	{
		M1[i][j] = scale;
		j++;
	}
	vertex[0] =  M1*vertex[0];
	vertex[1] =  M1*vertex[1];
	vertex[2] =  M1*vertex[2];
	vertex[3] =  M1*vertex[3];
	vertex[4] =  M1*vertex[4];

}

float* Pyramid::transPyr(double x, double y, double z)
{
	Matrix4 M(4,4);
	M[3][0] = x;
	M[3][1] = y;
	M[3][2] = z;
	float* matrix16 = new float[16];
	matrix16 = M.getMatrix16();
	return matrix16;
}

int Pyramid::getPosX()
{
	return posX;
}
int Pyramid::getPosY()
{
	return posY;
}
int Pyramid::getPosZ()
{
	return posZ;
}
int Pyramid::getRSpeedX()
{
	return rotateSpeedX;
}
int Pyramid::getRSpeedY()
{
	return rotateSpeedY;
}
int Pyramid::getRSpeedZ()
{
	return rotateSpeedZ;
}
float Pyramid::getRotateX()
{
	return rotateX;
}
float Pyramid::getRotateY()
{
	return rotateY;
}
float Pyramid::getRotateZ()
{
	return rotateZ;
}
float Pyramid::getColor()
{
	return color;
}
GLuint Pyramid::getTexHan()
{
	return texHandle;
}