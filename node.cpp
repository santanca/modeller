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
	nodeSpecificCodeDown();

	//iterate through the children and draw each child
	for (int i = 0; i < children->size(); ++i)
	{
		printf("Inside Node\n");
		children->at(i)->draw();
	}

	nodeSpecificCodeUp();


}

void Node::nodeSpecificCodeDown(){}
void Node::nodeSpecificCodeUp(){}

