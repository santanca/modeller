/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Material Node
*/
#ifndef __MATERIALNODE_H_
#define __MATERIALNODE_H_
#include "basicMathLibrary.h"
#include "Material.h"
#include "node.h"
using namespace std;

//Materila Node inherits form node
class MaterialNode: public Node{
	public:
		MaterialNode();
		MaterialNode(Material mat);
		Material material;
		virtual void pushNode();
		virtual void popNode();

	private:
};

#endif 