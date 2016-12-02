#ifndef __GROUPNODE_H__	
#define __GROUPNODE_H__

#include "node.h"
using namespace std;

//GroupNode inherits from Node class
class GroupNode: public Node{
public:
	GroupNode();	//constructor
	
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
	//virtual void saveNode(ofstream& file);
};

#endif
