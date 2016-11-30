#ifndef __NODESHAPE_H__	
#define __NODESHAPE_H__

#include "node.h"
#include <iostream>
#include <fstream>
#include "basicShapeLibrary.h"
using namespace std;


//NodeShape inherits from Node class
class NodeShape: public Node{
public:
	NodeShape(NodeType type);	//constructor
	bool currentlySelected;
	Shape s;
	GLUquadricObj *sphereOBJ;
	//void draw();
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();

	//virtual void saveNode(ofstream& file);
};

#endif
