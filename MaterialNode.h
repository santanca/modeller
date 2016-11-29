#ifndef __MATERIALNODE_H_
#define __MATERIALNODE_H_
#include "basicMathLibrary.h"
#include "Material.h"
#include "node.h"
using namespace std;

class MaterialNode: public Node{
	public:
		MaterialNode();
		MaterialNode(Material mat);
		Material material;
		virtual void nodeSpecificCodeDown();
		virtual void nodeSpecificCodeUp();

	private:
};

#endif 