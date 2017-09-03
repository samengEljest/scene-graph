#pragma once
#include "GlWindow.h"


std::string vs = 
"#version 330 core\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform vec3 LightPosition_worldspace;\n"

"in vec3 vertex;\n"
"in vec2 uv;\n"
"in vec3 normal;\n"

"out vec2 UV;\n"
"out vec3 Position_worldspace;\n"
"out vec3 Normal_cameraspace;\n"
"out vec3 EyeDirection_cameraspace;\n"
"out vec3 LightDirection_cameraspace;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(vertex, 1.0);\n"

"	Position_worldspace = (model * vec4(vertex,1)).xyz;\n"

"	vec3 vertexPosition_cameraspace = ( view * model * vec4(vertex,1)).xyz;\n"
"	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;\n"

"	vec3 LightPosition_cameraspace = (view * vec4(LightPosition_worldspace,1)).xyz;\n"
"	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;\n"

	// Normal of the the vertex, in camera space
"	Normal_cameraspace = (view * model * vec4(normal,0)).xyz;\n"

	// UV of the vertex.
"	UV = uv;\n"
"}\n";

// pixel shader which quite simply just draws the texture to the surface.
std::string ps =
"#version 330 core\n"
"uniform sampler2D tex;\n"
"uniform vec3 LightPosition_worldspace;\n"
"uniform float isSun;\n"

"in vec2 UV;\n"
"in vec3 Position_worldspace;\n"
"in vec3 Normal_cameraspace;\n"
"in vec3 EyeDirection_cameraspace;\n"
"in vec3 LightDirection_cameraspace;\n"

"out vec3 color;\n"


"void main()\n"
"{\n"
"	if(isSun == 1){\n"
"		color = texture2D( tex, UV ).rgb;}\n"
"	else{\n"
		// Light emission properties
"		vec3 LightColor = vec3(1,0.9,0.9);\n"
"		float LightPower = 1500.0f;\n"
	
		// Material properties
"		vec3 MaterialDiffuseColor = texture2D( tex, UV ).rgb;\n"
"		vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;\n"
"		vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);\n"

		// Distance to the light
"		float distance = length( LightPosition_worldspace - Position_worldspace );\n"

		// Normal of the computed fragment, in camera space
"		vec3 n = normalize( Normal_cameraspace );\n"
		// Direction of the light (from the fragment to the light)
"		vec3 l = normalize( LightDirection_cameraspace );\n"
		// Cosine of the angle between the normal and the light direction, 
		// clamped above 0
		//  - light is at the vertical of the triangle -> 1
		//  - light is perpendicular to the triangle -> 0
		//  - light is behind the triangle -> 0
"		float cosTheta = clamp( dot( n,l ), 0,1 );\n"

		// Eye vector (towards the camera)
"		vec3 E = normalize(EyeDirection_cameraspace);\n"
		// Direction in which the triangle reflects the light

"		vec3 R = reflect(-l,n);\n"
		// Cosine of the angle between the Eye vector and the Reflect vector,
		// clamped to 0
		//  - Looking into the reflection -> 1
		//  - Looking elsewhere -> < 1
"		float cosAlpha = clamp( dot( E,R ), 0,1 );\n"
	
"		color = MaterialAmbientColor + MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) + MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);\n"
"	}\n"
"}\n";


