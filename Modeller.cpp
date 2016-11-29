/*
Computer Graphics 3GC3 Assignment 3: 3D Modeller

Cesar Antonio Santana Penner - 001411598
Juan Carlos Santana Penner - 001411...
Date: November ..., 2016
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
#include "sceneObject.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
//#include "basicMathLibrary.h"
using std::vector;


int roomSize = 100;
int nodeID = 0;

float angleX = 0;
float angleY = 0;
bool shadingGouraud = true;
bool light0_on = true;
bool light1_on = true;
int rotationMode = 0;
int materialMode = 0;

SceneGraph *sceneGraph;
SceneObject *currentObject;
int nextChild = 0;
int currentObjectIndex = 0;
vector<SceneObject*> *sceneObjectList = new vector<SceneObject*>;

/*** CAMERA LOCATION ***/
float camPos[] = {roomSize/4,10,roomSize/4}; 	//where the camera is
float camUp[] = {0,1,0}; 	//up vector of the camera
float camTarget[] = {0,0,0}; //where the camera is looking at
float camSpeed = 0.1f;

/*** LIGHT0 PROPERTIES ***/
float light0_Pos[] = {roomSize/2, 20, roomSize/2, 1};
float amb0[4] = {0.5, 0.5, 0.5, 1};
float dif0[4] = {1, 1, 1, 1};
float spc0[4] = {1, 1, 1, 1};


/*** LIGHT1 PROPERTIES ***/
float light1_Pos[] = {0,20,0,1};
float amb1[4] = {0.5, 0.5, 0.5, 1};
float dif1[4] = {1, 1, 1, 1};
float spc1[4] = {1, 1, 1, 1};

/*** LIGHT MATERIAL ***/
float m_amb2[] = {0.33, 0.22, 0.03, 1.0};
float m_dif2[] = {0.78, 0.57, 0.11, 1.0};
float m_spec2[] = {0.99, 0.91, 0.81, 1.0};
float shiny2 = 27;

/*** defualt material ***/
float m_amb[] = {0.1, 0.1, 0.1, 1.0};
float m_dif[] = {0.5, 0.5, 0.5, 1.0};
float m_spec[] = {0.99, 0.91, 0.81, 1.0};
float shiny =10; //10, 100

/*** TEXTURES***/
//an array for iamge data
GLubyte* marbles_texture;
GLubyte* crates_texture;
GLubyte* stone_texture;
GLubyte* ironPattern_texture;
GLuint textures[4];
int width1, height1, max1;
int width2 , height2, max2;
int width3, height3, max3;
int width4 , height4, max4;

/* LoadPPM -- loads the specified ppm file, and returns the image data as a GLubyte 
 *  (unsigned byte) array. Also returns the width and height of the image, and the
 *  maximum colour value by way of arguments
 *  usage: GLubyte myImg = LoadPPM("myImg.ppm", &width, &height, &max);
 */
GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;
	
	fd = fopen(file, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n",file); 
		exit(0);
	}
	printf("%s is a PPM file\n", file);
	fscanf(fd, "%c",&c);
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	img = (GLubyte*)malloc(3*sizeof(GLuint)*nm);


	s=255.0/k;


	for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red*s;
		img[3*nm-3*i-2]=green*s;
		img[3*nm-3*i-1]=blue*s;
	}

	*width = n;
	*height = m;
	*max = k;

	return img;
}

int getID(){
	return nodeID++;
}

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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	//sglutSolidSphere(10,50,50);
	glBegin(GL_QUADS);
		//floor

		glColor3f(1,0,0);
		glNormal3f(0,1,0);
		glVertex3f(0,0,0);
		glNormal3f(0,1,0);
		glVertex3f(roomSize,0,0);
		glNormal3f(0,1,0);
		glVertex3f(roomSize,0,roomSize);
		glNormal3f(0,1,0);
		glVertex3f(0,0,roomSize);

		/*glColor3f(1,0,0);
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
		glVertex3f(0,0,0);*/
	glEnd();
	glPopMatrix();

}

