/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Shape node 
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
#include "ShapeNode.h"
using namespace std;

//Constructor
ShapeNode::ShapeNode(NodeType type){
	nodeType = type;
	currentlySelected = false;
	isDrawable = true;
	currentlySelected = false;
	Shape s;
	GLUquadricObj *sphereOBJ = NULL;

}

//Draw the shape
void ShapeNode::pushNode(){	
	//draw the shape based on the type of node
	glColor3f(0,1,0);
	switch(nodeType){
		case cube:
			glColor3f(0.5,0.5,0.5);
			if(currentlySelected){
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			//glutSolidCube(1);
			s.glutSolidCube2(1);
			break;

		case sphere:
			sphereOBJ = gluNewQuadric();
    			gluQuadricDrawStyle(sphereOBJ, GLU_FILL);
    			gluQuadricTexture(sphereOBJ, GL_TRUE);
    			gluQuadricNormals(sphereOBJ, GLU_SMOOTH);

			glColor3f(0,1,0);
			if(currentlySelected){
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
					glEnable(GL_LIGHTING);
				glPopMatrix();
			}
			//glutSolidSphere(1,50,50);
			gluSphere(sphereOBJ, 1, 20, 20);

			glEnable(GL_LIGHTING);
			break;

		case torus:
				
				if(currentlySelected){
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
				}
				glEnable(GL_LIGHTING);
				glutSolidTorus(0.3,0.6,100,100);
			break;

		case teapot:
			if(currentlySelected){
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glColor3f(0,1,0);
					glutWireCube(2);
				glPopMatrix();
			}
			glEnable(GL_LIGHTING);
			glutSolidTeapot(1);
			break;

		case tetrahedron:
			if(currentlySelected){
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glutWireCube(2);
					glEnable(GL_LIGHTING);
				glPopMatrix();
			}
			s.glutSolidTetrahedron2();
			//glutSolidTetrahedron();
			break;
	}
}


void ShapeNode::popNode(){}
