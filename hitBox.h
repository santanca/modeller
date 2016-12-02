/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Hitbox class
*/

class HitBox{
public:
	HitBox(float x, float y,float z, float length);	//constructor

	void hello();		//hello function
	float getX();
	float getY();
	float getZ();
	float getLength();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float x,y,z;
	float length;

private:
	float privateVar;
};
