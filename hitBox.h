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

	float getX();			//getters
	float getY();
	float getZ();
	float getLength();		//length getter
	void setX(float x);		//setters
	void setY(float y);
	void setZ(float z);

	float x,y,z;			//the center of the hitbox
	float length;			//length of cube

//private:
	//float privateVar;
};
