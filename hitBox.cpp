/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller (Group project)

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411625
Date: December 1, 2016

Description - Hitbox class
*/
#include "hitBox.h"
#include <stdio.h> //needed for printf command

HitBox::HitBox(float xcord, float ycord, float zcord,float len ){	//constructor
	//store the center of the cube
	x = xcord;
	y = ycord;
	z = zcord;

	length = len;
}

float HitBox::getX(){	//x getter
	return x;
}

float HitBox::getY(){	//y getter
	return y;
}

float HitBox::getZ(){	//z getter
	return z;
}

float HitBox::getLength(){	//get the length of the hitbox
	return length;
}

void HitBox::setX(float xs){ //x setter
	x = xs;
}

void HitBox::setY(float ys){ //y setter
	y = ys;
}

void HitBox::setZ(float zs){	//z setter
	z = zs;
}


