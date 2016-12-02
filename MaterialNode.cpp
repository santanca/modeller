/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Material Node
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
#include "MaterialNode.h"
#include <stdio.h>
using namespace std;

//Empty Constructor
MaterialNode::MaterialNode(){}

//Constructor given a material
MaterialNode::MaterialNode(Material mat){
	material = mat;
}

//Apply material to the object
void MaterialNode::nodeSpecificCodeDown(){
	glPushMatrix();
		float m_amb[] = {material.amb.x,material.amb.y, material.amb.z, 1.0};
		float m_dif[] = {material.dif.x, material.dif.y, material.dif.z, 1.0};
		float m_spec[] = {material.spec.x, material.spec.y, material.spec.z, 1.0};
		float shiny =10; //10, 100

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glPopMatrix();
}

//Diable the material once the object has been drawn
void MaterialNode::nodeSpecificCodeUp(){}