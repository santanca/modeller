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
	Shape s;
	GLUquadricObj *sphereOBJ = NULL;

}

void NodeShape::nodeSpecificCodeDown(){	
	//glTranslatef(50,20 ,50);
	//glColor3f(0,1,0);
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
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					//glLoadIdentity();
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
			//glutWireTeapot(1);
			glutSolidTeapot(1);
			break;

		case tetrahedron:
			if(currentlySelected){
				glPushMatrix();
					//glDisable(GL_COLOR_MATERIAL);
					glDisable(GL_LIGHTING);
					//glColor3f(0,1,0);
					glutWireCube(2);
					glEnable(GL_LIGHTING);
				glPopMatrix();
			}
			//glutWireTeapot(1);
			//glutSolidCone(1,1,100,100);
			s.glutSolidTetrahedron2();
			//glutSolidTetrahedron();
			break;
	}
}

void NodeShape::nodeSpecificCodeUp(){}
