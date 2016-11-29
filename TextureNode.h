#ifndef __TEXTURENODE_H_
#define __TEXTURENODE_H_
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "basicMathLibrary.h"
//#include "Material.h"
#include "node.h"
using namespace std;


class TextureNode: public Node{
	public:
		TextureNode();
		TextureNode(GLuint mytexture);
		TextureNode(GLuint mytexture, NodeType);
		GLuint texture;
		NodeType textureType;
		virtual void nodeSpecificCodeDown();
		virtual void nodeSpecificCodeUp();

	private:
};

#endif 