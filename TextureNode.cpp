/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Texture Node
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
#include "TextureNode.h"
#include <stdio.h>

//Empty Constructor
TextureNode::TextureNode(){}

//TextureNode Constructor given its texture
TextureNode::TextureNode(GLuint mytexture){
	texture = mytexture;
	textureType = cube;
	applyTexture = false;
}

//TextureNode Constructor given the texture and the shape
TextureNode::TextureNode(GLuint mytexture, NodeType type){
	texture = mytexture;
	textureType	= type;
	applyTexture = false;
}

//Apply the texture onto the object
void TextureNode::pushNode(){
	//if the texturing is enabled for this oject
	if(applyTexture == true){
		//special case for torus texturing. Because calculating texture coordinates is difficult
		// we used auto generated texture coordinates
		if(textureType == torus){
			glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	    	glEnable(GL_TEXTURE_GEN_T);
		}
			glBindTexture(GL_TEXTURE_2D, texture);
			glEnable(GL_TEXTURE_2D);
	} 
};

//Once the object has been drawn, disables the texture
void TextureNode::popNode(){
	//Disables the texuring one the object hass been drawn
	if (applyTexture == true){
		if(textureType == torus){
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	    glDisable(GL_TEXTURE_GEN_T);
		}
		glDisable(GL_TEXTURE_2D);
	}
};