void insertObject(NodeType type){
	sceneGraph->toRoot();


	Material defualtMat = Material(m_amb, m_dif, m_spec,shiny);
	Material gold (m_amb2, m_dif2, m_spec2, shiny2);

	point3D origin (0,0,0);
	point3D scaleOrigin(1,1,1);

	//insert group node as the root
	NodeGroup *group = new NodeGroup();
	sceneGraph->insertNode(group);
	sceneGraph->toChild(nextChild++);

	int groupID = sceneGraph->getCurrentNodeID();
	//translate node
	NodeTransformation *originTranslate = new NodeTransformation(translate,origin);
	sceneGraph->insertNode(originTranslate);
	sceneGraph->toChild(0);

	//rotation node
	NodeTransformation *originRotate = new NodeTransformation(rotate,origin);
	sceneGraph->insertNode(originRotate);
	sceneGraph->toChild(0);

	//scale node
	NodeTransformation *originScale = new NodeTransformation(scale,scaleOrigin);
	sceneGraph->insertNode(originScale);
	sceneGraph->toChild(0);

	//material node
	MaterialNode *material = new MaterialNode(defualtMat);
	sceneGraph->insertNode(material);
	sceneGraph->toChild(0);
	printf("Inside Insert Object %f %f %f \n",material->material.amb.x,material->material.amb.y, material->material.amb.z );

	TextureNode *texture = new TextureNode(textures[0], type);
	sceneGraph->insertNode(texture);
	sceneGraph->toChild(0);

	//actual shape object
	NodeShape *shape = new NodeShape(type);
	sceneGraph->insertNode(shape);

	/*//material node
	MaterialNode *material = new MaterialNode(gold);
	sceneGraph->insertNode(material);*/


	SceneObject* newObject = new SceneObject(groupID,originTranslate,originRotate,originScale,shape, material, texture);
	sceneObjectList->push_back(newObject);
	if(currentObject != NULL){ printf("Inside INSERT Size of object list: %i\n", sceneObjectList->size());}
	
	if (nextChild>1)currentObject->deselect();
	newObject->select();
	currentObject = newObject;
	currentObjectIndex = sceneObjectList->size()-1;

		/*sceneGraph.toParent();
		NodeShape s (sphere);
		sceneGraph.insertNode(s);	*/
}

void deleteObject(int id){
	//if(currentObject != NULL){
	sceneGraph->deleteNode(id);
	int index = -1;
	for (int i = 0; i < sceneObjectList->size(); ++i)
	{
		if(sceneObjectList->at(i)->id == id){
			index = i;
			break;
		}
	}

	if(sceneObjectList->size()-1 > 0){
		sceneObjectList->erase(sceneObjectList->begin()+index);
		currentObject = sceneObjectList->at(sceneObjectList->size()-1);
		currentObject->shape->currentlySelected = true;
	
		nextChild--;
	}else if (sceneObjectList->size()-1==0){
		currentObject =NULL;
		nextChild = 0; 
	}
	//}
}

//OpenGL keyboard function that handles keyboard events
void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'Q':
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
			if(light0_on == true && light1_on == true){
				light1_on = false;
				glDisable(GL_LIGHT1);
			}else if (light0_on == true && light1_on == false){
				light0_on = false ;
				glDisable(GL_LIGHT0);
			} else if (light0_on == false && light1_on == false){
				light1_on = true;
				light0_on = true;
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
			}
			break;

		//toggle drawing terrain with quads or traingles
		case 'y':{
			printf("Inserting a sphere\n");
			insertObject(sphere);
			break;
		}
		case 'u':{
			printf("Inserting a torus\n");	
			insertObject(torus);
			break;
		}
		//temporary delete object
		case 'i':{
			printf("Delete Sphere\n");
			if(currentObject != NULL){
				deleteObject(currentObject->id);
			}
			break;	
		}
		//temporary delete object
		case 'o':{
			printf("Insert Cube\n");
			insertObject(cube);
			break;	
		}
			//temporary delete object
		case 'n':{
			printf("Insert Cube\n");
			insertObject(teapot);
			break;	
		}
		case ',':{
			printf("Insert Cone\n");
			insertObject(cone);
			break;	
		}
		//translate currently selected object along xz plane
		case 'w':{
			if(currentObject != NULL){
				point3D p1 (0,0,-1);
				currentObject->translateFunc(p1);
			}
			break;
		}
		case 'a':{
			if(currentObject != NULL){
				point3D p1 (-1,0,0);
				currentObject->translateFunc(p1);
			}
			break;
		}
		case 's':{
			if(currentObject != NULL){
				point3D p1 (0,0,1);
				currentObject->translateFunc(p1);
			}
			break;
		}			
		case 'd':{
			if(currentObject != NULL){
				point3D p1 (1,0,0);
				currentObject->translateFunc(p1);
			}
			break;
		}
		//translate the currently selected object along the y axis
		case 'e':{
			if(currentObject != NULL){
				point3D p1 (0,1,0);
				currentObject->translateFunc(p1);
			}
			break;
		}
		case 'q':{
			if(currentObject != NULL){
				point3D p1 (0,-1,0);
				currentObject->translateFunc(p1);
			}
			break;
		}
		//rotate about the x axis
		case 'x':{
			if(rotationMode == 0){
				point3D p1 (1,0,0);
				currentObject->rotateFunc(p1);
			}else if (rotationMode == 1){
				point3D p1 (0,1,0);
				currentObject->rotateFunc(p1);
			}else{
				point3D p1 (0,0,1);
				currentObject->rotateFunc(p1);
			}
			break;
		}
		case 'z':{
			if(rotationMode == 0){
				point3D p1 (-1,0,0);
				currentObject->rotateFunc(p1);
			}else if (rotationMode == 1){
				point3D p1 (0,-1,0);
				currentObject->rotateFunc(p1);
			}else{
				point3D p1 (0,0,-1);
				currentObject->rotateFunc(p1);
			}
			break;
		}
		//modify object rotation mode
		case 'c':
		{
			if (rotationMode == 0){
				printf("Rotate about the x axis\n");
				rotationMode = 1;
			}else if (rotationMode == 1){
				printf("Rotate about the y axis\n");
				rotationMode = 2;
			}else if (rotationMode == 2){
				printf("Rotate about the z axis\n");
				rotationMode = 0;
			}
			break;
		}
		//modify object material
		case '1':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setEmerald();
			}
			break;
		}
		case '2':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setRuby();
			}
			break;
		}
		case '3':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setYellowRubber();
			}
			break;
		}
		case '4':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setCyanPlastic();
			}
			break;
		}
		case '5':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setChrome();
			}
			break;
		}
		case '0':
		{
			if(currentObject != NULL){
					currentObject->material_id = 1;
					currentObject->material->material.setReset();
			}
			break;
		}
		case '6':
		{
			if(currentObject != NULL){
					//currentObject->material_id = 1;
					//glBindTexture(GL_TEXTURE_2D, textures[0]);
					currentObject->texture->texture = textures[0];
			}
			break;
		}
		case '7':
		{
			if(currentObject != NULL){
					//currentObject->material_id = 1;
					//glBindTexture(GL_TEXTURE_2D, textures[1]);
					currentObject->texture->texture = textures[1];
			}
			break;
		}
		case '8':
		{
			if(currentObject != NULL){
					//currentObject->material_id = 1;
					//glBindTexture(GL_TEXTURE_2D, textures[1]);
					currentObject->texture->texture = textures[2];
			}
			break;
		}
		case '9':
		{
			if(currentObject != NULL){
					//currentObject->material_id = 1;
					//glBindTexture(GL_TEXTURE_2D, textures[1]);
					currentObject->texture->texture = textures[3];
			}
			break;
		}
		



		/*//movecamera taget
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
		*/
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

