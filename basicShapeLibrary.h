/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

ATTENTION: Since glutSolid<Shape> does not provide texture coordinates we got the
           source code from glut (https://www.opengl.org/resources/libraries/glut/).
           We used the same code to draw the shapes, but we modified the code to 
           provide texture coordinates.


Description - Shape class
*/
/* Copyright (c) Mark J. Kilgard, 1994, 1997. */

/**                                                                             
(c) Copyright 1993, Silicon Graphics, Inc.                                      

ALL RIGHTS RESERVED                                                             

Permission to use, copy, modify, and distribute this software                   
for any purpose and without fee is hereby granted, provided                     
that the above copyright notice appear in all copies and that                   
both the copyright notice and this permission notice appear in                  
supporting documentation, and that the name of Silicon                          
Graphics, Inc. not be used in advertising or publicity                          
pertaining to distribution of the software without specific,                    
written prior permission.

THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
"AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
PERFORMANCE OF THIS SOFTWARE.

US Government Users Restricted Rights

Use, duplication, or disclosure by the Government is subject to
restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer
Software clause at DFARS 252.227-7013 and/or in similar or
successor clauses in the FAR or the DOD or NASA FAR
Supplement.  Unpublished-- rights reserved under the copyright
laws of the United States.  Contractor/manufacturer is Silicon
Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
94039-7311.

OpenGL(TM) is a trademark of Silicon Graphics, Inc.
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

	private:
		
};



#endif
