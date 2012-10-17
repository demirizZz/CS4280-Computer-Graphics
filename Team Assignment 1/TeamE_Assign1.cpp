/*---------------------------------------------------------------------------------------------------------
*	Learning Team E
*	Members:
*		Aaron Copeland
*		Ben Strickler
*		Logan Green
*		Troy Thompson
*		Lance Ure
*	CS 4280	TW 11:30am
*	Dr. Rague
*	Due: 09/13/2012
*	Version: 1.1
*----------------------------------------------------------------------------------------------------------
*	This program creates an OpenGL program that displays a series of golden triangles in a screen window of 600 
*	pixels wide by 400 pixels high. The program calculates and displays the largest golden rectangle that will 
*	fit in the previous rectangle drawn until the size of the rectangle is one pixel high.
*---------------------------------------------------------------------------------------------------------
*/

/*---------------------------------------------------------------------------------------------------------
*	Change Control Section
*----------------------------------------------------------------------------------------------------------
*/

/*
*	Version 1.00
*	Aaron Copeland
*	Date: 09/11/2012
*	Created the program that uses regression to draw multiple rectangles
*	each having the golden ratio.
*/

/*
*	Version 1.01
*	Ben Strickler
*	Date: 09/11/2012
*	Added color choice in goldenRect function to fix a bug with
*	the first rectangles color changing.
*	Added Aspect ratio control to prevent distortion of the rectangles
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

// struct to hold the x and y coords for the starting points 
struct GLintPoint
{
	GLint x, y;
};

int wid = 600; //Global variable for Width
int hei = 400; //Global variable for Height

// function declarations
void init();
void display();
void myReshape(GLsizei w, GLsizei h);
void goldenRect(int width, int height);
void goldenVRightRect(GLintPoint start, int height, int width);
void goldenVLeftRect(GLintPoint start, int height, int width);
void goldenHTopRect(GLintPoint start, int height, int width);
void goldenHBottomRect(GLintPoint start, int height, int width);

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Group E: Team Assignment 1 Golden Ratio");	

	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	init();
	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	/* set the background (clearing) color to  RGBA(0,0,0,0) -- black */
	glColor3f(1.0, 1.0, 0.0);			/* Yellow */
	glMatrixMode(GL_PROJECTION);		/* Initialize the matrix state */	
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 400.0);	
}

void myReshape(GLsizei w, GLsizei h)
{
	wid = w; //Change Global variable to adjust width size
	hei = h; //Change Global variable to adjust height size
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, wid, 0.0, hei);
}

void display()
{		
	glClear(GL_COLOR_BUFFER_BIT);
	goldenRect(wid, hei);		// passes in the size of the window to our goldenRect function to draw the initial goldenRect
	glFlush();		
}

// draws the first golden rectangle
void goldenRect(int width, int height)
{
	int rectHeight = width / 1.618033989;
	int rectWidth = rectHeight * 1.618033989;
	int xOffset = (width - rectWidth) / 2;
	int yOffset = (height - rectHeight) / 2;	// does the math to center the first rectangle in the window
	
	glColor3f(1.0, 1.0, 0.0);
	glRecti(xOffset, yOffset, (width-xOffset), (height - yOffset));
	
	// calculates the endPoint so we can pass it to the next function
	GLintPoint endPoint;
	endPoint.x = width-xOffset;
	endPoint.y = height-yOffset;	

	goldenVRightRect(endPoint, rectHeight, rectWidth);
}

// draws the right vertical rectangles
void goldenVRightRect(GLintPoint start, int height, int width)
{
	int rectHeight = height / 1.618033989;
	int rectWidth = height;

	if(rectHeight > 1) // regresses down till our rectangle height is less than 1 pixel
	{
		glColor3f(1.0, 0.0, 0.0); // Red
		glRecti(start.x - rectHeight, start.y - rectWidth, start.x, start.y);
		
		// calculates the endPoint so we can pass it to the next function
		GLintPoint endPoint;
		endPoint.x = start.x - rectHeight;
		endPoint.y = start.y - rectWidth;	

		goldenHBottomRect(endPoint, rectHeight, rectWidth);
	}
}

// draws the left vertical rectangles
void goldenVLeftRect(GLintPoint start, int height, int width)
{
	int rectHeight = height / 1.618033989;
	int rectWidth = height;

	if(rectHeight > 1) // regresses down till our rectangle height is less than 1 pixel
	{
		glColor3f(0.0, 0.0, 1.0); // Green
		glRecti(start.x, start.y - rectWidth, start.x + rectHeight, start.y);
		
		// calculates the endPoint so we can pass it to the next function
		GLintPoint endPoint;
		endPoint.x = start.x + rectHeight;
		endPoint.y = start.y;			

		goldenHTopRect(endPoint, rectHeight, rectWidth);
	}
}

// draws the top horizontal rectangles
void goldenHTopRect(GLintPoint start, int height, int width)
{
	int rectHeight = height / 1.618033989;
	int rectWidth = height;

	if(rectHeight > 1)	// regresses down till our rectangle height is less than 1 pixel
	{		
		glColor3f(0.0, 1.0, 0.0); // Blue
		glRecti(start.x - rectWidth, start.y - rectHeight, start.x, start.y);
		
		// calculates the endPoint so we can pass it to the next function
		GLintPoint endPoint;
		endPoint.x = start.x;
		endPoint.y = start.y;

		goldenVRightRect(endPoint, rectHeight, rectWidth);
	}
}

// draws the bottom horizontal rectangles
void goldenHBottomRect(GLintPoint start, int height, int width)
{
	int rectHeight = height / 1.618033989;
	int rectWidth = height;

	if(rectHeight > 1)	// regresses down till our rectangle height is less than 1 pixel
	{		
		glColor3f(1.0, 1.0, 0.0); // Yellow
		glRecti(start.x, start.y, start.x + rectWidth, start.y + rectHeight );
		
		// calculates the endPoint so we can pass it to the next function
		GLintPoint endPoint;
		endPoint.x = start.x;
		endPoint.y = start.y + rectHeight;

		goldenVLeftRect(endPoint, rectHeight, rectWidth);
	}
}