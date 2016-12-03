/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Shape Node
*/
#ifndef __SHAPENODE_H__	
#define __SHAPENODE_H__

#include "node.h"
#include <iostream>
#include <fstream>
#include "basicShapeLibrary.h"
using namespace std;


//ShapeNode inherits from Node class
class ShapeNode: public Node{
public:
	ShapeNode(NodeType type);	//constructor
	bool currentlySelected;
	Shape s;
	GLUquadricObj *sphereOBJ;
	virtual void pushNode();
	virtual void popNode();
};

#endif
