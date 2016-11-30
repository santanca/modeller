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

TextureNode::TextureNode(){}

TextureNode::TextureNode(GLuint mytexture){
	texture = mytexture;
	textureType = cube;
	applyTexture = false;
}

TextureNode::TextureNode(GLuint mytexture, NodeType type){
	texture = mytexture;
	textureType	= type;
	applyTexture = false;
}

void TextureNode::nodeSpecificCodeDown(){
	//glPushMatrix();
	//printf("Inside TextureNode\n");
		//glLoadIdentity();
	if(applyTexture == true){
		if(textureType == torus){
			glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	    	glEnable(GL_TEXTURE_GEN_T);
	    	//glBindTexture(GL_TEXTURE_2D, textures[1]);
		}
			glBindTexture(GL_TEXTURE_2D, texture);
			glEnable(GL_TEXTURE_2D);
	} 
		//glBindTexture(GL_TEXTURE_2D,texture);
	//glPopMatrix();

};


void TextureNode::nodeSpecificCodeUp(){
	if (applyTexture == true){
		if(textureType == torus){
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	    glDisable(GL_TEXTURE_GEN_T);
		}
		glDisable(GL_TEXTURE_2D);
	}
};