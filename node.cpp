#include "node.h"

Node::Node()
{}

void Node::addChild(Node* n)
{
	children.push_back(n);
}