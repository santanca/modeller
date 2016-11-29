#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "MaterialNode.h"
#include <stdio.h>
using namespace std;

MaterialNode::MaterialNode(){}

MaterialNode::MaterialNode(Material mat){
	material = mat;
}

void MaterialNode::nodeSpecificCodeDown(){
	glPushMatrix();
		//glLoadIdentity();
		printf("Inside Material %f %f %f \n",material.amb.x,material.amb.y, material.amb.z );

		float m_amb[] = {material.amb.x,material.amb.y, material.amb.z, 1.0};
		float m_dif[] = {material.dif.x, material.dif.y, material.dif.z, 1.0};
		float m_spec[] = {material.spec.x, material.spec.y, material.spec.z, 1.0};
		float shiny =10; //10, 100
		/*float m_amb2[] = {0.33, 0.22, 0.03, 1.0};
		float m_dif2[] = {0.78, 0.57, 0.11, 1.0};
		float m_spec2[] = {0.99, 0.91, 0.81, 1.0};
		float shiny2 = 27;*/

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glPopMatrix();
}

void MaterialNode::nodeSpecificCodeUp(){}