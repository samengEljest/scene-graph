#pragma once
#include "Matrix4.h"
#include <math.h>
using namespace std;

Matrix4::Matrix4(int x, int y)
{
	rows = y;
	columns = x;
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for(int j = 0; j < 4; j++)
	{
		matrix[j][k] = 1;
		k++;
	}

}

Matrix4::Matrix4()
{
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix4 Matrix4::operator+(Matrix4 tmp)
{
	Matrix4 sumAdd(columns, rows);
	for (int i = 0; i < columns; i++) // for looparna to go throuh all columns and rows
	{
		for (int j = 0; j <rows; j++)
		{
			sumAdd.matrix[i][j] = matrix[i][j] + tmp.matrix[i][j];
		}
	}
	return sumAdd;
}

Matrix4 Matrix4::operator-(Matrix4 tmp)
{
	Matrix4 sumSub(columns, rows);
	for (int i = 0; i < columns; i++) 
	{
		for (int j = 0; j <rows; j++)
		{
			sumSub.matrix[i][j] = matrix[i][j] - tmp.matrix[i][j];
		}
	}
	return sumSub;
}

Matrix4 Matrix4::operator~()
{
	Matrix4 trans(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			trans.matrix[i][j] = matrix[j][i]; //change places in the matrix.
		}
	}
	return trans;
}

double* Matrix4::operator[](int tmp)
{
	return matrix[tmp];
}

Matrix4 Matrix4::operator*(Matrix4 tmp)
{
	if (rows != tmp.getCol()) //control, so we know that multiplication can be done
	{
		Matrix4 undef(1,1);
		return undef; //have to rturn, creates a 1x1 matrix becouse of this
	}
	Matrix4 sumMulti(columns,tmp.getRow()); //creates a matrix with column=row(first) and tmp.getRow()=column(secound)
	sumMulti.FillM(0); //fills the matrix with 0, otherwise its filld with -9... witch destroys the calculation
	for (int i = 0; i < sumMulti.getCol(); i++)
	{
		for (int j = 0; j < sumMulti.getRow(); j++)
		{
			for(int k = 0; k < rows; k++) 
			{
				sumMulti.matrix[i][j] += matrix[i][k] * tmp.matrix[k][j];//every number in the first matrix row multiplies with the secound matrix numbers in the columns, then gets put together.
			}
		}
	}
	return sumMulti;
}

Vector4 Matrix4::operator*(Vector4 tmp)
{
	Vector4 sumMulti(0,0,0,0); //
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sumMulti[i] += matrix[i][j] * tmp[i];//
		}
	}
	return sumMulti;
}

Matrix4 Matrix4::rotateAxis(double theta, string axis)
{
	Matrix4 rotate(4,4);
	rotate.FillM(0);
	double pi = 3.1415926535897932384626433832795;

	if (axis == "X" || axis == "x")
	{
		rotate[0][0] = 1;
		rotate[1][1] = cos(theta*pi/180);
		rotate[1][2] = -sin(theta*pi/180);
		rotate[2][1] = sin(theta*pi/180);
		rotate[2][2] = cos(theta*pi/180);
		rotate[3][3] = 1;
	}
	else if (axis == "Y" || axis == "y")
	{
		rotate[0][0] = cos(theta*pi/180);
		rotate[0][2] = sin(theta*pi/180);
		rotate[1][1] = 1;
		rotate[2][0] = -sin(theta*pi/180);
		rotate[2][2] = cos(theta*pi/180);
		rotate[3][3] = 1;
	}
	else if(axis == "Z" || axis == "z")
	{
		rotate[0][0] = cos(theta*pi/180);
		rotate[0][1] = -sin(theta*pi/180);
		rotate[1][0] = sin(theta*pi/180);
		rotate[1][1] = cos(theta*pi/180);
		rotate[2][2] = 1;
		rotate[3][3] = 1;
	}
	return rotate;
}

Matrix4 Matrix4::rotateVector(double theta, Vector4 tmp)
{
	Matrix4 rotate(columns, rows);
	rotate.FillM(0);
	double c = cos(theta);
	double s = sin(theta);
	double t = 1-cos(theta);
	double X = tmp[0];
	double Y = tmp[1];
	double Z = tmp[2];

	rotate.matrix[0][0] = t*pow(X, 2) + c;
	rotate.matrix[0][1] = t*X*Y + s*Z;
	rotate.matrix[0][2] = t*X*Z - s*Y;
	rotate.matrix[1][0] = t*X*Y - s*Z;
	rotate.matrix[1][1] = t*pow(Y, 2) + c;
	rotate.matrix[1][2] = t*Y*Z + s*X;
	rotate.matrix[2][0] = t*X*Z + s*Y;
	rotate.matrix[2][1] = t*Y*Z - s*X;
	rotate.matrix[2][2] = t*pow(Z, 2) + c;
	rotate.matrix[3][3] = 1;

	return rotate;

}