GlWindow::GlWindow(QWidget* parent) : QGLWidget(parent)
{
	doBeginning();
	this->timer.setInterval(1);
	connect(&this->timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	this->timer.start();
}

void GlWindow::doBeginning()
{
	m_camYaw = 0.0f;
	m_camPitch = 0.0f;
	camraXPos = 0.0f;
	camraYPos = 0.0f;
	camraZPos = 0.0f;
	m_Camra = Matrix4(4,4);
	m_id = Matrix4(4,4);
	m_camrapos = Matrix4(4,4);
	matrix = new float[16];
	matrixModView = new float[16];
	carrier=vector<Carrier>();
	m_mouseIn = false;
	m_camMat = Matrix4(4,4);
}

GlWindow::~GlWindow()
{}

void GlWindow::initializeGL()
{
	glClearColor(0., 0., 0., 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	this->funcs.initializeGLFunctions();

	bool compiled, linked, bound;
	compiled = this->program.addShaderFromSourceCode(QGLShader::Vertex,vs.c_str());
	if (!compiled)
	{
		QString error = this->program.log();
		qErrnoWarning((const char*)error.constData());
	}

	compiled = this->program.addShaderFromSourceCode(QGLShader::Fragment, ps.c_str());
	if (!compiled)
	{
		QString error = this->program.log();
		qErrnoWarning((const char*)error.constData());
	}

	linked = this->program.link();

	if (!linked)
	{
		QString error = this->program.log();
		qErrnoWarning((const char*)error.constData());
	}
	else
	{
		this->modelLocation = this->program.uniformLocation("model");
		if (this->modelLocation == -1) qErrnoWarning("Model matrix has been removed because of optimization");
		this->viewLocation = this->program.uniformLocation("view");
		if (this->viewLocation == -1) qErrnoWarning("View matrix has been removed because of optimization");
		this->projectionLocation = this->program.uniformLocation("projection");
		if (this->projectionLocation == -1) qErrnoWarning("Projection matrix has been removed because of optimization");
		this->textureLocation = this->program.uniformLocation("tex");
		if (this->textureLocation == -1) qErrnoWarning("Texture variable has been removed because of optimization");
		this->vertexCoordLocation = this->program.attributeLocation("vertex");
		if (this->vertexCoordLocation == -1) qErrnoWarning("Vertex coordinate has been removed because of optimization");
		this->uvLocation = this->program.attributeLocation("uv");
		if (this->uvLocation == -1) qErrnoWarning("UV coordinate has been removed because of optimization");
		this->normalLocation = this->program.attributeLocation("normal");
		if (this->normalLocation == -1) qErrnoWarning("normal coordinate has been removed because of optimization");
		this->LightLocation = this->program.uniformLocation("LightPosition_worldspace");
		if (this->LightLocation == -1) qErrnoWarning("Light coordinate has been removed because of optimization");
		this->isSun = this->program.uniformLocation("isSun");
		if (this->isSun == -1) qErrnoWarning("sun boolean has been removed because of optimization");
	}

	this->program.enableAttributeArray(this->vertexCoordLocation);
	this->program.enableAttributeArray(this->uvLocation);

	funcs.glEnableVertexAttribArray(vertexCoordLocation);
	funcs.glEnableVertexAttribArray(uvLocation);
	funcs.glEnableVertexAttribArray(normalLocation);

	bound = this->program.bind();
	Q_ASSERT(bound);

	center = new TransformNode(0,0,0,0,0);

	TransformNode* sun = new TransformNode(0,0,0,0.2,0.);
	ObjectLoader* sunObj = new ObjectLoader(10);
	sunObj->setSun();
	sunObj->loadTexture("sun.png");
	sunObj->loadOBJ("sphere.obj", sunObj->vertices, sunObj->uvs,sunObj->normals, funcs);
	center->addChild(sun);
	sun->addChild(sunObj);

	TransformNode* p1 = new TransformNode(0,0,45,0.01,0.1);
	ObjectLoader* p1Obj = new ObjectLoader(1.2);
	p1Obj->loadTexture("azurothBig.png");
	p1Obj->loadOBJ("sphere.obj", p1Obj->vertices, p1Obj->uvs, p1Obj->normals, funcs);
	center->addChild(p1);
	p1->addChild(p1Obj);
	
	TransformNode* p2 = new TransformNode(0,0,25,-0.05,-0.3);
	p2->setRotateZ(28);
	ObjectLoader* p2Obj = new ObjectLoader(2);
	p2Obj->loadTexture("eatrh.png");
	p2Obj->loadOBJ("sphere.obj", p2Obj->vertices, p2Obj->uvs, p2Obj->normals, funcs);
	center->addChild(p2);
	p2->addChild(p2Obj);

	TransformNode* m1 = new TransformNode(0,0,5,0.2,0.2);
	ObjectLoader* m1Obj = new ObjectLoader(0.3);
	m1Obj->loadTexture("death.png");
	m1Obj->loadOBJ("sphere.obj", m1Obj->vertices, m1Obj->uvs, m1Obj->normals, funcs);
	p2->addChild(m1);
	m1->addChild(m1Obj);

	TransformNode* p3 = new TransformNode(0,0,-700,0.03,0.7);
	ObjectLoader* p3Obj = new ObjectLoader(2);
	p3Obj->loadTexture("yuggoth.png");
	p3Obj->loadOBJ("sphere.obj", p3Obj->vertices, p3Obj->uvs, p3Obj->normals, funcs);
	center->addChild(p3);
	p3->addChild(p3Obj);

	TransformNode* p4 = new TransformNode(0,0,57,0.04,0.3);
	ObjectLoader* p4Obj = new ObjectLoader(2.8);
	p4Obj->loadTexture("omicronPersei8.png");
	p4Obj->loadOBJ("sphere.obj", p4Obj->vertices, p4Obj->uvs, p4Obj->normals, funcs);
	center->addChild(p4);
	p4->addChild(p4Obj);

	ship = new TransformNode(0,-1,-1,0.,0.01);
	ObjectLoader* tardisObj = new ObjectLoader(0.005);
	//tardisObj->loadTexture("blue.png");
	//tardisObj->loadOBJ("tardis2.obj",tardisObj->vertices, tardisObj->uvs,tardisObj->normals, funcs);
	ship->addChild(tardisObj);

}
void GlWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//camra
	control(m_mouseIn);
	updateCamra();

	//Matrix4 M(4,4);
	//Matrix4 trans(4,4);

	//M[0][3] = -camraXPos;
	//M[1][3] = -camraYPos;
	//M[2][3] = -camraZPos;
	
	//Matrix4 RotX(4,4);
	//Matrix4 RotY(4,4);
	//Matrix4 RotSum(4,4);
	Matrix4 Cam(4,4);
	
	//RotX = RotX.rotateAxis(rotCamX, "X");
	//RotY = RotY.rotateAxis(rotCamY, "Y");
	//RotSum = RotY * RotX;
	//Cam = M*RotSum;

	ship->update(Cam, carrier); 

	funcs.glUniformMatrix4fv(modelLocation, 1, false, carrier[0].trans.getMatrix16());
	glBindTexture(GL_TEXTURE_2D, carrier[0].texture);

	//vertex
	funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[0].vertexID);
	funcs.glVertexAttribPointer(vertexCoordLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//uv
	funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[0].uvID);
	funcs.glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//normal
	funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[0].normalID);
	funcs.glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//Draw
	glDrawArrays(GL_TRIANGLES, 0, carrier[0].verSize);

	carrier.clear();
	//camra end


	funcs.glUniform3f(LightLocation, 0,0,0);
	Matrix4 id(4,4);
	center->update(id, carrier);


	for(int i = 0; i < carrier.size(); i++)
	{
		Matrix4 modelView(4,4);
		modelView = modelView  * carrier[i].trans * m_Camra;

		float x = modelView[3][0];
		float y = modelView[3][1];
		float z = modelView[3][2];
		bool culled = false;

		if(x + 2.1 + carrier[i].boundingRightX < getFrustumLeftX(z) || 
			x - 2.1 - carrier[i].boundingLeftX > getFrustumRightX(z) || 
			y + 2.1 + carrier[i].boundingTopY < getFrustumBottomY(z) ||
			y - 2.1 - carrier[i].boundingBottomY > getFrustumTopY(z))
		{
			culled = true;
		}

		program.setUniformValue(textureLocation, 0);
		funcs.glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, carrier[i].texture);

		funcs.glUniformMatrix4fv(modelLocation, 1, false, carrier[i].trans.getMatrix16());
		
		if(carrier[i].sun)
			funcs.glUniform1f(isSun, 1);
		else
			funcs.glUniform1f(isSun, 0);

		//vertex
		funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[i].vertexID);
		funcs.glVertexAttribPointer(vertexCoordLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//uv
		funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[i].uvID);
		funcs.glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//normal
		funcs.glBindBuffer(GL_ARRAY_BUFFER, carrier[i].normalID);
		funcs.glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//draw
		if (!culled)
		{
			glDrawArrays(GL_TRIANGLES,0,carrier[i].verSize); 
		}
		else
		{
			cout << "Culled:" << i << " ";
		}
	}
	cout << endl;
	carrier.clear();
}


