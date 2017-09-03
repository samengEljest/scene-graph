//Carrrier has arrived
#pragma once
#include "Carrier.h"


Carrier::Carrier()
{}

Carrier::Carrier(const Carrier&temp)
{

	this->trans=temp.trans;

	this->textureLocation=temp.textureLocation;
	this->texture=temp.texture;

	this->vertexID=temp.vertexID;
	this->uvID=temp.uvID;
	this->normalID=temp.normalID;

	this->verSize=temp.verSize;
	this->uvSize=temp.uvSize;
	this->normSize=temp.normSize;

	this->sun=temp.sun;

	this->scale=temp.scale;

	this->boundingRightX=temp.boundingRightX;
	this->boundingLeftX=temp.boundingLeftX;
	this->boundingTopY=temp.boundingTopY;
	this->boundingBottomY=temp.boundingBottomY;

}