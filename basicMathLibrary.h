/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Basic math class
*/
#ifndef __BASICMATHLIBRARY_H_
#define __BASICMATHLIBRARY_H_
class point3;
class vec3D;

//3D point class
class point3D{
public: 
	point3D();
	point3D(float xIn, float yIn, float zIn);
	float Distance(point3D p3);
	float FastDistance(point3D p2);
	float x,y,z;	
private:
};

//3D vector class
class vec3D{
public:
	vec3D();
	vec3D(float xIn, float yIn, float zIn);
	float x,y,z,mag;
	float length();
	vec3D getNormal(vec3D v2);
	vec3D normalize();
	vec3D add(vec3D v2);
	vec3D vectorMultiply(float scalar);
	vec3D createVector(point3D p1, point3D p2);

private:
};

//

//Represents a colour using floats r,g,b
class colour{
public:
	float r,g,b;
private:
};

#endif