void GlWindow::resizeGL( int width, int height )
{
	m_proj = m_proj.persProj(60.0, 16/10, 0.001, 1000);
	funcs.glUniformMatrix4fv(projectionLocation, 1, false, m_proj.getMatrix16());
	glViewport(0, 0, width, height);

}

void GlWindow::updateCamra()
{
	Matrix4 traTmp(4,4);
	traTmp[3][0] = camraXPos; 
	traTmp[3][1] = camraYPos;
	traTmp[3][2] = camraZPos;

	traTmp = traTmp * traTmp.rotateAxis(rotCamY, "Y");
	traTmp = traTmp * traTmp.rotateAxis(rotCamX, "X");

	m_Camra = traTmp;

	funcs.glUniformMatrix4fv(viewLocation, 1, false, m_Camra.getMatrix16());

}

float GlWindow::getFrustumRightX(float deep)
{
	float pi = 3.14159265359;
	float tmp = pi - ((pi/3)*(16/10));
	return -(1.0f / 2.0f) * deep / sin(tmp/2);
}

float GlWindow::getFrustumLeftX(float deep)
{
	float pi = 3.14159265359;
	float tmp = pi - ((pi/3)*(16/10));
	return (1.0f / 2.0f) * deep / sin(tmp/2);
}

float GlWindow::getFrustumTopY(float deep)
{
	float pi = 3.14159265359;
	return -(1.0f / 2.0f) * deep / sin(pi / 3);
}

