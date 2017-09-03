#pragma once
#include "node.h"
#include <QGLWidget>

class LightNode
	:public Node
{
public:
	LightNode(); ///< constructor
	void update(Matrix4 matrix, std::vector<Carrier> &carrier);  ///< sets light to the position 0,0,0 then calls update to its children


private:

};