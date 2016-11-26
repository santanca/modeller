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


//Globals
int mapSize = 300;
float angleX = 0;
float angleY = 0;
bool shadingGouraud = true;
bool lightingOn = true;
bool trianglesOn = true;	//draw terrain with triangles if true, else draw with quads
bool HypsometricColors = false;
bool faultMapOn = false;
int mainWindow;
int secondWindow; 
int globalMaxHeight = 5;
vector<vector<float> > heightMap;

/*wire frame mode 
				= 0 - solid polygons
				= 1 - just the wire frame
				= 2 - both					*/
int wireFrameMode = 0;

/*** CAMERA LOCATION ***/
float camPos[] = {mapSize+(mapSize/3),mapSize/3,mapSize+(mapSize/3)}; 	//where the camera is
float camUp[] = {0,1,0}; 	//up vector of the camera
float camTarget[] = {mapSize/2,0,mapSize/2}; //where the camera is looking at
float camSpeed = 0.1f;

/*** LIGHT0 LOCATION ***/
float light0_Pos[] = {mapSize, 20, mapSize, 1};
/*** LIGHT1 LOCATION ***/
float light1_Pos[] = {20,20,20,1};

/*** SNOWMAN LOCATION & ROTATION***/
float pos[] = {mapSize/2,0,mapSize/2};
float rot[] = {0,0,0};
float headRot[] = {0,0,0};

//find the distance between two points
float distancePoints(int x1,int z1,int x2,int z2){
	return sqrt(pow(x2-x1,2) + pow(z2-z1,2));
}

//Generate terrain height map based on circle algorithm from: http://www.lighthouse3d.com/opengl/terrain/index.php?circles
vector<vector<float> > generateHeightMap(){
	//initialize 2d heigh map
	vector<vector<float> > heightMap;
	heightMap.resize(mapSize);

	for (int i = 0; i < heightMap.size(); ++i)
	{
		heightMap[i].resize(mapSize);
	}

	//initialize heigh values to 0
	for (int x = 0; x < heightMap.size(); ++x)
	{
		for (int z = 0; z < heightMap.size(); ++z)
		{
			heightMap[x][z] = 0.0f;
		}
	}

	
	//generate a random number of hills 
	int number_Of_Hills = rand() % (mapSize*4) + (mapSize*2);
	for (int i = 0; i < number_Of_Hills; ++i)
	{
		int x = rand() % (mapSize-1);	//x position of hill center
		int z = rand() % (mapSize-1);	//z position of hill center
		int terrainCircleSize = rand() % (mapSize/10) + 5;	//radius of the hill
		float disp = rand() % 3 + 1;
		
		//circle algorithm for hill
		//use the circles algorithm to produce height values
		for (int hx = (x-terrainCircleSize); hx< (x+terrainCircleSize); ++hx)
		{
				
				for (int hz = (z-terrainCircleSize); hz < (z+terrainCircleSize); ++hz)
				{

					//check boundary of the hill
					if(hz >= 0 && hz <mapSize && hx >= 0 && hx< mapSize){	
						float distanceFromCenter = distancePoints(x,z,hx,hz);
						float pd = distanceFromCenter * 2.0f / float(terrainCircleSize);
						if (fabs(pd) <= 1.0f){
							float height = float(disp/2 + cos(pd*3.14)*disp/2);
							heightMap.at(hx).at(hz) += height;
						}
					}
				}
		}				
	}

	return heightMap;

}

//Return the maximum height in the height map
float getMaxHeight(vector<vector<float> > myheightMap){
	float maxHeight = 0;
	//iterate through the height map
	for (int i = 0; i < myheightMap.size(); ++i)
	{
		for (int j = 0; j < myheightMap.size(); ++j)
		{
			if(heightMap[i][j] > maxHeight){
				maxHeight = myheightMap[i][j];
			}
		}
	}
	return maxHeight;
}

