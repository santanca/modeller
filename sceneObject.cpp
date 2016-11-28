#include "sceneObject.h"
using namespace std;
//#include <vector>
//#include "basicMathLibrary.h"

SceneObject::SceneObject(int id, NodeTransformation *mytranslate, NodeTransformation *myrotation, NodeTransformation *myscale, NodeShape *myshape){
	this->id = id;
	translate = mytranslate;
	rotation = myrotation;
	scale = myscale;
	shape = myshape;
}

void SceneObject::translateFunc(point3D pointTranslate){
	translate->trans.x += pointTranslate.x;
	translate->trans.y += pointTranslate.y;
	translate->trans.z += pointTranslate.z;
}

void SceneObject::scaleFunc(point3D pointScale){
	scale->trans.x += pointScale.x;
	scale->trans.y += pointScale.y;
	scale->trans.z += pointScale.z;
}

void SceneObject::rotateFunc(point3D pointRotate){
	rotation->trans.x += pointRotate.x;
	rotation->trans.y += pointRotate.y;
	rotation->trans.z += pointRotate.z;
}

void SceneObject::select(){
	shape->currentlySelected = true;
}

void SceneObject:: deselect(){
	shape->currentlySelected = false;
}
