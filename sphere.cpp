#include "sphere.h"
#include <math.h>

Sphere::Sphere()
{
}

Sphere::Sphere(int size)
{
	float t = (size/2 + sqrt(5.0) / 2.0);
	Vector4 V1(-size/2,  t, 0, 1);
	Vector4 V2( size/2,  t, 0, 1);
	Vector4 V3(-size/2, -t, 0, 1);
	Vector4 V4( size/2, -t, 0, 1);

	Vector4 V5(0, -size/2,  t, 1);
	Vector4 V6(0,  size/2,  t, 1);
	Vector4 V7(0, -size/2, -t, 1);
	Vector4 V8(0,  size/2, -t, 1);

	Vector4 V9( t, 0, -size/2, 1);
	Vector4 V10( t, 0,  size/2, 1);
	Vector4 V11(-t, 0, -size/2, 1);
	Vector4 V12(-t, 0,  size/2, 1);

	vertex[0] = V1;
	vertex[1] = V2;
	vertex[2] = V3;
	vertex[3] = V4;
	vertex[4] = V5;
	vertex[5] = V6;
	vertex[6] = V7;
	vertex[7] = V8;
	vertex[8] = V9;
	vertex[9] = V10;
	vertex[10] = V11;
	vertex[11] = V12;

	normal[0] = V1.normal();
	normal[1] = V2.normal();
	normal[2] = V3.normal();
	normal[3] = V4.normal();
	normal[4] = V5.normal();
	normal[5] = V6.normal();
	normal[6] = V7.normal();
	normal[7] = V8.normal();
	normal[8] = V9.normal();
	normal[9] = V10.normal();
	normal[10] = V11.normal();
	normal[11] = V12.normal();
	randGenerator();

	QString filename("texture4.png");
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

void Sphere::randGenerator()
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

double Sphere::getVertex(int vec, int xyz)
{
	return vertex[vec][xyz];
}
Vector4 Sphere::getVector(int vec)
{
	return vertex[vec];
}

double Sphere::getNormalP(int vec,int xyz)
{
	return normal[vec][xyz];
}

void Sphere::setRotate(float speed, string axis)
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

float* Sphere::rotateSph(float theta, string axis, float speed)
{
	Matrix4 M1(4,4);
	M1 = M1.rotateAxis(theta,axis);
	float* matrix16 = new float[16];
	matrix16 = M1.getMatrix16();
	setRotate(speed, axis);
	return matrix16;
}


int Sphere::getPosX()
{
	return posX;
}
int Sphere::getPosY()
{
	return posY;
}
int Sphere::getPosZ()
{
	return posZ;
}
int Sphere::getRSpeedX()
{
	return rotateSpeedX;
}
int Sphere::getRSpeedY()
{
	return rotateSpeedY;
}
int Sphere::getRSpeedZ()
{
	return rotateSpeedZ;
}
float Sphere::getRotateX()
{
	return rotateX;
}
float Sphere::getRotateY()
{
	return rotateY;
}
float Sphere::getRotateZ()
{
	return rotateZ;
}
float Sphere::getColor()
{
	return color;
}
GLuint Sphere::getTexHan()
{
	return texHandle;
}