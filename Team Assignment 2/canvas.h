#include<gl/glut.h>
#include<cmath>
#include<iostream>

using namespace std;

//<<Support Classes for Canvas>>>
class Point2   //single point w/ floating point coordinates
{
public:
	Point2() {x = y = 0.0f;} //constructor 1
	Point2(float xx, float yy) {x=xx; y=yy;} //constructor 2
	void set(float xx, float yy) {x=xx; y=yy;}
	float getX() {return x;}
	float getY() {return y;}
	void draw(void)
	{
		glBegin(GL_POINTS); //draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
		glFlush();
	}
private:
	float x, y;
};

class IntRect  //aligned rectangle with integer coordinates, used for viewport
{
public:
	IntRect() {l = 0; r=100; b=0; t=100;} //constructors
	IntRect(int left, int right, int bottom, int top)
		{l = left; r=right; b=bottom; t=top;}
	void set(int left, int right, int bottom, int top)
	{
		l=left; r=right; b=bottom; t=top;
	}
	void draw(void); //draw this rectangle using OpenGL
	int getL(void)
	{
		return l;
	}
	int getR(void)
	{
		return r;
	}
	int getT(void)
	{
		return t;
	}
	int getB(void)
	{
		return b;
	}

private:
	int l, r, b, t;
};

class RealRect   //simlar to IntRect but w/ floating points & used for world window
{
public:
	RealRect() {l = 0; r=100; b=0; t=100;} //constructors
	RealRect(float left, float right, float bottom, float top)
		{l = left; r=right; b=bottom; t=top;}
	void set(float left, float right, float bottom, float top)
	{
		l=left; r=right; b=bottom; t=top;
	}
	float getL(void)
	{
		return l;
	}
	float getR(void)
	{
		return r;
	}
	float getT(void)
	{
		return t;
	}
	float getB(void)
	{
		return b;
	}
	void draw(void); //draw this rectangle using OpenGL
private:
	float l, r, b, t;
};


//<<End Support Classes>>>



class Canvas
{
public:
	Canvas(int width, int height, char* windowTitle); //constructor
        void setWindow(float l, float r, float b, float t);
        void setViewport(int l, int r, int b, int t);
        IntRect getViewport(void); //divulge the viewport data
        RealRect getWindow(void); // divulge the window data
        float getWindowAspectRatio(void);
        void clearScreen();
        void setBackgroundColor(float r, float g, float b);
        void setColor(float r, float g, float b);
        void lineTo(float x, float y);
        void lineTo(Point2 p);
        void moveTo(float x, float y);
        void moveTo(Point2 p);
		void moveRel(float dx, float dy);
		void lineRel(float dx, float dy);
		void turnTo(float angle);          // turtle graphics routines
		void turn(float angle);
		void forward(float dist, int isVisible);
private:
     Point2 CP;         //current position in the world
     IntRect viewport;  //the current window
     RealRect window;   //the current viewport
	 float CD;          //current direction for turtle graphics
} ;

