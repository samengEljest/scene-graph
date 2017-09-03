#include "objectLoader.h"


ObjectLoader::ObjectLoader()
{}
ObjectLoader::ObjectLoader(float scale1)
{
	scale = scale1;
	sun = false;
	drawmMat16 = new float[16];
}

void ObjectLoader::loadTexture(QString newtexture)
{
	QString filename(newtexture);
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

	//How the texture will react with the environment.
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0 ,GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) texture.bits());
}

bool ObjectLoader::loadOBJ(
        const char * path, 
        std::vector<float*> & out_vertices, 
        std::vector<float*> & out_uvs,
        std::vector<float*> & out_normals,
		QGLFunctions funcs)
{
        printf("Loading OBJ file %s...\n", path);

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<float*> temp_vertices; 
        std::vector<float*> temp_uvs;
        std::vector<float*> temp_normals;


        FILE * file = fopen(path, "r");
        if( file == NULL ){
                printf("Impossible to open the file \n");
                return false;
        }

        while( 1 ){

                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                        break; // EOF = End Of File. Quit the loop.

                // else : parse lineHeader
                
                if ( strcmp( lineHeader, "v" ) == 0 )
				{
						float* vertex = new float[3];
                        fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2] );
                        temp_vertices.push_back(vertex);
                }
				else if ( strcmp( lineHeader, "vt" ) == 0 )
				{
                        float* uv = new float[3];
                        fscanf(file, "%f %f\n", &uv[0], &uv[1] );
                       // uv[1] = -uv[1]; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                        temp_uvs.push_back(uv);
                }
				else if ( strcmp( lineHeader, "vn" ) == 0 )
				{
                        float* normal = new float[3];
                        fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2] );
                        temp_normals.push_back(normal);
                }
				else if ( strcmp( lineHeader, "f" ) == 0 )
				{
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                        if (matches != 9)
						{
                                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                                return false;
                        }
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                        uvIndices    .push_back(uvIndex[0]);
                        uvIndices    .push_back(uvIndex[1]);
                        uvIndices    .push_back(uvIndex[2]);
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                }
				else
				{
                        // Probably a comment, skip the line
                        char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
                }

        }

        // For each vertex of each triangle
        for( unsigned int i=0; i<vertexIndices.size(); i++ )
		{
                // Get the indices of its attributes
                unsigned int vertexIndex = vertexIndices[i];
                unsigned int uvIndex = uvIndices[i];
                unsigned int normalIndex = normalIndices[i];
                
                // Get the attributes thanks to the index
                float* vertex = temp_vertices[ vertexIndex-1 ];
                float* uv = temp_uvs[ uvIndex-1 ];
                float* normal = temp_normals[ normalIndex-1 ];
                
                // Put the attributes in buffers
                out_vertices.push_back(vertex);
                out_uvs     .push_back(uv);
                out_normals .push_back(normal);
        }
		printf("object loaded\n");

		float* vec = new float[out_vertices.size()*3];
		float* nor = new float[out_normals.size()*3];
		float* u = new float[out_uvs.size()*2];

		for(int i = 0, j = 0; j < out_vertices.size();j++)
		{
			vec[i++]=out_vertices[j][0]*scale;
			vec[i++]=out_vertices[j][1]*scale;
			vec[i++]=out_vertices[j][2]*scale;
		}
		for(int i = 0, j = 0; j < out_normals.size();j++)
		{
			nor[i++]=out_normals[j][0]*scale;
			nor[i++]=out_normals[j][1]*scale;
			nor[i++]=out_normals[j][2]*scale;
		}
		for(int i = 0, j = 0; j < out_uvs.size();j++)
		{
			u[i++]=out_uvs[j][0];
			u[i++]=out_uvs[j][1];
		}
		funcs.glGenBuffers(1,&vertexID);
		funcs.glBindBuffer(GL_ARRAY_BUFFER, vertexID);
		funcs.glBufferData(GL_ARRAY_BUFFER, ((out_vertices.size()*3)*sizeof(float)), vec,GL_STATIC_DRAW);

		funcs.glGenBuffers(1, &uvID);
		funcs.glBindBuffer(GL_ARRAY_BUFFER, uvID);
		funcs.glBufferData(GL_ARRAY_BUFFER, ((out_uvs.size()*2)*sizeof(float)), u, GL_STATIC_DRAW);

		funcs.glGenBuffers(1, &normalID);
		funcs.glBindBuffer(GL_ARRAY_BUFFER, normalID);
		funcs.glBufferData(GL_ARRAY_BUFFER, ((out_normals.size()*3)*sizeof(float)), nor, GL_STATIC_DRAW);

        return true;
}

void ObjectLoader::update(Matrix4 matrix, std::vector<Carrier> &carrier)
{
	Carrier tmp = Carrier();

	tmp.boundingBottomY = 1*scale;
	tmp.boundingLeftX = 1*scale;
	tmp.boundingRightX = 1*scale;
	tmp.boundingTopY = 1*scale;

	tmp.vertexID = vertexID;
	tmp.uvID = uvID;
	tmp.normalID = normalID;

	tmp.verSize = vertices.size();
	tmp.normSize = normals.size();
	tmp.uvSize = uvs.size();

	tmp.scale = scale;

	tmp.texture = texHandle;
	matrix = ~matrix; 
	tmp.trans = matrix;

	if(sun)
		tmp.sun = true;
	else 
		tmp.sun = false;

	carrier.push_back(tmp);
}

GLint ObjectLoader::getTexHan()
{
	return texHandle;
}

void ObjectLoader::scaleObj(float scale)
{
	Matrix4 M(4,4);
	M[0][0] = scale;
	M[1][1] = scale;
	M[2][2] = scale;
	float* M16 = new float[16];
	M16 = M.getMatrix16();
	glMultMatrixf(M16);
}

void ObjectLoader::setSun()
{
	sun = true;
}