float GlWindow::getFrustumBottomY(float deep)
{
	float pi = 3.14159265359;
	return (1.0f / 2.0f) * deep / sin(pi / 3);
}

void GlWindow::lockCamera()
{
	if (m_camPitch > 90)
	{
		m_camPitch = 90;
	}
	if (m_camPitch < -90)
	{
		m_camPitch = -90;
	}
	if (m_camYaw < 0.0)
	{
		m_camYaw += 360;
	}
	if (m_camYaw > 360)
	{
		m_camYaw -= 360;
	}
}


void GlWindow::control(bool i_mi)
{
	if(i_mi) // mouse inside the window?
	{
		QPoint t_screenRes = mapToGlobal(QPoint(width()/2,height()/2));

		POINT t_mousePos;
		GetCursorPos(&t_mousePos);

		m_camYaw += + 0.1f * (t_screenRes.rx()-t_mousePos.x);	
		m_camPitch += 0.1f * (t_screenRes.ry()-t_mousePos.y);

		lockCamera();
		SetCursorPos(t_screenRes.rx(), t_screenRes.ry());
	}
	rotCamX = m_camPitch;
	rotCamY = m_camYaw;
}

void GlWindow::keyPressEvent(QKeyEvent *event)
{
	float pi = 3.14159265359;
    if(event->key() == Qt::Key_W)
	{
		camraZPos += cos(rotCamY*pi/180);
		camraXPos += sin(rotCamY*pi/180);
		camraYPos -= sin(rotCamX*pi/180);
	}
	else if(event->key() == Qt::Key_A)
	{
		camraXPos += cos(rotCamY*pi/180);
		camraZPos -= sin(rotCamY*pi/180);
	}
	else if(event->key() == Qt::Key_S)
	{
		camraZPos -= cos(rotCamY*pi/180);
		camraXPos -= sin(rotCamY*pi/180);
		camraYPos += sin(rotCamX*pi/180);
	}
	else if(event->key() == Qt::Key_D)
	{
		camraXPos -= cos(rotCamY*pi/180);
		camraZPos += sin(rotCamY*pi/180);
	}
	else if(event->key() == Qt::Key_Up)
    {
        rotCamX++;
    }
	else if(event->key() == Qt::Key_Down)
    {
        rotCamX--;
    }
	else if(event->key() == Qt::Key_Left)
    {
        rotCamY++;
    }
	else if(event->key() == Qt::Key_Right)
    {
        rotCamY--;
    }
	else if(event->key() == Qt::Key_Space)
    {
        camraYPos--;
    }
	else if(event->key() == Qt::Key_Control)
    {
        camraYPos++;
    }
	else if(event->key() == Qt::Key_1)
    {
        RandObject();
    }
}

 void GlWindow::mousePressEvent(QMouseEvent *event)
 {
	QPoint t_screenRes = mapToGlobal(QPoint(width()/2,height()/2));
	SetCursorPos(t_screenRes.rx(), t_screenRes.ry());

	GetCursorPos(&m_mousePos);
	m_mouseIn = true;
	ShowCursor(false);
 }

 void GlWindow::mouseReleaseEvent(QMouseEvent *event)
 {
	 m_mouseIn = false;
	 ShowCursor(true);
 }

void GlWindow::RandObject()
{
	float distance = rand() % 100;
	float orbSpeed = rand() % 20;
	orbSpeed -= 10;
	orbSpeed /= 100;
	float selfSpeed = rand() % 20;
	selfSpeed -= 10;
	selfSpeed /= 100;

	float scale = rand() % 10;
	scale /= 10;

	QString textures[] = {"eatrh.png", "yuggoth.png", "omicronPersei8.png", "death.png", "azurothBig.png"};
	int texture = rand() % 5;

	TransformNode* randP = new TransformNode(0,0,distance,orbSpeed,selfSpeed);
	ObjectLoader* randPObj = new ObjectLoader(scale);
	randPObj->loadTexture(textures[texture]);
	randPObj->loadOBJ("sphere.obj", randPObj->vertices, randPObj->uvs, randPObj->normals, funcs);
	center->addChild(randP);
	randP->addChild(randPObj);
}