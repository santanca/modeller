/*
Computer Graphics 3GC3 Assignment 2: Terrain Modeling 

Cesar Antonio Santana Penner - 001411598
Date: November 9, 2016
*/
#include "basicMathLibrary.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

//3D point empty constructor
point3D::point3D(){}

//3D point constructor
point3D::point3D(float xIn, float yIn, float zIn){
	x = xIn;
	y= yIn;
	z = zIn;
}

//3D get the distance between two 3d points
float point3D::Distance(point3D p2){
	float distance = sqrt(pow((p2.x - x),2) + pow((p2.y - y),2)+pow(p2.z - z,2));
	return distance;
}

//fast formula
float point3D::FastDistance(point3D p2){
	float distance = pow((p2.x-x),2) + pow((p2.y - y),2) + pow((p2.z-z),2);
}

//3D vector constructors
vec3D::vec3D(){}
vec3D::vec3D(float xIn, float yIn, float zIn){
	x = xIn;
	y = yIn;
	z = zIn;
	mag = this->length();
}

//Returns the length of a 3D Vector
float vec3D::length(){
	float length = sqrt(pow(x,2) + pow(y,2));
	mag = length;
	return length;
}

//Reutnrs the normalized version of the vector
vec3D vec3D::normalize(){
	float normX = x/this->mag;
	float normY = y/this->mag;
	float normZ = z/this->mag;
	vec3D v (normX,normY,normZ);
	return v;
}

//Returns the normalized cross product between two vectors
vec3D vec3D::getNormal(vec3D v2){
	float normX = (this->y * v2.z) - (v2.y * this->z);
	float normY = (this->z * v2.x) - (v2.z * this->x);
	float normZ = (this->x * v2.y) - (v2.x * this->y);
	vec3D v (normX, normY, normZ);
	return v.normalize();
	//return v
}

//Multiplies the vector by same scalar
vec3D vec3D::vectorMultiply(float scalar){
	vec3D v (scalar * this->x, scalar * this->y, scalar * this->z);
	return 	v;
}

//creates a vector given two 3D points
vec3D vec3D::createVector(point3D p1, point3D p2){
	vec3D v (p2.x -p1.x,p2.y-p1.y, p2.z - p1.z);
	return v;
}

//adds two vectors together
vec3D vec3D::add(vec3D v2){
	vec3D v (this->x + v2.x, this->y + v2.y, this->z + v2.z);
	return v;
}

//moves a 3d point
point3D movePoint(point3D p, vec3D v){
	point3D p1 (p.x + v.x, p.y + v.y, p.z + v.z);
	return p1;
}

