/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Texture Node*/
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
#include "node.h"
using namespace std;

//Texure Node class inherits from Node.
//Applies texture to the scene object.
class TextureNode: public Node{
	public:
		//Constructors
		TextureNode();
		TextureNode(GLuint mytexture);
		TextureNode(GLuint mytexture, NodeType);
		GLuint texture;	//the texture that this will have 
		NodeType textureType; //the node type
		bool applyTexture;	//texture toggling
		virtual void pushNode();
		virtual void popNode();

	private:
};

#endif 