//Retusn the minimum height in the height map
float getMinHeight(vector<vector<float> > myheightMap){
	float minHeight = getMaxHeight(heightMap);
	//iterate thorugh the height map
	for (int i = 0; i < myheightMap.size(); ++i)
	{
		for (int j = 0; j < myheightMap.size(); ++j)
		{
			if(heightMap[i][j] < minHeight){
				minHeight = myheightMap[i][j];
			}
		}
	}
	return minHeight;
}

//Generate a height map based on the Fault Algorithm on: http://www.lighthouse3d.com/opengl/terrain/index.php?fault
vector<vector<float> > generateFaultHeightMap(){
	//initialize the height map
	vector<vector<float> > heightMap;
	heightMap.resize(mapSize);

	for (int i = 0; i < heightMap.size(); ++i){ heightMap[i].resize(mapSize);}

	//initialze the height values to 0
	for (int x = 0; x < heightMap.size(); ++x)
	{
		for (int z = 0; z < heightMap.size(); ++z)
		{
			heightMap[x][z] = 0.0f;
		}
	}

	
	int number_of_Faults = mapSize*2;	//the number of faults in a given map
	for (int i = 0; i < number_of_Faults; ++i)
	{
		float v = (float)rand();
		float a = sin(v);
		float b = cos(v);
		float d = sqrt(mapSize*mapSize + mapSize*mapSize);
		float c = ((float)rand() / RAND_MAX) * d -d/2.0f;
		float displacement = 1;

		//for each point in the terrain change the height depending on which side of the fault line it is
		for (int x = 0; x < mapSize; ++x){
			for (int z = 0; z < mapSize; ++z){
				if ((a*x) + (b*z) - c > 0){					
					heightMap[x][z] += displacement;
				}else{
					heightMap[x][z] -= displacement;
				}
			}
		}

	}

	//subtract the each height value with the min value
	//this is done to keep the terrain within the view of the camera
	float minHeight = getMinHeight(heightMap);
	for (int x = 0; x < mapSize; ++x)
	{
		for (int z = 0; z < mapSize; ++z)
		{
			heightMap[x][z] -= minHeight;
		}
	}

	return heightMap;
}

