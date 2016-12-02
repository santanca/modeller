#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "GroupNode.h"
using namespace std;

//Constructor for GroupNode
GroupNode::GroupNode(){
	nodeType = group;
}

void GroupNode::nodeSpecificCodeDown(){
	glPushMatrix();
}

void GroupNode::nodeSpecificCodeUp(){
	glPopMatrix();
}
