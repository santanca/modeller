#ifndef __NODE_H__
#define __NODE_H__

#include "basicMathLibrary.h"
#include <vector>

using namespace std;

//Different type of nodes
enum NodeType{
	root,
	group,
	
	//tranlsation nodes
	scale,
	translate,
	rotate,
	
	//shape nodes
	cube,
	sphere,
	torus,
	teapot,
	cone

	//textures/materials
	//material,
	//textures,
			
};

extern int getID();

//Node class
class Node{
	public:
		Node();	//constructor
		//Node(int id);
		Node* parent;
		vector<Node*> *children;
		int id;
		int currentChildNode;
		bool isDrawable;
		NodeType nodeType;
		void draw();
		
		virtual void nodeSpecificCodeDown();
		virtual void nodeSpecificCodeUp();
	private:
};

#endif