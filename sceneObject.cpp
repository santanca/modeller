/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Scene Object*/
#include "sceneObject.h"
using namespace std;

//Constructor
SceneObject::SceneObject(int id, TransformationNode *mytranslate, TransformationNode *myrotation, TransformationNode *myscale, ShapeNode *myshape, MaterialNode *mymaterial, TextureNode *mytexture, HitBox *myhitBox){
	this->id = id;
	translate = mytranslate;
	rotation = myrotation;
	scale = myscale;
	shape = myshape;
	material = mymaterial;
	texture = mytexture;
	material_id=0;
	hitBox = myhitBox;
}

//This method translates the object, given the transformaiton has a 3d point
void SceneObject::translateFunc(point3D pointTranslate){
	translate->trans.x += pointTranslate.x;
	translate->trans.y += pointTranslate.y;
	translate->trans.z += pointTranslate.z;
}

//This method scales the object, given the transformaiton has a 3d point
void SceneObject::scaleFunc(point3D pointScale){
	scale->trans.x += pointScale.x;
	scale->trans.y += pointScale.y;
	scale->trans.z += pointScale.z;
}

//This method rotates the object, given the transformaiton has a 3d point
void SceneObject::rotateFunc(point3D pointRotate){
	rotation->trans.x += pointRotate.x;
	rotation->trans.y += pointRotate.y;
	rotation->trans.z += pointRotate.z;
}

//Selects the object
void SceneObject::select(){
	shape->currentlySelected = true;
}

//Deselects the object
void SceneObject:: deselect(){
	shape->currentlySelected = false;
}
