/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Transformation Node header file 
*/
#ifndef __TRANSFORMATIONNODE_H__	
#define __TRANSFORMATIONNODE_H__

#include "node.h"
using namespace std;


//Transformation node inherits from Node class
class TransformationNode: public Node{
public:
	/*Constructor: takes in the NodeType a.k.a the type of transformation
	and a 3D point that will represents the position of the object*/
	TransformationNode();
	TransformationNode(NodeType type, point3D myP);	
	point3D trans;
	virtual void pushNode();
	virtual void popNode();
};

#endif
