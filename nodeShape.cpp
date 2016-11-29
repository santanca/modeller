#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "nodeShape.h"
using namespace std;

NodeShape::NodeShape(NodeType type){
	nodeType = type;
	currentlySelected = false;
	isDrawable = true;
	currentlySelected = false;

}

void NodeShape::nodeSpecificCodeDown(){	
	//glTranslatef(50,20 ,50);
	glColor3f(0,1,0);
	switch(nodeType){
		case cube:
			glColor3f(0.5,0.5,0.5);
			if(currentlySelected){
				glPushMatrix();
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			glutSolidCube(1);
			break;

		case sphere:
			glColor3f(0,1,0);
			if(currentlySelected){
				glPushMatrix();
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			glutSolidSphere(1,50,50);
			break;

		case torus:
				
				if(currentlySelected){
				glPushMatrix();
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
				}
				glEnable(GL_LIGHTING);
				
				//glRotatef(30,0,1,0);
				//glutWireCube(2);
				glutSolidTorus(0.3,0.6,100,100);
				//glutSolidTorus(10,20,100,100);
			break;

		case teapot:
			if(currentlySelected){
				glPushMatrix();
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			glutWireTeapot(1);
			//glutSolidTeapot
			break;

		case cone:
			glutSolidCone(0.5,1,10,10);
			break;
	}
}

void NodeShape::nodeSpecificCodeUp(){}
