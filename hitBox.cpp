#include "hitBox.h"
#include <stdio.h> //needed for printf command

HitBox::HitBox(float xcord, float ycord, float zcord,float len ){	//constructor
	
	x = xcord;
	y = ycord;
	z = zcord;
	length = len;
	privateVar = 1;
}

void HitBox::hello(){	//our function hello
	printf("hello world, private variable is: %f, public variable is: %f\n",privateVar, privateVar);
}



float HitBox::getX(){	//our function hello
	return x;
}

float HitBox::getY(){	//our function hello
	return y;
}

float HitBox::getZ(){	//our function hello
	return z;
}

float HitBox::getLength(){
	return length;
}

void HitBox::setX(float xs){
	x = xs;
}

void HitBox::setY(float ys){
	y = ys;
}

void HitBox::setZ(float zs){
	z = zs;
}

