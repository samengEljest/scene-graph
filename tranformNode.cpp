#include "transformNode.h"


TransformNode::TransformNode(float posX1, float posY1, float posZ1, float rotateOrbit, float rotateAxis)
{
	rotateX = 0; rotateY = 0; rotateY2 = 0; rotateZ = 0;
	posX = posX1;
	posY = posY1;
	posZ = posZ1;
	rotateSpeedX = 0;
	rotateSpeedY = rotateOrbit;
	rotateSpeedY2 = rotateAxis;
	rotateSpeedZ = 0;
	tilt = false;
	ship = false;
	matrixTrans = Matrix4(4,4);
	tmp = Matrix4(4,4);
	tmp[0][3] = posX1;
	tmp[1][3] = posY1;
	tmp[2][3] = posZ1;


}

void TransformNode::update(Matrix4 matrix, std::vector<Carrier> &carrier)
{
	
	Matrix4 tmp2(4,4);
	tmp2 = (rotateObject(rotateY, "y", rotateSpeedY, "orb") * tmp) * rotateObject(rotateY2, "y", rotateSpeedY2, "self");
	if (tilt)
		tmp2 = tmp2*rotateObject(rotateZ, "z", 0, "nada");
	matrixTrans = matrix*tmp2;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->update(matrixTrans, carrier);
	}
	//glPopMatrix();
}

Matrix4 TransformNode::rotateObject(float theta, string axis, float speed, string what)
{
	Matrix4 M(4,4);
	M = M.rotateAxis(theta,axis);
	if (axis == "X" || axis == "x")
	{
		rotateX += speed;
	}
	else if (axis == "Y" || axis == "y" && what == "orb")
	{
		rotateY += speed;
	}
	else if (axis == "Y" || axis == "y" && what == "self")
	{
		rotateY2 += speed;
	}
	else if (axis == "Z" || axis == "z")
	{
		rotateZ += speed;
	}
	return M;
}


int TransformNode::getPosX()
{
	return posX;
}
int TransformNode::getPosY()
{
	return posY;
}
int TransformNode::getPosZ()
{
	return posZ;
}

int TransformNode::getRSpeedX()
{
	return rotateSpeedX;
}
int TransformNode::getRSpeedY()
{
	return rotateSpeedY;
}
int TransformNode::getRSpeedZ()
{
	return rotateSpeedZ;
}
float TransformNode::getRotateX()
{
	return rotateX;
}
float TransformNode::getRotateY()
{
	return rotateY;
}
float TransformNode::getRotateZ()
{
	return rotateZ;
}

void TransformNode::setRotateZ(float z)
{
	rotateZ = z;
	tilt = true;
}