#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "TransformationNode.h"
#include <stdio.h>
using namespace std;


TransformationNode::TransformationNode(NodeType mytype, point3D myP){
	nodeType = mytype;
	trans = myP;
}

void TransformationNode::pushNode(){
	switch(nodeType){
		case translate:
			glTranslatef(trans.x,trans.y,trans.z);
			break;
		case rotate:
			//printf("Inside the rotate function\n");
			glRotatef(trans.x,1,0,0);
			glRotatef(trans.y,0,1,0);
			glRotatef(trans.z,0,0,1);
			break;
		case scale:
			glScalef(trans.x,trans.y,trans.z);
			break;
	}
}

void TransformationNode::popNode(){}
