#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "nodeGroup.h"
using namespace std;

//Constructor for NodeGroup
NodeGroup::NodeGroup(){
	nodeType = group;
}

void NodeGroup::nodeSpecificCodeDown(){
	glPushMatrix();
}

void NodeGroup::nodeSpecificCodeUp(){
	glPopMatrix();
}
