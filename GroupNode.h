/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Group Node
*/
#ifndef __GROUPNODE_H__	
#define __GROUPNODE_H__

#include "node.h"
using namespace std;

//GroupNode inherits from Node class
class GroupNode: public Node{
public:
	GroupNode();	//constructor
	
	virtual void pushNode();
	virtual void popNode();

};

#endif
