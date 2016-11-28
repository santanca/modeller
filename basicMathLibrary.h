/*
Computer Graphics 3GC3 Assignment 2: Terrain Modeling 

Cesar Antonio Santana Penner - 001411598
Date: November 9, 2016
*/
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
