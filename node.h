#pragma once
#include "Matrix4.h"
#include "Vector4.h"
#include "Carrier.h"
#include <vector>

class Node 
{
private:
	

public:	
	Node();  ///< defoult constructor
	void addChild(Node* n);  ///<adds a child to children
	virtual void update(Matrix4 matrix, std::vector<Carrier> &carrier) = 0;  ///< updates what needs to be done depending on what node its in, the calls its children to update
	
protected:
	vector <Node*> children;

};