//Calculate the normals of the terrain. These noramls are supplied for the lighting effects
vector<vector<vec3D> > calulateNormals(vector<vector<float> > heightMap){
	vector<vector<vec3D> > faceNormals(mapSize,vector<vec3D>(mapSize));
	vector<vector<vec3D> > vertexNormals(mapSize, vector<vec3D>(mapSize)); 

	/*** GET THE FACE NORAMLS ***/
	//iterate through each point
	for (int x = 0; x < mapSize; ++x)
	{
		for (int z = 0; z < mapSize; ++z)
		{
			//check boundary & get the noraml based on the cross product of triangle
			if(z == mapSize-1 && x < mapSize-1){
				point3D p2 (x,heightMap[x][z],z);
				point3D p1 (x,heightMap[x][z-1],z-1);
				point3D p3 (x+1, heightMap[x+1][z],z);

				vec3D u = u.createVector(p1,p2);
				vec3D v = v.createVector(p3,p1);
				vec3D faceNormal = u.getNormal(v);

				faceNormals[x][z] = faceNormal;
			}else if (z==mapSize-1 && x== mapSize-1 ){	
				point3D p2 (x,heightMap[x][z],z);
				point3D p1 (x-1,heightMap[x-1][z-1],z-1);
				point3D p3 (x, heightMap[x][z-1],z-1);

				vec3D u = u.createVector(p1,p2);
				vec3D v = v.createVector(p3,p1);
				vec3D faceNormal = u.getNormal(v);

				faceNormals[x][z] = faceNormal;
			}else if (z < mapSize-1 && x== mapSize-1 ){	
				point3D p2 (x,heightMap[x][z],z);
				point3D p1 (x-1,heightMap[x-1][z-1],z-1);
				point3D p3 (x, heightMap[x][z-1],z-1);

				vec3D u = u.createVector(p1,p2);
				vec3D v = v.createVector(p3,p1);
				vec3D faceNormal = u.getNormal(v);

				faceNormals[x][z] = faceNormal;
			}else{
				point3D p1 (x,heightMap[x][z+1],z+1);
				point3D p2 (x,heightMap[x][z],z);
				point3D p3 (x+1, heightMap[x+1][z],z);

				vec3D u = u.createVector(p1,p2);
				vec3D v = v.createVector(p3,p1);
				vec3D faceNormal = u.getNormal(v);

				faceNormals[x][z] = faceNormal;
			}
		}
	}


	/*** GET THE VERTEX NORMALS***/
	for (int x = 0; x < mapSize; ++x)
	{
		for (int z = 0; z < mapSize; ++z)
		{
			//each vertex normal is based on the average of the face normals surrounding the vertex, unless the vertex is an edge case
			if (x > 0 && x < mapSize-1 && z > 0 && z < mapSize-1){
				vec3D u (0,0,0);
				u = u.add(faceNormals[x][z]);
				u = u.add(faceNormals[x][z+1]);
				u = u.add(faceNormals[x+1][z+1]);
				u = u.add(faceNormals[x+1][z]);
				u = u.add(faceNormals[x+1][z-1]);
				u = u.add(faceNormals[x][z-1]);
				u = u.add(faceNormals[x-1][z-1]);
				u = u.add(faceNormals[x-1][z]);
				u = u.add(faceNormals[x-1][z+1]);
				u = u.normalize();
				vertexNormals[x][z] = u;

			}else{ // if the vertex is on the edge, the vertex normal = face normal
				vertexNormals[x][z] = faceNormals[x][z];
			}
		}
	}

	//supply face normals when flat shading and vertex normals for Gouraud Shading
	if(shadingGouraud == false){
		return faceNormals;
	}else{
		return vertexNormals;
	}
	
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

//draws the wire frame
void drawOnlyWireFrame(){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,1,0);

	float m_amb[] = {0, 1, 0, 1.0};
	float m_dif[] = {0, 1, 0, 1.0};
	float m_spec[] = {0, 1, 0, 1.0};
	float shiny =10; //10, 100

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	glBegin(GL_TRIANGLES);
		//iterate through the height map 
		for(int x =1; x < mapSize-1; ++x)
		{
			for(int z = 1; z < mapSize-1; ++z)
			{
				//first triangle
				glColor3f(0,1,0);
				glVertex3f(x,heightMap[x][z+1],z+1);
				glVertex3f(x,heightMap[x][z],z);
				glVertex3f(x+1,heightMap[x+1][z],z);
				//second triangle
				glVertex3f(x+1,heightMap[x+1][z+1],z+1);
				glVertex3f(x,heightMap[x][z+1],z+1);
				glVertex3f(x+1,heightMap[x+1][z],z);
			}
		}

	glEnd();
}

//Determines the color of a point given its height
vector<float> HypsometricHints(float height){
	vector<float> colors(2);
	if(height < 0.08){
		colors[0] = 20.0f / 100.0f;
		colors[1] = 40.0f / 100.0f;
		colors[2] = 20.0f / 100.0f;
		return colors;
	}else if (height < 0.16){
		colors[0] = 20.0f / 100.0f;
		colors[1] = 60.0f / 100.0f;
		colors[2] = 20.0f / 100.0f;
		return colors;
	}else if(height < 0.24){
		colors[0] = 60.0f / 100.0f;
		colors[1] = 100.0f / 100.0f;
		colors[2] = 20.0f / 100.0f;
		return colors;
	} else if (height < 0.32){
		colors[0] = 153.0f / 100.0f;
		colors[1] = 255.0f / 100.0f;
		colors[2] = 51.0f / 100.0f;
		return colors;
	} else if (height < 0.40){
		colors[0] = 100.0f / 100.0f;
		colors[1] = 60.0f / 100.0f;
		colors[2] = 20.0f / 100.0f;
		return colors;
	}else if (height < 0.48){
		colors[0] = 80.0f / 100.0f;
		colors[1] = 20.0f / 100.0f;
		colors[2] = 0.0f / 100.0f;
		return colors;
	}else if (height < 0.56){
		colors[0] = 50.f / 100.0f;
		colors[1] = 0.0f / 100.0f;
		colors[2] = 0.0f / 100.0f;
		return colors;
	}else if (height < 0.64){
		colors[0] = 20.f / 100.0f;
		colors[1] = 0.0f / 100.0f;
		colors[2] = 0.0f / 100.0f;
		return colors;
	} else{
		colors[0] = 0.5;
		colors[1] = 0.5;
		colors[2] = 0.5;
		return colors;
	}
}

