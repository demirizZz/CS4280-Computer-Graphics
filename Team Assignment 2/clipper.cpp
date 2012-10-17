/*
-----------------------------------------------------------------------
	Learning Team E
	Members:
		Lance Ure
		Logan Green
		Benjamin Strickler
		Aaron Copeland
		Troy Thompson

	CS 4280 - 11:30 pm
	Group Assignment 2
	Dr. Rague
	Due: 09/27/12
	Version: 
------------------------------------------------------------------------

------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------
Change Control Log
--------------------------------------------------------------------------
	Team Member: Lance Ure
	Version: 0.1
	Date: 09/27/12
	Setup structures and data types for the program as well as the point
	location assigner

	Team Member: Logan Green
	Version: 0.2
	Date: 09/27/12
	-Redefined world window to be from (-100, -100) to (100, 100)
	-Setup canvas windows and viewports
	-Restructured bitmapping (the hex version I couldn't figure out so I 
			substituted it with the book's example)
	-Defined the clipping algorithm and trivial Accept/Reject methods

---------------------------------------------------------------------------
*/

/*--------------------------------To Do------------------------------------
	@ Create a method that randomly generates Vertex objects with -200<x<200
		and -200<y<200 and places them in our arrays startPoints[POINT_ARRAY_SIZE]
		and endPoints[POINT_ARRAY_SIZE]
	@ Create a method that tests each corresponding line segment and 
		calls the appropriate draw function (eg: trivialAccept(), 
		trivialReject(), clipLine()
	@ Any other requirements needed and any other features we want to make
		this more awesome.
-------------------------------------------------------------------------*/

#include <iomanip>
#include<windows.h>
#include<gl/Gl.h>
#include<gl/glut.h>
#include<cmath>
#include<iostream>
#include<fstream>
#include "Canvas.h"
using namespace std;

//---------------------------------------Global Variables--------------------------------------
//global canvas object
Canvas cvs(600, 600, "Clipping");

// How many individual start and end points
// DETERMINES HOW MANY LINE SEGMENTS WE WANT
#define	POINT_ARRAY_SIZE 3

// the world window discribed as a rectangle. from canvas.h
RealRect worldWindow(-100.0f, 100.0f, -100.0f, 100.0f);

//Structure that holds a vertex location and bit set location
struct Vertex
{
	Point2 point;

	// 00001000 = left, 00000100 = top, 0000010 = right, 00000001 = bottom, all 0's for middle
	char screenLoc; 
};

// the point arrays to be drawn
Vertex startPoints[POINT_ARRAY_SIZE];
Vertex endPoints[POINT_ARRAY_SIZE];
//----------------------------------------------------------------------------------------------


//------------------------------------Prototypes------------------------------------------------

// assign where the points are on the screen that are in our point arrays
// based on the definition described in the Vertex struct
void computePointsLocation();

void clipLine(Vertex& p1, Vertex& p2);      //Draws the line if it has points that lie outside of the world window
void trivialAccept(Vertex& p1, Vertex& p2); //Draws the line segment inside the world window
void trivialReject(Vertex& p1, Vertex& p2); //Draws the line segment outside the world window


//----------------------------------------------------------------------------------------------
const double pi = 3.14159265;
double theta = 0.0;

//Display Methos
void display(void)
{
	cvs.clearScreen();
	cvs.setWindow(-200.0, 200.0, -200.0, 200.0);
	cvs.setViewport(0, 600, 0, 600);	

//TODO Initialize Vertecies and invoke the drawline methods HERE
	
	//Just to show the example lines
	clipLine(startPoints[0], endPoints[0]);
	clipLine(startPoints[1], endPoints[1]);
	clipLine(startPoints[2], endPoints[2]);





	cvs.setColor(0.0, 0.0, 0.0);
	//Draw "World Window"
	worldWindow.draw();

	glFlush();
}

