#ifndef __NODETRANSFORMATION_H__	
#define __NODETRANSFORMATION_H__

#include "node.h"
using namespace std;


//NodeTransformation inherits from Node class
class NodeTransformation: public Node{
public:
	/*Constructor: takes in the NodeType a.k.a the type of transformation
	and a 3D point that will represent either rotation angle, scale factor, or 
	transformation*/
	NodeTransformation();
	NodeTransformation(NodeType type, point3D myP);	
	point3D trans;
	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
	//virtual void saveNode(ofstream& file);
};

#endif
