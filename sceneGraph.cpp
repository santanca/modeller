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
#include "nodeShape.h"
#include "nodeTransformation.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
}

void SceneGraph::toRoot(){
	currentNode = rootNode;
}

void SceneGraph::toParent(){
	currentNode = currentNode->parent;
}

void SceneGraph::toChild(int i){
	if (i < currentNode->children->size() && i >= 0){
		currentNode = currentNode->children->at(i);
	}else{
		printf("Child out of range\n");
	}
}

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
		printf("ID not found amoung children\n");
	}
}

int SceneGraph::getCurrentNodeID(){
	return currentNode->id;
}

void SceneGraph::insertNode(Node *node){
	currentNode->children->push_back(node);
}

void SceneGraph::deleteCurrentNode(){
	vector<Node*> *temp = currentNode->children;
	toParent();
	for (int i = 0; i < temp->size(); ++i)
	{
		insertNode(temp->at(i));
	}
}

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
	if(index==-1){printf("Child not found\n");}

}

void SceneGraph::draw(){
	//printf("Insde Graph\n");
	rootNode->draw();
	/*point3D p (1,2,3);
	NodeTransformation t (translate,p);*/
	/*NodeShape s (teapot);
	s.draw();*/

}



