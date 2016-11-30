#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "basicShapeLibrary.h"
#define T       1.73205080756887729
#define DIFF3(_a,_b,_c) { \
    (_c)[0] = (_a)[0] - (_b)[0]; \
    (_c)[1] = (_a)[1] - (_b)[1]; \
    (_c)[2] = (_a)[2] - (_b)[2]; \
}
 static GLfloat tdata[4][3] =
{
  {T, T, T},
  {T, -T, -T},
  {-T, T, -T},
  {-T, -T, T}
};

static int tndex[4][3] =
{
  {0, 1, 3},
  {2, 1, 0},
  {3, 2, 0},
  {1, 2, 3}
};

Shape::Shape(){}

void Shape::crossprod(GLfloat v1[3], GLfloat v2[3], GLfloat prod[3])
{
  GLfloat p[3];         /* in case prod == v1 or v2 */

  p[0] = v1[1] * v2[2] - v2[1] * v1[2];
  p[1] = v1[2] * v2[0] - v2[2] * v1[0];
  p[2] = v1[0] * v2[1] - v2[0] * v1[1];
  prod[0] = p[0];
  prod[1] = p[1];
  prod[2] = p[2];
}

void Shape::normalize(GLfloat v[3])
{
  GLfloat d;

  d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  if (d == 0.0) {
    //__glutWarning("normalize: zero length vector");
    v[0] = d = 1.0;
  }
  d = 1 / d;
  v[0] *= d;
  v[1] *= d;
  v[2] *= d;
}