//Receives two Vertex objects as references and draws the correspoding bound and unbound line segments
void clipLine(Vertex& p1_Orig, Vertex& p2_Orig)
{
	Vertex p1, p2;

	p1 = p1_Orig;
	p2 = p2_Orig;

	float delx, dely;

	//Check first Point
	{
		delx = p2.point.getX() - p1.point.getX();
		dely = p2.point.getY() - p1.point.getY();

		float tempX, tempY;

		//If point is on the left
		if(p1.screenLoc & 8)
		{
			tempX = p1.point.getX();
			tempY = p1.point.getY();

			p1.point.set( worldWindow.getL(), tempY + (worldWindow.getL() - tempX) * dely/delx);

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p1, v1);
		}
		//If point is on the right		
		else if(p1.screenLoc & 2)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p1.point.getX();
			tempY = p1.point.getY();

			p1.point.set( worldWindow.getR(), tempY + (worldWindow.getR() - tempX) * dely/delx);

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p1, v1);
		}
		//If point is below
		else if(p1.screenLoc & 1)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p1.point.getX();
			tempY = p1.point.getY();

			p1.point.set(tempX + (worldWindow.getB() - tempY) * delx/dely, worldWindow.getB());

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p1, v1);
		}
		//If point is above
		else if(p1.screenLoc & 4)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p1.point.getX();
			tempY = p1.point.getY();

			p1.point.set(tempX + (worldWindow.getT() - tempY) * delx/dely, worldWindow.getT());

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p1, v1);
		}
	}//end Check First Point

	//Check Second Point
	{
		delx = p2.point.getX() - p1.point.getX();
		dely = p2.point.getY() - p1.point.getY();

		float tempX, tempY;

		//If point is on the left
		if(p2.screenLoc & 8)
		{
			tempX = p2.point.getX();
			tempY = p2.point.getY();

			p2.point.set( worldWindow.getL(), tempY + (worldWindow.getL() - tempX) * dely/delx);

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p2, v1);
		}
		//If point is on the right		
		else if(p2.screenLoc & 2)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p2.point.getX();
			tempY = p2.point.getY();

			p2.point.set( worldWindow.getR(), tempY + (worldWindow.getR() - tempX) * dely/delx);

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p2, v1);
		}
		//If point is below
		else if(p2.screenLoc & 1)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p2.point.getX();
			tempY = p2.point.getY();

			p2.point.set(tempX + (worldWindow.getB() - tempY) * delx/dely, worldWindow.getB());

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p2, v1);
		}
		//If point is above
		else if(p2.screenLoc & 4)
		{
			cvs.setColor(0.0,1.0,1.0);
			tempX = p2.point.getX();
			tempY = p2.point.getY();

			p2.point.set(tempX + (worldWindow.getT() - tempY) * delx/dely, worldWindow.getT());

			Vertex v1;
			v1.point.set(tempX, tempY);
			trivialReject(p2, v1);
		}
	}//end Check Second Point

	trivialAccept(p1, p2); //draws what is inside the "World Window"
}

//Sets the bitmap
void computePointsLocation()
{
	
	for (int i = 0; i < POINT_ARRAY_SIZE; i++)
	{
		// for startPoints
		startPoints[i].screenLoc = 0;

		if (startPoints[i].point.getX() < worldWindow.getL()) // left side
		{
			startPoints[i].screenLoc |= 8;
		}
		else if (startPoints[i].point.getX() > worldWindow.getR()) // right side
		{
			startPoints[i].screenLoc |= 2;
		}
		else{}

		if (startPoints[i].point.getY() < worldWindow.getB()) //bottom
		{
			startPoints[i].screenLoc |= 1;
		}
		else if (startPoints[i].point.getY() > worldWindow.getT()) // top
		{
			startPoints[i].screenLoc |= 4;
		}
		else{}
		

		// for endPoints
		endPoints[i].screenLoc = 0;
		
		if (endPoints[i].point.getX() < worldWindow.getL())
		{
			endPoints[i].screenLoc |= 8;
		}
		else if (endPoints[i].point.getX() > worldWindow.getR())
		{
			endPoints[i].screenLoc |= 2;
		}
		else{}
		


		if (endPoints[i].point.getY() < worldWindow.getB())
		{
			endPoints[i].screenLoc |= 1;
		}
		else if (endPoints[i].point.getY() > worldWindow.getT())
		{
			endPoints[i].screenLoc |= 4;
		}
		else{}	
	} // end for loop
}

void trivialAccept(Vertex& p1, Vertex& p2)
{
	cvs.setColor(0.0,1.0,1.0);
	cvs.moveTo(p1.point);
	cvs.lineTo(p2.point);
}

void trivialReject(Vertex& p1, Vertex& p2)
{
	cvs.setColor(1.0,0.0,0.0);
	cvs.moveTo(p1.point);
	cvs.lineTo(p2.point);
}

// for testing
int main ()
{
	//Example of one of the line segments
	startPoints[0].point = Point2(-150, 175);
	endPoints[0].point = Point2(0, -150);

	startPoints[1].point = Point2(150, 90);
	endPoints[1].point = Point2(0, -110);

	startPoints[2].point = Point2(-75, 20);
	endPoints[2].point = Point2(65, 80);

	computePointsLocation();
	//-----------------------------------

	//Set up window
	cvs.setBackgroundColor(1.0, 1.0, 1.0);
	cvs.setColor(1.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();	
}