#pragma once
#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QtOpenGL\QGLWidget>
#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include "ui_lab2.h"
#include <GL/glu.h>

#include "Carrier.h"
#include <math.h>
#include <string>

#include "objectLoader.h"
#include "lightNode.h"
#include "node.h"
#include "transformNode.h"

#include <QKeyEvent>
#include <QMouseEvent>

#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"

/*!
	this is the class that handels the OpenGl window
*/
class GlWindow : public QGLWidget
{
	Q_OBJECT
public:
	GlWindow(QWidget* parent = 0); ///< opens the openGL window with the chosen file, sets the size to the picture
	~GlWindow();
	int objectCount;
	int lightX;
	int lightY;
	int lightZ;
	Matrix4 camraRotate(float theta,string axis);  ///<  rotates the camra
	double rotCamX; 
	double rotCamY;
	void doBeginning(); ///< initialize stuff
	void updateCamra(); //updates the m_camra matrix

	void newObject(QString texture, const char* newobject); ///< creates a new object

	vector<Carrier> carrier;

public slots:
	void RandObject(); ///< creates a new planet

private:
	Ui::Lab2Class ui;
	float rotate;
	QTimer timer;

	TransformNode* center;
	TransformNode* ship;

	double camraXPos, camraYPos, camraZPos;
	QGLShaderProgram program;
	QGLFunctions funcs;

	Matrix4 m_Camra;
	Matrix4 m_id;
	Matrix4 m_camrapos;
	Matrix4 m_Frustum;
	Matrix4 m_proj;

	float m_camX, m_camY, m_camZ;
	float m_camYaw;
 	float m_camPitch;
	Matrix4 m_camMat;

	float* matrix;
	float* matrixModView;
	POINT m_mousePos;
	bool m_mouseIn;

	GLuint texture;
	float tmpspeed;


protected:
	void initializeGL(); ///< initialize option for the gl window and sets the scene graph
	void paintGL(); ///< paints the picture on the openGL window
	void resizeGL(int width, int height);///< resize the gl window
	void keyPressEvent(QKeyEvent *); ///< if a key is pressd, do different things
	void mousePressEvent(QMouseEvent *event); ///< if mause button is pressed, update camera rotation
	void mouseReleaseEvent(QMouseEvent *event); ///< if mause button is released, do not update camera rotation

	void lockCamera(); ///< lock camera at different degrees, makes it easier to control 
	void control(bool i_mi); // control the camera rotation

	float getFrustumBottomY(float deep); ///<used to compare id object is inside frustrum
	float getFrustumTopY(float deep); ///<used to compare id object is inside frustrum
	float getFrustumLeftX(float deep); ///<used to compare id object is inside frustrum
	float getFrustumRightX(float deep); ///<used to compare id object is inside frustrum

	GLint vertexCoordLocation;
	GLint uvLocation;
	GLint normalLocation;
	GLint projectionLocation;
	GLint viewLocation;
	GLint modelLocation;
	GLint textureLocation;
	GLint LightLocation;
	GLint isSun;
};