//draw the terrain, using the height map
void drawTerrain(){
	vector<vector<vec3D> > normals = calulateNormals(heightMap);
	
	glColor3f(0,1,0);
	glTranslatef(0.0f,0.0f,0.0f);
	glRotatef(angleX,0,1,0);
	glRotatef(angleY,1,0,0);

	//manage the wire frame mode
	if(wireFrameMode == 0 || wireFrameMode ==2){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}else if (wireFrameMode ==1){
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}

	//manage the lighting
	if(lightingOn == true){
		glEnable(GL_LIGHTING);		//enable lighting
		glEnable(GL_LIGHT0);		//turn on light bulb 0
		glEnable(GL_LIGHT1);		//turn on light bulb 0
		glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
	}else{
		glDisable(GL_LIGHTING);
	}

	float maxHeight = getMaxHeight(heightMap);
	globalMaxHeight = maxHeight;
	//draw triangles or quads
	if(trianglesOn == true){
		glBegin(GL_TRIANGLES);
		//iterate through the height map
		for(int x =1; x < mapSize-1; ++x)
		{
			for(int z = 1; z < mapSize-1; ++z)
			{
				float colors1[3];
				float colors2[3];
				float colors3[3];
				float colors4[3];

				//get the color of each vertex, either gray scale or hypsometric colors
				if (HypsometricColors == true){
					vector<float> myColors1 = HypsometricHints(heightMap[x][z]/maxHeight);
					vector<float> myColors2 = HypsometricHints(heightMap[x+1][z]/maxHeight);
					vector<float> myColors3 = HypsometricHints(heightMap[x+1][z+1]/maxHeight);
					vector<float> myColors4 = HypsometricHints(heightMap[x][z+1]/maxHeight);

					float colors1[3] = {myColors1[0],myColors1[1],myColors1[2]};
					float colors2[3] = {myColors2[0], myColors2[1], myColors2[2]};
					float colors3[3] = {myColors3[0],myColors3[1],myColors3[2]};
					float colors4[3] = {myColors4[0],myColors4[1], myColors4[2]};
				}else{
					//get the color of each vertex
					float color1 = heightMap[x][z]/maxHeight;
					float color2 = heightMap[x+1][z]/maxHeight;
					float color3 = heightMap[x+1][z+1]/maxHeight;
					float color4 = heightMap[x][z+1]/maxHeight;

					float colors1[3] = {color1,color1,color1};
					float colors2[3] = {color2, color2, color2};
					float colors3[3] = {color3,color3,color3};
					float colors4[3] = {color4,color4, color4};
				}
				
				//first triangle
				glColor3fv(colors4);
				glNormal3f(normals[x][z+1].x,normals[x][z+1].y, normals[x][z+1].z );
				glVertex3f(x,heightMap[x][z+1],z+1);

				glColor3fv(colors1);
				glNormal3f(normals[x][z].x,normals[x][z].y, normals[x][z].z );
				glVertex3f(x,heightMap[x][z],z);
				
				glColor3fv(colors2);
				glNormal3f(normals[x+1][z].x,normals[x+1][z].y, normals[x+1][z].z );
				glVertex3f(x+1,heightMap[x+1][z],z);

				//second triangle
				glColor3fv(colors3);
				glNormal3f(normals[x+1][z+1].x,normals[x+1][z+1].y, normals[x+1][z+1].z );
				glVertex3f(x+1,heightMap[x+1][z+1],z+1);
				
				glColor3fv(colors4);
				glNormal3f(normals[x][z+1].x,normals[x][z+1].y, normals[x][z+1].z );
				glVertex3f(x,heightMap[x][z+1],z+1);
				
				glColor3fv(colors2);
				glNormal3f(normals[x+1][z].x,normals[x+1][z].y, normals[x+1][z].z );
				glVertex3f(x+1,heightMap[x+1][z],z);
			}
		}

		glEnd();
	}else{
		glBegin(GL_QUADS);
		//iterate through the height map
		for(int x =1; x < mapSize-1; ++x)
		{
			for(int z = 1; z < mapSize-1; ++z)
			{
				float colors1[3];
				float colors2[3];
				float colors3[3];
				float colors4[3];
				
				//get the color of each vertex, either gray scale or hypsometric colors
				if (HypsometricColors == true){
					vector<float> myColors1 = HypsometricHints(heightMap[x][z]/maxHeight);
					vector<float> myColors2 = HypsometricHints(heightMap[x+1][z]/maxHeight);
					vector<float> myColors3 = HypsometricHints(heightMap[x+1][z+1]/maxHeight);
					vector<float> myColors4 = HypsometricHints(heightMap[x][z+1]/maxHeight);

					float colors1[3] = {myColors1[0],myColors1[1],myColors1[2]};
					float colors2[3] = {myColors2[0], myColors2[1], myColors2[2]};
					float colors3[3] = {myColors3[0],myColors3[1],myColors3[2]};
					float colors4[3] = {myColors4[0],myColors4[1], myColors4[2]};
				}else{
					//get the color of each vertex
					float color1 = heightMap[x][z]/maxHeight;
					float color2 = heightMap[x+1][z]/maxHeight;
					float color3 = heightMap[x+1][z+1]/maxHeight;
					float color4 = heightMap[x][z+1]/maxHeight;

					float colors1[3] = {color1,color1,color1};
					float colors2[3] = {color2, color2, color2};
					float colors3[3] = {color3,color3,color3};
					float colors4[3] = {color4,color4, color4};
				}

				//quad vertices
				glColor3fv(colors4);
				glNormal3f(normals[x][z+1].x,normals[x][z+1].y, normals[x][z+1].z );
				glVertex3f(x,heightMap[x][z+1],z+1);

				glColor3fv(colors1);
				glNormal3f(normals[x][z].x,normals[x][z].y, normals[x][z].z );
				glVertex3f(x,heightMap[x][z],z);
				
				glColor3fv(colors2);
				glNormal3f(normals[x+1][z].x,normals[x+1][z].y, normals[x+1][z].z );
				glVertex3f(x+1,heightMap[x+1][z],z);

				glColor3fv(colors3);
				glNormal3f(normals[x+1][z+1].x,normals[x+1][z+1].y, normals[x+1][z+1].z );
				glVertex3f(x+1,heightMap[x+1][z+1],z+1);

			}
		}

		glEnd();

	}
	
	//draw the wire frame if its in the right mode
	if(wireFrameMode == 2){
			drawOnlyWireFrame();
			resetMaterial();
	}
	


}