Matrix4 Matrix4::Invert()
{
	Matrix4 invers(rows, columns);
	double det, inv[4][4];
	inv[0][0] = matrix[1][1] * matrix[2][2] * matrix[3][3] - 
			  matrix[1][1] * matrix[2][3] * matrix[3][2] - 
			  matrix[2][1] * matrix[1][2] * matrix[3][3] + 
			  matrix[2][1] * matrix[1][3] * matrix[3][2] +
			  matrix[3][1] * matrix[1][2] * matrix[2][3] - 
			  matrix[3][1] * matrix[1][3] * matrix[2][2];

	inv[1][0] = -matrix[1][0] * matrix[2][2] * matrix[3][3] + 
			  matrix[1][0] * matrix[2][3] * matrix[3][2] + 
			  matrix[2][0] * matrix[1][2] * matrix[3][3] - 
			  matrix[2][0] * matrix[1][3] * matrix[3][2] - 
			  matrix[3][0] * matrix[1][2] * matrix[2][3] + 
			  matrix[3][0] * matrix[1][3] * matrix[2][2];

	inv[2][0] = matrix[1][0] * matrix[2][1] * matrix[3][3] - 
			  matrix[1][0] * matrix[2][3] * matrix[3][1] - 
			  matrix[2][0] * matrix[1][1] * matrix[3][3] + 
			  matrix[2][0] * matrix[1][3] * matrix[3][1] + 
			  matrix[3][0] * matrix[1][1] * matrix[2][3] - 
			  matrix[3][0] * matrix[1][3] * matrix[2][1];

	inv[3][0] = -matrix[1][0] * matrix[2][1] * matrix[3][2] + 
			  matrix[1][0] * matrix[2][2] * matrix[3][1] +
			  matrix[2][0] * matrix[1][1] * matrix[3][2] - 
			  matrix[2][0] * matrix[1][2] * matrix[3][1] - 
			  matrix[3][0] * matrix[1][1] * matrix[2][2] + 
			  matrix[3][0] * matrix[1][2] * matrix[2][1];

	inv[0][1] = -matrix[0][1] * matrix[2][2] * matrix[3][3] + 
			  matrix[0][1] * matrix[2][3] * matrix[3][2] + 
			  matrix[2][1] * matrix[0][2] * matrix[3][3] - 
			  matrix[2][1] * matrix[0][3] * matrix[3][2] - 
			  matrix[3][1] * matrix[0][2] * matrix[2][3] + 
			  matrix[3][1] * matrix[0][3] * matrix[2][2];

	inv[1][1] = matrix[0][0] * matrix[2][2] * matrix[3][3] - 
			  matrix[0][0] * matrix[2][3] * matrix[3][2] - 
			  matrix[2][0] * matrix[0][2] * matrix[3][3] + 
			  matrix[2][0] * matrix[0][3] * matrix[3][2] + 
			  matrix[3][0] * matrix[0][2] * matrix[2][3] - 
			  matrix[3][0] * matrix[0][3] * matrix[2][2];

	inv[2][1] = -matrix[0][0] * matrix[2][1] * matrix[3][3] + 
			  matrix[0][0] * matrix[2][3] * matrix[3][1] + 
			  matrix[2][0] * matrix[0][1] * matrix[3][3] - 
			  matrix[2][0] * matrix[0][3] * matrix[3][1] - 
			  matrix[3][0] * matrix[0][1] * matrix[2][3] + 
			  matrix[3][0] * matrix[0][3] * matrix[2][1];

	inv[3][1] = matrix[0][0] * matrix[2][1] * matrix[3][2] - 
			  matrix[0][0] * matrix[2][2] * matrix[3][1] - 
			  matrix[2][0] * matrix[0][1] * matrix[3][2] + 
			  matrix[2][0] * matrix[0][2] * matrix[3][1] + 
			  matrix[3][0] * matrix[0][1] * matrix[2][2] - 
			  matrix[3][0] * matrix[0][2] * matrix[2][1];

	inv[0][2] = matrix[0][1] * matrix[1][2] * matrix[3][3] - 
			  matrix[0][1] * matrix[1][3] * matrix[3][2] - 
			  matrix[1][1] * matrix[0][2] * matrix[3][3] + 
			  matrix[1][1] * matrix[0][3] * matrix[3][2] + 
			  matrix[3][1] * matrix[0][2] * matrix[1][3] - 
			  matrix[3][1] * matrix[0][3] * matrix[1][2];

	inv[1][2] = -matrix[0][0] * matrix[1][2] * matrix[3][3] + 
			  matrix[0][0] * matrix[1][3] * matrix[3][2] + 
			  matrix[1][0] * matrix[0][2] * matrix[3][3] - 
			  matrix[1][0] * matrix[0][3] * matrix[3][2] - 
			  matrix[3][0] * matrix[0][2] * matrix[1][3] + 
			  matrix[3][0] * matrix[0][3] * matrix[1][2];

	inv[2][2] = matrix[0][0] * matrix[1][1] * matrix[3][3] - 
			  matrix[0][0] * matrix[1][3] * matrix[3][1] - 
			  matrix[1][0] * matrix[0][1] * matrix[3][3] + 
			  matrix[1][0] * matrix[0][3] * matrix[3][1] + 
			  matrix[3][0] * matrix[0][1] * matrix[1][3] - 
			  matrix[3][0] * matrix[0][3] * matrix[1][1];

	inv[3][2] = -matrix[0][0] * matrix[1][1] * matrix[3][2] + 
			  matrix[0][0] * matrix[1][2] * matrix[3][1] + 
			  matrix[1][0] * matrix[0][1] * matrix[3][2] - 
			  matrix[1][0] * matrix[0][2] * matrix[3][1] - 
			  matrix[3][0] * matrix[0][1] * matrix[1][2] + 
			  matrix[3][0] * matrix[0][2] * matrix[1][1];

	inv[0][3] = -matrix[0][1] * matrix[1][2] * matrix[2][3] + 
			  matrix[0][1] * matrix[1][3] * matrix[2][2] + 
			  matrix[1][1] * matrix[0][2] * matrix[2][3] - 
			  matrix[1][1] * matrix[0][3] * matrix[2][2] - 
			  matrix[2][1] * matrix[0][2] * matrix[1][3] + 
			  matrix[2][1] * matrix[0][3] * matrix[1][2];

	inv[1][3] = matrix[0][0] * matrix[1][2] * matrix[2][3] - 
			  matrix[0][0] * matrix[1][3] * matrix[2][2] - 
			  matrix[1][0] * matrix[0][2] * matrix[2][3] + 
			  matrix[1][0] * matrix[0][3] * matrix[2][2] + 
			  matrix[2][0] * matrix[0][2] * matrix[1][3] - 
			  matrix[2][0] * matrix[0][3] * matrix[1][2];

	inv[2][3] = -matrix[0][0] * matrix[1][1] * matrix[2][3] + 
			  matrix[0][0] * matrix[1][3] * matrix[2][1] + 
			  matrix[1][0] * matrix[0][1] * matrix[2][3] - 
			  matrix[1][0] * matrix[0][3] * matrix[2][1] - 
			  matrix[2][0] * matrix[0][1] * matrix[1][3] + 
			  matrix[2][0] * matrix[0][3] * matrix[1][1];

	inv[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] - 
			  matrix[0][0] * matrix[1][2] * matrix[2][1] - 
			  matrix[1][0] * matrix[0][1] * matrix[2][2] + 
			  matrix[1][0] * matrix[0][2] * matrix[2][1] + 
			  matrix[2][0] * matrix[0][1] * matrix[1][2] - 
			  matrix[2][0] * matrix[0][2] * matrix[1][1];

	det = matrix[0][0] * inv[0][0] + matrix[0][1] * inv[1][0] + matrix[0][2] * inv[2][0] + matrix[0][3] * inv[3][0];
	try
	{
		det = 1.0 / det;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				invers.matrix[i][j] = inv[i][j] * det;
			}
		}
	}
	catch(const exception &ex)
	{
		cerr << ex.what() << "\nFatal error" << endl;
		throw;
	}
	return invers;
}


