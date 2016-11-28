#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__
#include "node.h"

class SceneGraph{
	public:
		SceneGraph(); 	//empty constructor
		void toRoot();	//reset the current node to the root (during traversal of the graph)
		void toParent();
		void toChild(int i);
		void toChildID(int id);
		int getCurrentNodeID();
		void insertNode(Node *node);
		void deleteCurrentNode();
		void deleteNode(int id);
		void draw();
		//void save();
		//void deleteNode(int id);
		//vector<SceneObject*>* load();

		Node *rootNode;
		Node *currentNode;
	private:
		//void insertVector(vector<Node> nodes);

};

#endif