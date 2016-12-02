/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Material class
*/
#ifndef __MATERIAL_H_
#define __MATERIAL_H_
#include "basicMathLibrary.h"
using namespace std;

//Material Class representing materials
class Material{
	public:
		//Constructors
		Material();
		Material(vec3D ambient, vec3D diffuse, vec3D specular, float shine);
		Material(float ambient[4], float diffuse[4], float specular[4], float shine);
		//instance variables
		vec3D amb;
		vec3D dif;
		vec3D spec;
		float shiny;

		//Changing the material
		void setEmerald();
		void setRuby();
		void setYellowRubber();
		void setCyanPlastic();
		void setChrome();
		void setReset();
	private:
};

#endif 