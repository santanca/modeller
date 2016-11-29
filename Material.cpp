#include <stdio.h>
#include "Material.h"
#include "basicMathLibrary.h"

Material::Material(){
	vec3D amb (0,0,0);
	vec3D dif (0,0,0);
	vec3D spec (0,0,0);
	shiny = 0.0f;
}

Material::Material(vec3D ambient, vec3D diffuse, vec3D specular, float shine){
	amb = ambient;
	dif = diffuse;
	spec = specular;
	shiny = shine;
}

Material::Material(float ambient[4], float diffuse[4], float specular[4], float shine){
	amb.x = ambient[0];
	amb.y = ambient[1];
	amb.z = ambient[2];
	dif.x = diffuse[0];
	dif.y = diffuse[1];
	dif.z = diffuse[2];
	spec.x = specular[0];
	spec.y = specular[1];
	spec.z = specular[2];
	shiny = shine;
}

void Material::setEmerald(){
	amb.x = 0.0215;
	amb.y = 0.1745;
	amb.z = 0.0215;
	dif.x = 0.07568;
	dif.y = 0.61424;
	dif.z = 0.07568;
	spec.x = 0.633;
	spec.y = 0.727811;
	spec.z = 0.633;
	shiny = 0.6*128;
}

void Material::setRuby(){
	amb.x = 0.1745;
	amb.y = 0.01175;
	amb.z = 0.01175;
	dif.x = 0.61424;
	dif.y = 0.04136;
	dif.z = 0.04136;
	spec.x = 0.727811;
	spec.y = 0.626959;
	spec.z = 0.626959;
	shiny = 0.6*128;
}

void Material::setYellowRubber(){
	amb.x = 0.05;
	amb.y = 0.05;
	amb.z = 0.0;
	dif.x = 0.5;
	dif.y = 0.5;
	dif.z = 0.4;
	spec.x = 0.7;
	spec.y = 0.7;
	spec.z = 0.4;
	shiny = 0.78125*128;
}

void Material::setCyanPlastic(){
	amb.x = 0.0;
	amb.y = 0.1;
	amb.z = 0.06;
	dif.x = 0.0;
	dif.y = 0.50980392;
	dif.z = 0.50980392;
	spec.x = 0.50196078;
	spec.y = 0.50196078;
	spec.z = 0.50196078;
	shiny = 0.25*128;
}

void Material::setChrome(){
	amb.x = 0.24725;
	amb.y = 0.1995;
	amb.z = 0.0745;
	dif.x = 0.75164;
	dif.y = 0.60648;
	dif.z = 0.22648;
	spec.x = 0.628281;
	spec.y = 0.555802;
	spec.z = 0.366065;
	shiny = 0.4*128;
}

void Material::setReset(){
	amb.x = 0.1;
	amb.y = 0.1;
	amb.z = 0.1;
	dif.x = 0.5;
	dif.y = 0.5;
	dif.z = 0.5;
	spec.x = 0.99;
	spec.y = 0.91;
	spec.z = 0.81;
	shiny = 10;
}