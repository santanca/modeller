/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Node class, parent to all other types of nodes
*/
#ifndef __NODE_H__
#define __NODE_H__

#include "basicMathLibrary.h"
#include <vector>

using namespace std;

//Different type of nodes
enum NodeType{
	root,
	group,
	
	//tranlsation nodes
	scale,
	translate,
	rotate,
	
	//shape nodes
	cube,
	sphere,
	torus,
	teapot,
	tetrahedron,

	//textures/materials nodes
	material,
	texture
			
};

extern int getID();

//Node class
class Node{
	public:
		Node();	//constructor
		Node* parent;
		vector<Node*> *children;
		int id;
		int currentChildNode;
		bool isDrawable;
		NodeType nodeType;
		void draw();
		
		virtual void nodeSpecificCodeDown();
		virtual void nodeSpecificCodeUp();
	private:
};

#endif
