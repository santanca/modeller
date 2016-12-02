/*
Computer Graphics 3GC3 Assignment 3: 3D Modeling 

Cesar Antonio Santana Penner - 001411598
Date: November 9, 2016
*/
#ifndef __BASICSHAPELIBRARY_H_
#define __BASICSHAPELIBRARY_H_
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <math.h>
class Shape{
	public:
		Shape();
		void glutSolidCube2(GLfloat size);
		void drawBox(GLdouble size);
		void glutSolidTetrahedron2();
		void drawTetrahedron(GLenum shadeType);
		void drawTriangle(int i, GLfloat data[][3], int ndx[][3], GLenum shadeType);
		void subdivide(GLfloat * v0, GLfloat * v1, GLfloat * v2,GLenum shadeType);
		void recorditem(GLfloat * n1, GLfloat * n2, GLfloat * n3, GLenum shadeType);
		void crossprod(GLfloat v1[3], GLfloat v2[3], GLfloat prod[3]);
		void normalize(GLfloat v[3]);
		//GLfloat tdata[4][3];
		//int tndex[4][3];


		void drawSolidTorus();
		void drawSolidTorus(double r, double c, int rSeg, int cSeg, int texture);
		void doughnut(GLfloat r, GLfloat R, GLint nsides, GLint rings);

	private:
		
};



#endif