//Reset the height map (set all the height values to 0)
vector<vector<float> > resetHeightMap(){
	vector<vector<float> > heightMap(mapSize,vector<float>(mapSize));
	//iterate through the height map
	for (int x = 0; x < mapSize; ++x)
	{
		for (int z = 0; z < mapSize; ++z)
		{
			heightMap[x][z] = 0.0f;
		}
	}
	return heightMap;
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
		
		//generate new random height map
		case 'r':	
			if(faultMapOn == false){
				heightMap = generateHeightMap();
			}else{
				heightMap = generateFaultHeightMap();
			}
			
			break;
		//reset the height map height map, ie. set all the height values to 0
		case 'R':
			heightMap = resetHeightMap();
			break;

		//toggle the wire frame
		case 'w':
			if(wireFrameMode == 0){
				wireFrameMode = 1;
			}else if (wireFrameMode == 1){
				wireFrameMode = 2;
			}else if (wireFrameMode ==2){
				wireFrameMode = 0;
			}
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
			if (mapSize == 300){
				mapSize = 50;
				camPos[0] = 100;
				camPos[1] = 50;
				camPos[2] = 100;
				camTarget[0] = mapSize/2;
				camTarget[2] = mapSize/2;
				camTarget[1] = 0;
			}else{
				mapSize = 300;
				camPos[0] = 400;
				camPos[1] = 100;
				camPos[2] = 400;
				camTarget[0] = mapSize/2;
				camTarget[2] = mapSize/2;
				camTarget[1] = 0;
			}
			//redraw the terrain
			if(faultMapOn == false){
				heightMap = generateHeightMap();
			}else{
				heightMap = generateFaultHeightMap();
			}

			//reshape the secondary 2d window
			glutSetWindow(secondWindow);

			glutReshapeWindow(mapSize,mapSize);
			if(mapSize == 50){
				glScalef(6,6,1);
			}else{
				glScalef(1.0f/6.0f,1.0f/6.0f,1.0f);
			}
			
			//gluOrtho2D(0,mapSize,0,mapSize);
			glutPostRedisplay();
			glutSetWindow(mainWindow);
			
			//reset the camera
			gluLookAt(camPos[0], camPos[1], camPos[2], 
			camTarget[0], camTarget[1], camTarget[2], 
			camUp[0], camUp[1], camUp[2]); 
			
			break;	

		//toggle hypsometric tints
		case 'b':
			if(HypsometricColors == true){
				HypsometricColors = false;
				lightingOn = true;
			}else{
				HypsometricColors = true;
				lightingOn = false;
			}
			break;

		//toggle fault algorithm
		case 'f':
			if(faultMapOn == false){
				faultMapOn = true;
				heightMap = generateFaultHeightMap();
			}else{
				faultMapOn = false;
				heightMap = generateHeightMap();
			}
			
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

		//change the shading to Flat shading
		case 'e':
			if(shadingGouraud == true){
				shadingGouraud = false;
				glShadeModel(GL_FLAT);
			}else{
				shadingGouraud = true;
				glShadeModel(GL_SMOOTH);
			}
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

	//update all the windows
	glutSetWindow(secondWindow);
	glutPostRedisplay();
	glutSetWindow(mainWindow);


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
	printf("\t \t Hello and welcome to my Terrain Modeling program\n");
	printf("----------------------------------By Cesar Santana-----------------------------\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("q or ESCAP----------------> Quit the program\n");
	printf("r ------------------------> Generate a new random height map\n");
	printf("R ------------------------> Reset the height map\n");
	printf("w ------------------------> Toggle the wire frame\n");
	printf("l ------------------------> Toggle the lighting\n");
	printf("t ------------------------> Draw terrain with traingles\n");
	printf("y ------------------------> Draw terrrain with quads\n");
	printf("m ------------------------> Toggle Map size (300x300 or 50x50)\n");
	printf("e ------------------------> Change shading model (Gouraud / Flat)\n");
	printf("Arrow Keys ---------------> Rotate the terrain\n");
	printf("h,j,k,u ------------------> Move Camera Viewing Target (side to side)\n");
	printf("c,v ----------------------> Move Camera Viewing Target (up and down)\n");
	printf("WASD ---------------------> Move light0\n");
	printf("UHJK ---------------------> Move light1\n");
	printf("b ------------------------> Toggle Hypsometric Colors\n");
	printf("f ------------------------> Toggle between Fault and Cricle Terrain Algorithms\n");
	printf("-------------------------------- On 2D Terrain Window --------------------------\n");
	printf("LEFT MOUSE CLICK ---------> Adds hill to the terrain\n");
	printf("RIGHT MOUSE CLICK --------> Adds dent to the terrain\n");
}

//initilize height map,camera, lighting, shading variables
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
    printInstruction();

    //heightMap = generateFaultHeightMap();
    heightMap = generateHeightMap();
    /************************************************************************
     
                            PERSPECTIVE SET UP!
     
     modelview moves the eye and objects, projection is for camera type
     frustum
     
     ************************************************************************/
    glMatrixMode(GL_PROJECTION);
    //glFrustum(-10,10,-10,10,0,100);
	gluPerspective(45, 1, 1, mapSize*2);

	//enable lighting
	glEnable(GL_DEPTH_TEST);	//enable the depth test and enable lights
	glEnable(GL_LIGHTING);		//enable lighting
	//glEnable(GL_LIGHT0);		//turn on light bulb 0
	glEnable(GL_LIGHT1);		//turn on light bulb 1

	//define light properties
	float pos[4] = {mapSize/2, 0, mapSize/2, 1};
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

	
	//define material
	float m_amb[] = {0.1, 0.1, 0.1, 1.0};
	float m_dif[] = {0.5, 0.5, 0.5, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny =10; //10, 100

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	//define smooth (guaruod) shading*/
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

}


//makes a bump or dent on the height map given the x ,z coordinate
void genCircle(int x, int z, bool dent){
	int terrainCircleSize = 10;
	float disp = 2;
	
	//circle algorithm for hill
	//use the circles algorithm to produce height values
	for (int hx = (x-terrainCircleSize); hx< (x+terrainCircleSize); ++hx)
	{
		for (int hz = (z-terrainCircleSize); hz < (z+terrainCircleSize); ++hz)
		{
			//check boundary of the hill
			if(hz >= 0 && hz <mapSize && hx >= 0 && hx< mapSize){	
				float distanceFromCenter = distancePoints(x,z,hx,hz);
				float pd = distanceFromCenter * 2.0f / float(terrainCircleSize);
				if (fabs(pd) <= 1.0f){
					float height = float(disp/2 + cos(pd*3.14)*disp/2);

					//increases/decreases the height depeding on the which button is clicked
					if(dent == false){
						heightMap.at(hx).at(hz) += height;
					}else{
						heightMap.at(hx).at(hz) -= height;
					}
					
				}
			}
		}
	}

}

//inverts the y coordinate on the 2d terrain window
int invert(int y){
	return mapSize - y;
}

//handles the mouse events
void mouse(int btn, int state, int x, int y){
	//create a bump if the left mouse button is pressed
	if(btn == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			genCircle(x,invert(y),false);
		}

	//create a dent if the right button is pressed
	}else if(btn == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN){
			genCircle(x,invert(y),true);
		}
	}

	glutPostRedisplay();

	//update the other window
	glutSetWindow(mainWindow);
	glutPostRedisplay();
	glutSetWindow(secondWindow);

}