void printCurrentNode(){
	//currentObject->id
	if(currentObject != NULL){ printf("Size of object list: %i\n", sceneObjectList->size());
	}else{printf("List is Empty\n");}
}


void drawLightSources(){
	glEnable(GL_DEPTH_TEST);	//enable the depth test and enable lights
	glEnable(GL_LIGHTING);		//enable lighting

	glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny2);

		glLoadIdentity();
		if(light0_on == true){
		glEnable(GL_LIGHT0);		//turn on light bulb 0	
			glLightfv(GL_LIGHT0, GL_POSITION, light1_Pos);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
			glLightfv(GL_LIGHT0, GL_SPECULAR, spc0);

			glPushMatrix();
				glLoadIdentity();
				glTranslatef(light0_Pos[0],light0_Pos[1],light0_Pos[2]);
				glutSolidSphere(1,50,50);
			glPopMatrix();
		}

		if(light1_on == true){
			glEnable(GL_LIGHT1);		//turn on light bulb 1
			glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, dif1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
			glLightfv(GL_LIGHT1, GL_SPECULAR, spc1);

			glPushMatrix();
				glLoadIdentity();
				glTranslatef(light1_Pos[0], light1_Pos[1], light1_Pos[2]);
				glutSolidSphere(1,50,50);
			glPopMatrix();
		}

	glPopMatrix();

}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	//float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    /************************************************************************
     
                                    CAMERA SET UP
     
     ************************************************************************/
	
	gluLookAt(camPos[0], camPos[1], camPos[2], 
			camTarget[0], camTarget[1], camTarget[2], 
			camUp[0], camUp[1], camUp[2]); 


	drawBackGround();
	sceneGraph->draw();
	drawLightSources();

	glutSolidTeapot(1);

	printCurrentNode();
	glutSwapBuffers();
}

void initTexture(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(0, 0);

	//add texture code here!

	marbles_texture = LoadPPM("marble.ppm", &width1, &height1, &max1);
	crates_texture = LoadPPM("crates_256.ppm", &width2, &height2, &max2);
	stone_texture = LoadPPM("stone_256.ppm", &width3, &height3, &max3);
	ironPattern_texture = LoadPPM("ironPattern_256.ppm", &width4, &height4, &max4);
	glEnable(GL_TEXTURE_2D); 

	glGenTextures(4, textures); 
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB,GL_UNSIGNED_BYTE, marbles_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glBindTexture(GL_TEXTURE_2D, textures[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB,GL_UNSIGNED_BYTE, crates_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glBindTexture(GL_TEXTURE_2D, textures[2]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB,GL_UNSIGNED_BYTE, stone_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glBindTexture(GL_TEXTURE_2D, textures[3]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB,GL_UNSIGNED_BYTE, ironPattern_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glDisable(GL_TEXTURE_2D);
}

//initilize height map,camera, lighting, shading variables
void init(void)
{
	//glClearColor(0, 0, 0, 0);
	//glColor3f(1, 1, 1);
    
    printInstruction();
    glShadeModel(GL_SMOOTH);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45,1,1,700);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);	//enable the depth test and enable lights
    drawLightSources();
    sceneGraph = new SceneGraph();

    initTexture();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT

	//main window set up
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("3D Modeller");	//creates the window

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
