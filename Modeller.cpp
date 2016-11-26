/*
Computer Graphics 3GC3 Assignment 2: Terrain Modeling 

Cesar Antonio Santana Penner - 001411598
Date: November 9, 2016
*/
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "basicMathLibrary.h"
using std::vector;


int roomSize = 300;

float angleX = 0;
float angleY = 0;
bool shadingGouraud = true;
bool lightingOn = true;
bool trianglesOn = true;	//draw terrain with triangles if true, else draw with quads
bool HypsometricColors = false;
bool faultMapOn = false;


/*wire frame mode 
				= 0 - solid polygons
				= 1 - just the wire frame
				= 2 - both					*/
int wireFrameMode = 0;

/*** CAMERA LOCATION ***/
float camPos[] = {100,10,100}; 	//where the camera is
float camUp[] = {0,1,0}; 	//up vector of the camera
float camTarget[] = {50,0,50}; //where the camera is looking at
float camSpeed = 0.1f;

/*** LIGHT0 LOCATION ***/
float light0_Pos[] = {100, 20, 100, 1};
/*** LIGHT1 LOCATION ***/
float light1_Pos[] = {0,20,0,1};




//reset the values of the material
void resetMaterial(){
	//define material
	float m_amb[] = {0.1, 0.1, 0.1, 1.0};
	float m_dif[] = {0.5, 0.5, 0.5, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny =10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}


//draw the terrain, using the height map
void drawBackGround(){
	glBegin(GL_QUADS);
		//floor
		glColor3f(0,1,0);
		
		glVertex3f(0,0,0);
		glVertex3f(roomSize,0,0);
		glVertex3f(roomSize,0,roomSize);
		glVertex3f(0,0,roomSize);

		glColor3f(1,0,0);
		//wall 1
		glVertex3f(0,0,0);
		glVertex3f(0,0,roomSize);
		glVertex3f(0,roomSize,roomSize);
		glVertex3f(0,roomSize,0);
		
		glColor3f(0,0,1);
		//wall 2
		glVertex3f(0,roomSize,0);
		glVertex3f(roomSize,roomSize,0);
		glVertex3f(roomSize,0,0);
		glVertex3f(0,0,0);
	glEnd();




}



//OpenGL keyboard function that handles keyboard events
void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:	//esc key
			exit (0);
		
		//
		case 'r':	
			
			break;
		//
		case 'R':

			break;

		//toggle lighting
		case 'l':
			if(lightingOn == true){
				lightingOn = false;
			}else{
				lightingOn = true;
			}
			break;

		//toggle drawing terrain with quads or traingles
		case 't':
			trianglesOn = true;
			break;
		case 'y':
			trianglesOn = false;
			break;

		//toggle map size
		case 'm':

			
			break;	

		//toggle hypsometric tints
		case 'b':
			
			break;

		//toggle fault algorithm
		case 'f':
			
			
			break;


		//movecamera taget
		case 'k':
			camTarget[0] += 10;
			break;
		case 'c':
			camTarget[1] -= 10;
			break;
		case 'h':
			camTarget[0] -= 10;
			break;
		case 'v':
			camTarget[1] += 10;
			break;
		case 'u':
			camTarget[2] -= 10;
			break;
		case 'j':
			camTarget[2] += 10;
			break;	

		//change position of light 0
		case 'W':
			light0_Pos[2] -= 5;
			glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
			break;
		case 'S':
			light0_Pos[2] +=5;
			glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
			break;
		case 'D':
			light0_Pos[0] +=5;
			glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
			break;
		case 'A':
			light0_Pos[0] -=5;
			glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
			break;

		//change position of light 0
		case 'U':
			light1_Pos[2] -= 5;
			glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
			break;
		case 'J':
			light1_Pos[2] +=5;
			glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
			break;
		case 'K':
			light1_Pos[0] +=5;
			glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
			break;
		case 'H':
			light1_Pos[0] -=5;
			glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
			break;

	}
	glutPostRedisplay();



}

//OpenGl special function handling all special keyboard events
void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
    /************************************************************************
     
                        CAMERA CONTROLS
     
     ************************************************************************/
	switch(key)
	{
	//camera control
	case GLUT_KEY_LEFT:
		angleX -= 5;
		break;
	case GLUT_KEY_RIGHT:
		angleX += 5;
		break; 	
	case GLUT_KEY_UP:
		angleY +=5;
		break;
	case GLUT_KEY_DOWN:
		angleY -=5;
		break;
    }
	glutPostRedisplay();
}

//Prints all the instructions
void printInstruction(){
	printf("\n\n");
	printf("\t \t Hello and welcome to our 3D Modeller program\n");
	printf("--------------------By Juan Sanatan and Cesar Santana-----------------------------\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("q or ESCAP----------------> Quit the program\n");
}

//initilize height map,camera, lighting, shading variables
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
    printInstruction();

    //heightMap = generateFaultHeightMap();

    /************************************************************************
     
                            PERSPECTIVE SET UP!
     
     modelview moves the eye and objects, projection is for camera type
     frustum
     
     ************************************************************************/
    glMatrixMode(GL_PROJECTION);
    //glFrustum(-10,10,-10,10,0,100);
	gluPerspective(45, 1, 1, 100*2);

	//enable lighting
	glEnable(GL_DEPTH_TEST);	//enable the depth test and enable lights
	glEnable(GL_LIGHTING);		//enable lighting
	glEnable(GL_LIGHT0);		//turn on light bulb 0
	glEnable(GL_LIGHT1);		//turn on light bulb 1

	//define light properties
	float pos[4] = {100/2, 0, 100/2, 1};
	float amb[4] = {0.5, 0.5, 0.5, 1};
	float dif[4] = {1, 1, 1, 1};
	float spc[4] = {1, 1, 1, 1};

	//upload material data to gpu
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spc);

	float pos2[4] = {0, 0, 0, 1};
	float amb2[4] = {0.5, 0.5, 0.5, 1};
	float dif2[4] = {1, 1, 1, 1};
	float spc2[4] = {1, 1, 1, 1};

	//upload material data to gpu
	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spc2);

	
/*	//define material
	float m_amb[] = {0.1, 0.1, 0.1, 1.0};
	float m_dif[] = {0.5, 0.5, 0.5, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny =10; //10, 100

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);*/

	//define smooth (guaruod) shading*/
	//glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

}


//inverts the y coordinate on the 2d terrain window
int invert(int y){
	return 800 - y;
}

//handles the mouse events
void mouse(int btn, int state, int x, int y){
	//create a bump if the left mouse button is pressed
	if(btn == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
	
		}

	//create a dent if the right button is pressed
	}else if(btn == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN){
			
		}
	}

	glutPostRedisplay();

}



/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    /************************************************************************
     
                                    CAMERA SET UP
     
     ************************************************************************/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], 
			camTarget[0], camTarget[1], camTarget[2], 
			camUp[0], camUp[1], camUp[2]); 


	drawBackGround();
	
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT

	//main window set up
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Terrain Modeling");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();

	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
