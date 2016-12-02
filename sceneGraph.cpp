/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Scene Graph 
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

#include "sceneGraph.h"
#include "ShapeNode.h"
#include "TransformationNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

//Constructor  
SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
}

//Makes Current node the root node
void SceneGraph::toRoot(){
	currentNode = rootNode;
}

//Traverses to the parent node of the current node
void SceneGraph::toParent(){
	currentNode = currentNode->parent;
}

//Traverse to one of the child node of the current node, given its position
void SceneGraph::toChild(int i){
	if (i < currentNode->children->size() && i >= 0){
		currentNode = currentNode->children->at(i);
	}else{
		//printf("Child out of range\n");
	}
}

//Traverse to the child node with a given ID
void SceneGraph::toChildID(int id){
	int index = -1;
	for (int i = 0; i < currentNode->children->size(); ++i)
	{
		if(currentNode->children->at(i)->id = id){
			index = i;
			break;
		}
	}
	if (index == -1){
		//printf("ID not found amoung children\n");
	}
}

//Gets the ID of the current Node
int SceneGraph::getCurrentNodeID(){
	return currentNode->id;
}

//Inserts node into the graph as child of the current node
void SceneGraph::insertNode(Node *node){
	currentNode->children->push_back(node);
}

//Deletes the current node, giving all of the children of the
// current node to the parent
void SceneGraph::deleteCurrentNode(){
	vector<Node*> *temp = currentNode->children;
	toParent();
	for (int i = 0; i < temp->size(); ++i)
	{
		insertNode(temp->at(i));
	}
}

//Deletes Node given its ID
void SceneGraph::deleteNode(int id){
	toRoot();
	int index = -1;
	for (int i = 0; i < currentNode->children->size(); ++i)
	{
		if(currentNode->children->at(i)->id == id){
			index = i;
			currentNode->children->erase(currentNode->children->begin() + index);
			break;
		}
	}
	if(index==-1){//printf("Child not found\n");
    }

}

//Draws the scene graph recusively
void SceneGraph::draw(){
	rootNode->draw();
}