//handles the second window display (2D Terrain)
void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	glPointSize(1);

	//draw the height map on the second window
	glBegin(GL_POINTS);	
		//iterate through the height map
		for (int x = 0; x < mapSize; ++x)
		{
			for (int z = 0; z < mapSize; ++z)
			{
				float colors1[3];

				//get the color of each vertex, either gray scale or hypsometric colors
				if (HypsometricColors == true){
					vector<float> myColors1 = HypsometricHints(heightMap[x][z]/globalMaxHeight);
					float colors1[3] = {myColors1[0],myColors1[1],myColors1[2]};

				}else{
					//get the color of each vertex
					float color1 = heightMap[x][z]/globalMaxHeight;
					float colors1[3] = {color1,color1,color1};
				}

				//draw the vertex
				glColor3fv(colors1);
				glVertex2f(x,z);
				
			}
		}
	glEnd();

	//update the other window
	glutSwapBuffers();
	glutSetWindow(mainWindow);
	glutPostRedisplay();
	glutSetWindow(secondWindow);

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


	drawTerrain();
	
	glutSwapBuffers();

	//update the other window
	glutSetWindow(secondWindow);
	glutPostRedisplay();
	glutSetWindow(mainWindow);
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT

	//main window set up
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	mainWindow = glutCreateWindow("Terrain Modeling");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();


	//second window
	glutInitWindowSize(mapSize,mapSize);
	glutInitWindowPosition(200, 200);
	secondWindow =  glutCreateWindow("2D Terrain");

	gluOrtho2D(0,mapSize,0,mapSize);
	glutDisplayFunc(display2);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);


	glutSetWindow(mainWindow);

	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
