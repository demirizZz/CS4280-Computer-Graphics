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
	Group Assignment 3 "Circles Galore"
	Dr. Rague
	Due: 10/16/12
	Version: 
------------------------------------------------------------------------

------------------------------------------------------------------------
*/


/*-------------------------------------------------------------------------
Change Control Log
--------------------------------------------------------------------------
	Editor: Logan Green
	Date: 10/5/2012
	Version: 1.0
	Details: I set up the system for drawing the initial triangle and
			 vertices.
--------------------------------------------------------------------------
	Editor: Lance Ure
	Date: 10/15/2012
	Version 1.1
	Details: Added the point pick functionality
*/


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
//Structure that holds 3 vertices used to calculate circles
struct Points3
{
	Point2 p1;
	Point2 p2;
	Point2 p3;
};

//Global Items
Canvas cvs(600, 600, "Circles Galore");
Points3 pts;
Point2 a;
Point2 b;
Point2 c;
Point2 exCenter;
Point2 inCenter;
Point2 nineCenter;
int exRad;
int inRad;
int nineRad;
int wid;
int hei;
//----------------------------------------------------------------------------------------------


//------------------------------------Methods------------------------------------------------
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);  //Used to get the three mouse clicks from the user.
void drawPoint(float x, float y);  //used to draw individual points
void drawTriangle(Points3 pts);  //Used to draw the triangle
Point2 calcCenter(Points3 pt, Point2 i, Point2 j, Point2 k);  //Finds the center of a circle, given three vertices
void myReshape(GLsizei w, GLsizei h);
void drawCircle(float x, float y, float r, int segments); 
float radCirc(Point2 i, Point2 j, Point2 k);
Point2 subtactPoints(Point2 A, Point2 B);
Point2 calcCenterInCirc(Points3 pts);
Point2 calcNineCirc(Points3 pt);
void mousemove(int x, int y);
//----------------------------------------------------------------------------------------------

//Display Method
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);

	if(pts.p1.getX() != 0 || pts.p2.getX() != 0 || pts.p3.getX() != 0) //Reset Struct and set first
		{	a = subtactPoints(pts.p1, pts.p2);
			b = subtactPoints(pts.p2, pts.p3);
			c = subtactPoints(pts.p3, pts.p1);	
			drawPoint(pts.p1.getX(), pts.p1.getY());
			drawPoint(pts.p2.getX(), pts.p2.getY());
			drawPoint(pts.p3.getX(), pts.p3.getY());
			drawTriangle(pts);
			exCenter = calcCenter(pts, a, b, c);
			exRad = radCirc(a, b, c);
			glColor3f(1.0, 1.0, 0.0);
			drawCircle(exCenter.getX(), exCenter.getY(), exRad, 1000);
			inCenter = calcCenterInCirc(pts);
			glColor3f(0.0, 1.0, 0.0);
			drawCircle(inCenter.getX(), inCenter.getY(), inRad, 1000);
			nineCenter = calcNineCirc(pts);
			glColor3f(0.0, 1.0, 1.0);
			drawCircle(nineCenter.getX(), nineCenter.getY(), nineRad, 1000);
		}

}

//Main Driving Program---------------------------------------------------------------
int main ()
{
	//Set up window
	cvs.setColor(1.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();	
}


void myReshape(GLsizei w, GLsizei h) 
{ wid = w; //Change Global variable to adjust width size 
hei = h; //Change Global variable to adjust height size 
cvs.setViewport(0, w, 0, h);
}

int mstate = 0;
int modx = 0;
int mody = 0;
void mouse(int button, int state, int x, int y)
{
	y = hei - y;

	//Place vertices into Points3 struct
	
	
	if ((state == GLUT_UP))
	{
	
		if((button == GLUT_LEFT_BUTTON))
		{
			if(pts.p1.getX() == 0 && pts.p1.getY() == 0)  //Set first
			{
				pts.p1.set(x, y);
				drawPoint(x, y);
			}
			else if(pts.p2.getX() == 0 && pts.p2.getY() == 0)  //Set Second
			{
				pts.p2.set(x, y);
				drawPoint(x, y);
			}
			else if(pts.p3.getX() == 0 && pts.p3.getY() == 0)  //Set third
			{
				pts.p3.set(x, y);
				drawPoint(x, y);
				glutPostRedisplay();
			}
		}
	}

	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		
		if (mstate == 0)
		{
				int d1, d2, d3;
		
				d1 = sqrt(pow(pts.p1.getX() - x,2)+ pow(pts.p1.getY() - (y+hei),2));
				d2 = sqrt(pow(pts.p2.getX() - x,2)+ pow(pts.p2.getY() - (y+hei),2));
				d3 = sqrt(pow(pts.p3.getX() - x,2)+ pow(pts.p3.getY() - (y+hei),2));
				
				if (d1 > d2 && d1 > d3)
				{
					mstate = 1;
					
				}
				if (d2 > d3 && d2 > d1)
				{
					mstate = 2;
					
				}
				if (d3 > d1 && d3 > d2)
				{
					mstate = 3;
					
				}
				
		}
				
	
		
		
		
	}
	else
	{
		
		mstate = 0;
		modx = 0;
		mody = 0;
	}
	
	if (state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
	{
	glutPostRedisplay();
	}
	
}

void drawPoint(float x, float y)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();

	glFlush();
}

