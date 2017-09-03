#pragma once
#include "cube.h"
#include "Vector4.h"
#include "Matrix4.h"

Cube::Cube()
{
}

Cube::Cube(double size)
{
	Vector4 V1(-size/2,-size/2,size/2,1);
	Vector4 V2(size/2,-size/2,size/2,1);
	Vector4 V3(-size/2,-size/2,-size/2,1);
	Vector4 V4(size/2,-size/2,-size/2,1);
	Vector4 V5(-size/2,size/2,size/2,1);
	Vector4 V6(size/2,size/2,size/2,1);
	Vector4 V7(-size/2,size/2,-size/2,1);
	Vector4 V8(size/2,size/2,-size/2,1);

	vertex[0] = V1;
	vertex[1] = V2;
	vertex[2] = V3;
	vertex[3] = V4;
	vertex[4] = V5;
	vertex[5] = V6;
	vertex[6] = V7;
	vertex[7] = V8;

	normal[0] = V1.normal();
	normal[1] = V2.normal();
	normal[2] = V3.normal();
	normal[3] = V4.normal();
	normal[4] = V5.normal();
	normal[5] = V6.normal();
	normal[6] = V7.normal();
	normal[7] = V8.normal();

	randGenerator();

	QString filename("texture2.png");
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

double Cube::getNormalP(int vec,int xyz)
{
	return normal[vec][xyz];
}

void Cube::randGenerator()
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

double Cube::getVertex(int vec, int xyz)
{
	return vertex[vec][xyz];
}

void Cube::setRotate(float speed, string axis)
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

float* Cube::rotateCube(float theta, string axis, float speed)
{
	Matrix4 M1(4,4);
	M1 = M1.rotateAxis(theta,axis);
	float* matrix16 = new float[16];
	matrix16 = M1.getMatrix16();
	setRotate(speed, axis);
	return matrix16;
}

void Cube::scalingCube(double scale)
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
	for (int i = 0; i < 8; i++)
	{
		vertex[i] =  M1*vertex[i];
	}
}

void Cube::transCube(double x, double y, double z)
{
	for (int i = 0; i < 8; i ++)
	{
		vertex[i][0] += x;
		vertex[i][1] += y;
		vertex[i][2] += z;
	}
}

int Cube::getPosX()
{
	return posX;
}
int Cube::getPosY()
{
	return posY;
}
int Cube::getPosZ()
{
	return posZ;
}
int Cube::getRSpeedX()
{
	return rotateSpeedX;
}
int Cube::getRSpeedY()
{
	return rotateSpeedY;
}
int Cube::getRSpeedZ()
{
	return rotateSpeedZ;
}
float Cube::getRotateX()
{
	return rotateX;
}
float Cube::getRotateY()
{
	return rotateY;
}
float Cube::getRotateZ()
{
	return rotateZ;
}
float Cube::getColor()
{
	return color;
}
GLint Cube::getTexHan()
{
	return texHandle;
}