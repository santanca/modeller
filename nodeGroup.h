#ifndef __NODEGROUP_H__	
#define __NODEGROUP_H__

#include "node.h"
#include <iostream>
#include <fstream>
using namespace std;

//NodeGroup inherits from Node class
class NodeGroup: public Node{
public:
	NodeGroup();	//constructor
	
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
	//virtual void saveNode(ofstream& file);
};

#endif
