/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Scene Graph header 
*/
#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__
#include "node.h"

//Scene graph class
//Scene graph keeps hierarchical scene structure
class SceneGraph{
	public:
		SceneGraph(); 	//empty constructor
		void toRoot();	//reset the current node to the root (during traversal of the graph)
		
		//Graph Traversal,Insertion,Deletion methods
		void toParent();
		void toChild(int i);
		void toChildID(int id);
		int getCurrentNodeID();
		void insertNode(Node *node);
		void deleteCurrentNode();
		void deleteNode(int id);
		void draw();

		//Instance variables to keep track of root node and current node
		Node *rootNode;
		Node *currentNode;
	private:
};

#endif