#include "lightNode.h"

LightNode::LightNode()
{
}

void LightNode::update(Matrix4 matrix, std::vector<Carrier> &carrier)
{
	
	GLfloat lightpos[] = {0,0,0,1};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->update(matrix, carrier);
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}