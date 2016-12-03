/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Node class, parent to all other types of nodes
*/
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "node.h"
using namespace std;

//Constructor for a node
Node::Node(){
	id = getID();
	parent = 0;
	children = new vector<Node*>();
	isDrawable = false;
	nodeType = root;
	currentChildNode = 0;

}

//Draw the node 
void Node::draw(){
	pushNode();

	//iterate through the children and draw each child
	for (int i = 0; i < children->size(); ++i)
	{
		//printf("Inside Node\n");
		children->at(i)->draw();
	}

	popNode();


}

void Node::pushNode(){}
void Node::popNode(){}

