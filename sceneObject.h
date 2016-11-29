#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__

#include "node.h"
#include "nodeTransformation.h"
#include "nodeShape.h"
#include "MaterialNode.h"

//#include "nodeShape.cpp"
//#include <vector>
//#include "node.cpp"
using namespace std;

class SceneObject{
	public: 
		SceneObject();
		SceneObject(int id, NodeTransformation *mytranslate, NodeTransformation *myrotation, NodeTransformation *myscale, NodeShape *myshape, MaterialNode *mymaterial);
		int id;
		NodeTransformation *translate;
		NodeTransformation *rotation;
		NodeTransformation *scale;
		NodeShape *shape;
		MaterialNode *material;
		int material_id;

		void translateFunc(point3D pointTranslate);	//float x, float y, float z
		void scaleFunc(point3D pointScale);
		void rotateFunc(point3D pointRotate);
		void select();
		void deselect();

	private:
};

#endif