Matrix4 Matrix4::persProj(double fovy, double aspect, double zNear, double zFar)
{
	Matrix4 proj(4,4);
	float pi = 3.14159265359;
	float f = 1/(tan((fovy/2)*(pi/180)));
	proj.matrix[0][0] = f / aspect;
	proj.matrix[1][1] = f;
	proj.matrix[2][2] = (zFar+zNear)/(zNear-zFar);
	proj.matrix[3][2] = 2*(zFar*zNear)/(zNear-zFar);
	proj.matrix[2][3] = -1;
	//proj = ~proj; //maby transpose
	return proj;
}

Matrix4 Matrix4::orthProj()
{
	Matrix4 proj(rows, columns);
	proj.FillM(0);
	proj.matrix[0][0] = 1;
	proj.matrix[1][1] = 1;
	proj.matrix[3][3] = 1;

	return proj;
}

float* Matrix4::getMatrix16()
{
	float* matrix16 = new float[16];
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix16[k] = matrix[i][j];
			k++;
		}
	}
	return matrix16;
}

void Matrix4::FillM(double tmp)
{
	for (int i = 0; i < columns; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			matrix[i][j] = tmp;
		}
	}
}

void Matrix4::FillMRand()
{
	for (int i = 0; i < columns; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			matrix[i][j] = rand() % 5;
		}
	}
}

void Matrix4::getmatrix()
{

	for (int i = 0; i < columns; i++) 
	{
		for (int j = 0; j <rows; j++)
		{
			cout<<"  "<<matrix[i][j];
		}
		cout<<endl;
	}
}

int Matrix4::getRow()
{
	return rows;
}

int Matrix4::getCol()
{
	return columns;
}