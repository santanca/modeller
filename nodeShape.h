#ifndef __NODESHAPE_H__	
#define __NODESHAPE_H__

#include "node.h"
#include <iostream>
#include <fstream>
using namespace std;


//NodeShape inherits from Node class
class NodeShape: public Node{
public:
	NodeShape(NodeType type);	//constructor
	bool currentlySelected;
	//void draw();
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();

	//virtual void saveNode(ofstream& file);
};

#endif
