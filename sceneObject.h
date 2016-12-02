/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Scene Object*/
#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__
//imported library and files
#include "node.h"
#include "TransformationNode.h"
#include "ShapeNode.h"
#include "MaterialNode.h"
#include "TextureNode.h"
#include "hitBox.h"
using namespace std;

/*Scene object class- represents an object in the scene
  A scene object has many transformations, shapes, meterial, texture,id, hitbox, etc. attributes	
*/
class SceneObject{
	public: 
		//Constructors
		SceneObject();
		SceneObject(int id, TransformationNode *mytranslate, TransformationNode *myrotation, TransformationNode *myscale, ShapeNode *myshape, MaterialNode *mymaterial, TextureNode *mytexture, HitBox *myhitBox);
		// instance variables
		int id;
		TransformationNode *translate;
		TransformationNode *rotation;
		TransformationNode *scale;
		ShapeNode *shape;
		MaterialNode *material;
		TextureNode *texture;
		HitBox *hitBox;
		int material_id;

		//functions that apply transformations to the scene object
		void translateFunc(point3D pointTranslate);	
		void scaleFunc(point3D pointScale);
		void rotateFunc(point3D pointRotate);
		void select();
		void deselect();

	private:
};

#endif