void drawTriangle(Points3 pts)
{
	glColor3f(1.0, 0.0, 0.0);
	cvs.moveTo(pts.p1);
	cvs.lineTo(pts.p2);
	cvs.lineTo(pts.p3);
	cvs.lineTo(pts.p1);
}

Point2 subtactPoints(Point2 A, Point2 B)
{
	int x = B.getX() - A.getX();
	int y = B.getY() - A.getY();
	Point2 ret;
	ret.set(x,y);
	return ret;
}

Point2 getNormal(Point2 A)
{
	Point2 ret;
	ret.set(-A.getY(), A.getX());
	return ret;
}

float dotProduct(Point2 A, Point2 B)
{
	Point2 ret;
	ret.set((A.getX()*B.getX()),(A.getY()*B.getY()));
	int r = ret.getX() + ret.getY();
	return r;
}

Point2 scalePoint(float A, Point2 B)
{
	Point2 ret;
	ret.set(A*B.getX(), A*B.getY());
	return ret;
}

Point2 addPoints(Point2 A, Point2 B)
{
	int x = B.getX() + A.getX();
	int y = B.getY() + A.getY();
	Point2 ret;
	ret.set(x,y);
	return ret;
}

float magnitude(Point2 A)
{
	return sqrt(pow(A.getX(),2) + pow(A.getY(),2));
}

float radCirc(Point2 i, Point2 j, Point2 k)
{
	return (magnitude(i)/2)*sqrt(pow((dotProduct(j,k)/dotProduct(getNormal(i),k)),2) + 1);
}

Points3 findMidPoints(Points3 pt)
{
	Points3 mid;
	mid.p1.set(((pt.p1.getX() + pt.p2.getX())/2), ((pt.p1.getY() + pt.p2.getY())/2));
	mid.p2.set(((pt.p2.getX() + pt.p3.getX())/2), ((pt.p2.getY() + pt.p3.getY())/2));
	mid.p3.set(((pt.p1.getX() + pt.p3.getX())/2), ((pt.p1.getY() + pt.p3.getY())/2));
	return mid;
}

void drawCircle(float x, float y, float r, int segments) 
{ 
	float xi = x;
	float yi = y;

	double angle = 2*3.1415/segments;  
    glBegin(GL_POLYGON);  
     {  
         for (int i=1; i<=segments; i++)  
         {  
			 xi= x + r*cos(i * angle);  

             yi= y + r*sin(i * angle);     

				 
                 cvs.lineTo(xi, yi);  
             
         }  
     }  
     glEnd();  
} 


//Will find the center vertex of a circle given three points
Point2 calcCenter(Points3 pt, Point2 i, Point2 j, Point2 k)
{
	Point2 center;
	center = addPoints(pt.p1, scalePoint(0.5, addPoints(i,scalePoint((dotProduct(j,k)/dotProduct(getNormal(i),k)),getNormal(i)))));
	return center;
}

Point2 calcCenterInCirc(Points3 pt)
{
	Point2 center;
	int La = ((magnitude(a)+magnitude(c)-magnitude(b))/2);
	int Lb = ((magnitude(a)+magnitude(b)-magnitude(c))/2);

	Points3 InCirc;

	InCirc.p1 = addPoints(pt.p1, scalePoint(La, scalePoint((1/magnitude(a)),a)));
	InCirc.p2 = addPoints(pt.p2, scalePoint(Lb, scalePoint((1/magnitude(b)),b)));
	InCirc.p3 = subtactPoints(scalePoint(La, scalePoint((1/magnitude(c)),c)), pt.p1);

	Point2 r = subtactPoints(InCirc.p1, InCirc.p2);
	Point2 s = subtactPoints(InCirc.p2, InCirc.p3);
	Point2 t = subtactPoints(InCirc.p3, InCirc.p1);

	center = calcCenter(InCirc, r, s, t);

	inRad = radCirc(r, s, t);

	return center;
}

Point2 calcNineCirc(Points3 pt)
{
	Point2 center;
	
	Points3 mid = findMidPoints(pt);

	Point2 r = subtactPoints(mid.p1, mid.p2);
	Point2 s = subtactPoints(mid.p2, mid.p3);
	Point2 t = subtactPoints(mid.p3, mid.p1);

	center = calcCenter(mid, r, s, t);

	//drawPoint(center.getX(), center.getY());

	nineRad = radCirc(r, s, t);

	return center;
}

void mousemove(int x, int y)
{
y = hei - y;
	switch (mstate)
	{
		
		case 1:
			pts.p1.set(x,y);
			drawPoint(x,y);
			
		break;
		
		case 2:
			pts.p2.set(x,y);
			drawPoint(x,y);
			
		break;
		
		case 3:
			pts.p3.set(x,y);
			drawPoint(x,y);
			
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'r':
	case 'R':
		pts.p1.set(0,0);
		pts.p2.set(0,0);
		pts.p3.set(0,0);
		
		glutPostRedisplay();
		break;

	}

}
