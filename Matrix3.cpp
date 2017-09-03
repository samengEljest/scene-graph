#pragma once
#include "Matrix3.h"
#include "Vector3.h"
#include <math.h>
using namespace std;

Matrix3::Matrix3(int x, int y)
{
	rows = y;
	columns = x;
}

Matrix3::Matrix3()
{
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix3 Matrix3::operator+(Matrix3 tmp)
{
	Matrix3 sumAdd(columns, rows);
	for (int i = 0; i < columns; i++) // for looparna to go throuh all columns and rows
	{
		for (int j = 0; j <rows; j++)
		{
			sumAdd.matrix[i][j] = matrix[i][j] + tmp.matrix[i][j];
		}
	}
	return sumAdd;
}

Matrix3 Matrix3::operator-(Matrix3 tmp)
{
	Matrix3 sumSub(columns, rows);
	for (int i = 0; i < columns; i++) 
	{
		for (int j = 0; j <rows; j++)
		{
			sumSub.matrix[i][j] = matrix[i][j] - tmp.matrix[i][j];
		}
	}
	return sumSub;
}

double* Matrix3::operator[](int tmp)
{
	return matrix[tmp];
}

Matrix3 Matrix3::operator~()
{
	Matrix3 trans(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			trans.matrix[i][j] = matrix[j][i]; //change places in the matrix.
		}
	}
	return trans;
}

Matrix3 Matrix3::operator*(Matrix3 tmp)
{
	if (rows != tmp.getCol()) //control, so we know that multiplication can be done
	{
		Matrix3 undef(1,1);
		return undef; //have to rturn, creates a 1x1 matrix becouse of this
	}
	Matrix3 sumMulti(columns,tmp.getRow()); //creates a matrix with column=row(first) and tmp.getRow()=column(secound)
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


Vector3 Matrix3::operator*(Vector3 tmp)
{
	Vector3 sumMulti(0,0,0); //
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sumMulti[i] += matrix[i][j] * tmp[i];//
		}
	}
	return sumMulti;
}

Matrix3 Matrix3::Invert()
{
	Matrix3 invers(rows, columns);
	double det, inv[4][4];
	det = matrix[0][0]*(matrix[1][1]*matrix[2][2]-matrix[2][1]*matrix[1][2])-
		  matrix[0][1]*(matrix[1][0]*matrix[2][2]-matrix[2][0]*matrix[1][2])+
		  matrix[0][2]*(matrix[1][0]*matrix[2][1]-matrix[2][0]*matrix[1][1]);

	for (int i = 0; i < rows; i++) //transpose
	{
		for(int j = 0; j < columns; j++)
		{
			invers.matrix[i][j] = matrix[j][i];
		}
	}

	inv[0][0] = +(invers.matrix[1][1]*invers.matrix[2][2]-invers.matrix[2][1]*invers.matrix[1][2]);
	inv[0][1] = -(invers.matrix[1][0]*invers.matrix[2][2]-invers.matrix[2][0]*invers.matrix[1][2]);
	inv[0][2] = +(invers.matrix[1][0]*invers.matrix[2][1]-invers.matrix[2][0]*invers.matrix[1][1]);
	inv[1][0] = -(invers.matrix[0][1]*invers.matrix[2][2]-invers.matrix[2][1]*invers.matrix[0][2]);
	inv[1][1] = +(invers.matrix[0][0]*invers.matrix[2][2]-invers.matrix[2][0]*invers.matrix[0][2]);
	inv[1][2] = -(invers.matrix[0][0]*invers.matrix[2][1]-invers.matrix[2][0]*invers.matrix[0][1]);
	inv[2][0] = +(invers.matrix[0][1]*invers.matrix[1][2]-invers.matrix[1][1]*invers.matrix[0][2]);
	inv[2][1] = -(invers.matrix[0][0]*invers.matrix[1][2]-invers.matrix[1][0]*invers.matrix[0][2]);
	inv[2][2] = +(invers.matrix[0][0]*invers.matrix[1][1]-invers.matrix[1][0]*invers.matrix[0][1]);

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
Matrix3 Matrix3::Convert()
{
	Matrix3 convert(4,4);
	if (rows == 3)
	{
		convert.FillM(0);
		for (int i = 0; i < columns; i++)
		{
			for(int j = 0; j < rows; j++)
			{
				convert.matrix[i][j] = matrix[i][j];
			}
		}
	}
	return convert;
}

Matrix3 Matrix3::rotateAxis(double theta, string axis)
{
	Matrix3 rotate(columns, rows);
	rotate.FillM(0);

	if (axis == "X" || axis == "x")
	{
		rotate.matrix[0][0] = 1;
		rotate.matrix[1][1] = cos(theta);
		rotate.matrix[1][2] = -sin(theta);
		rotate.matrix[2][1] = sin(theta);
		rotate.matrix[2][2] = cos(theta);
	}
	else if (axis == "X" || axis == "x")
	{
		rotate.matrix[0][0] = cos(theta);
		rotate.matrix[0][2] = sin(theta);
		rotate.matrix[1][1] = 1;
		rotate.matrix[2][0] = -sin(theta);
		rotate.matrix[2][2] = cos(theta);
	}
	else if (axis == "X" || axis == "x")
	{
		rotate.matrix[0][0] = cos(theta);
		rotate.matrix[0][1] = -sin(theta);
		rotate.matrix[1][0] = sin(theta);
		rotate.matrix[1][1] = cos(theta);
		rotate.matrix[2][2] = 1;
	}
	return rotate;
}

Matrix3 Matrix3::rotateVector(double theta, Vector3 tmp)
{
	Matrix3 rotate(columns,rows);
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
	
	return rotate;
}








void Matrix3::FillM(double tmp)
{
	for (int i = 0; i < columns; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			matrix[i][j] = tmp;
		}
	}
}

void Matrix3::FillMRand()
{
	for (int i = 0; i < columns; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			matrix[i][j] = rand() % 5;
		}
	}
}

void Matrix3::getmatrix()
{

	for (int i = 0; i < columns; i++) 
	{
		for (int j = 0; j <rows; j++)
		{
			cout << "  " << matrix[i][j];
		}
		cout<<endl;
	}
}


int Matrix3::getRow()
{
	return rows;
}

int Matrix3::getCol()
{
	return columns;
}