void Shape::drawBox(GLdouble size){
	 static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    
    glTexCoord2f(0, 0);
    glVertex3fv(&v[faces[i][0]][0]);
    
    glTexCoord2f(0, 1);
    glVertex3fv(&v[faces[i][1]][0]);
    
    glTexCoord2f(1, 1);
    glVertex3fv(&v[faces[i][2]][0]);
    
    glTexCoord2f(1, 0);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void Shape::glutSolidCube2(GLfloat size){
	drawBox(size);
}

void Shape::recorditem(GLfloat * n1, GLfloat * n2, GLfloat * n3, GLenum shadeType){
  GLfloat q0[3], q1[3];

  DIFF3(n1, n2, q0);
  DIFF3(n2, n3, q1);
  crossprod(q0, q1, q1);
  normalize(q1);

  glBegin(shadeType);
  glNormal3fv(q1);
  glTexCoord2f(0, 0);
  glVertex3fv(n1);
  glTexCoord2f(0, 1);
  glVertex3fv(n2);
  glTexCoord2f(1, 1);
  glVertex3fv(n3);
  glEnd();
}

void Shape::subdivide(GLfloat * v0, GLfloat * v1, GLfloat * v2,GLenum shadeType){
  int depth;
  GLfloat w0[3], w1[3], w2[3];
  GLfloat l;
  int i, j, k, n;

  depth = 1;
  for (i = 0; i < depth; i++) {
    for (j = 0; i + j < depth; j++) {
      k = depth - i - j;
      for (n = 0; n < 3; n++) {
        w0[n] = (i * v0[n] + j * v1[n] + k * v2[n]) / depth;
        w1[n] = ((i + 1) * v0[n] + j * v1[n] + (k - 1) * v2[n])
          / depth;
        w2[n] = (i * v0[n] + (j + 1) * v1[n] + (k - 1) * v2[n])
          / depth;
      }
      l = sqrt(w0[0] * w0[0] + w0[1] * w0[1] + w0[2] * w0[2]);
      w0[0] /= l;
      w0[1] /= l;
      w0[2] /= l;
      l = sqrt(w1[0] * w1[0] + w1[1] * w1[1] + w1[2] * w1[2]);
      w1[0] /= l;
      w1[1] /= l;
      w1[2] /= l;
      l = sqrt(w2[0] * w2[0] + w2[1] * w2[1] + w2[2] * w2[2]);
      w2[0] /= l;
      w2[1] /= l;
      w2[2] /= l;
      recorditem(w1, w0, w2, shadeType);
    }
  }
}

void Shape::drawTriangle(int i, GLfloat data[][3], int ndx[][3], GLenum shadeType){
  GLfloat *x0, *x1, *x2;

  x0 = data[ndx[i][0]];
  x1 = data[ndx[i][1]];
  x2 = data[ndx[i][2]];
  subdivide(x0, x1, x2, shadeType);
}

void Shape::drawTetrahedron(GLenum shadeType){
  int i;

  for (i = 3; i >= 0; i--)
    drawTriangle(i, tdata, tndex, shadeType);
}

void Shape::glutSolidTetrahedron2(){
  drawTetrahedron(GL_TRIANGLES);
}





void Shape::doughnut(GLfloat r, GLfloat R, GLint nsides, GLint rings)
{
  int i, j;
  GLfloat theta, phi, theta1;
  GLfloat cosTheta, sinTheta;
  GLfloat cosTheta1, sinTheta1;
  GLfloat ringDelta, sideDelta;

  ringDelta = 2.0 * M_PI / rings;
  sideDelta = 2.0 * M_PI / nsides;

  theta = 0.0;
  cosTheta = 1.0;
  sinTheta = 0.0;

  GLfloat twoPi = 2* 3.1415;
  GLfloat threePi =  3* 3.1415;
  for (i = rings - 1; i >= 0; i--) {
    theta1 = theta + ringDelta;
    cosTheta1 = cos(theta1);
    sinTheta1 = sin(theta1);
    glBegin(GL_QUAD_STRIP);
    phi = 0.0;
    for (j = nsides; j >= 0; j--) {
      GLfloat cosPhi, sinPhi, dist;

      phi += sideDelta;
      cosPhi = cos(phi);
      sinPhi = sin(phi);
      dist = R + r * cosPhi;

      glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
      glTexCoord2f((cosTheta1 * cosPhi)/twoPi ,(-sinTheta1 * cosPhi)/twoPi );
      glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
      
      glTexCoord2f((cosTheta1 * cosPhi)/twoPi ,(-sinTheta1 * cosPhi)/twoPi );
      glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
      glVertex3f(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
    }
    glEnd();
    theta = theta1;
    cosTheta = cosTheta1;
    sinTheta = sinTheta1;
  }
}



//https://gist.github.com/gyng/8939105
void Shape::drawSolidTorus(){
	double r = 0.07;
	double c = 0.15; int rSeg = 50;
	int cSeg = 50; int texture = 0;

  const double PI = 3.1415926535897932384626433832795;
  const double TAU = 2 * PI;

  for (int i = 0; i < rSeg; i++) {
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= cSeg; j++) {
      for (int k = 0; k <= 1; k++) {
        double s = (i + k) % rSeg + 0.5;
        double t = j % (cSeg + 1);

        double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
        double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
        double z = r * sin(s * TAU / rSeg);

        double u = (i + k) / (float) rSeg;
        double v = t / (float) cSeg;

        glTexCoord2f(u, v);
        glNormal3f(2 * x, 2 * y, 2 * z);
        glVertex3d(2 * x, 2 * y, 2 * z);
      }
    }
    glEnd();
  }

}

//https://gist.github.com/gyng/8939105
void Shape::drawSolidTorus(double r = 0.07, double c = 0.15, int rSeg = 50, int cSeg = 50, int texture = 0){

  const double PI = 3.1415926535897932384626433832795;
  const double TAU = 2 * PI;

  for (int i = 0; i < rSeg; i++) {
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= cSeg; j++) {
      for (int k = 0; k <= 1; k++) {
        double s = (i + k) % rSeg + 0.5;
        double t = j % (cSeg + 1);

        double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
        double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
        double z = r * sin(s * TAU / rSeg);

        double u = (i + k) / (float) rSeg;
        double v = t / (float) cSeg;

        glTexCoord2f(u, v);
        glNormal3f(2 * x, 2 * y, 2 * z);
        glVertex3d(2 * x, 2 * y, 2 * z);
      }
    }
    glEnd();
  }

}
