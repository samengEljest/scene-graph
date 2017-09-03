#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <string>
#include <QGLWidget>
#include <QGLFunctions>
#include "node.h"

class ObjectLoader:
	public Node
{

public :
	ObjectLoader(); ///< defoult constructor
	ObjectLoader(float scale1);  ///< constructor

	bool loadOBJ(
        const char * path, 
        std::vector<float*>& out_vertices, 
        std::vector<float*>& out_uvs,
        std::vector<float*>& out_normals,
		QGLFunctions funcs);  ///< gets vectors, texture position and normals from .obj file
	std::vector< float* > vertices;
	std::vector< float* > uvs;
	std::vector< float* > normals;
	GLint getTexHan();  ///< teturns TecHan
	void loadTexture(QString newtexture);  ///< loads the texture for the object
	void update(Matrix4 matrix, std::vector<Carrier> &carrier);  ///< calls drawObject
	void scaleObj(float scale);  ///< scales the object
	void setSun(); ///< sets a bool sun to true to know if the object is a sun

private:
	GLuint texHandle;
	float scale;
	float* drawmMat16;
	GLint texHandelID;
	GLuint vertexID;
	GLuint normalID;
	GLuint uvID;
	bool sun;

};

