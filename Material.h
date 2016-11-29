#ifndef __MATERIAL_H_
#define __MATERIAL_H_
#include "basicMathLibrary.h"
using namespace std;

class Material{
	public:
		Material();
		Material(vec3D ambient, vec3D diffuse, vec3D specular, float shine);
		Material(float ambient[4], float diffuse[4], float specular[4], float shine);
		vec3D amb;
		vec3D dif;
		vec3D spec;
		float shiny;

		void setEmerald();
		void setRuby();
		void setYellowRubber();
		void setCyanPlastic();
		void setChrome();
		void setReset();
	private:
};

#endif 