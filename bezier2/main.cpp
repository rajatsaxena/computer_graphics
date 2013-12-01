/*Program to Draw the n-th order Bezier curve from n+1 user given control points using Bernstein Polynomial Technique*/

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>

using namespace std;

GLfloat t1,r1,t=0.0;GLfloat x=0.0,y=0.0,fa=1.0,fb=1.0,fc=1.0;
GLfloat n;  //Number of Control Points
GLfloat p1[2]={0.0,0.0}; //To store Points on curve

class Point   //Class with x & Y as the variables
{
public:
	GLfloat x,y;
	Point()         //constructor to initialise x,y with 0.0
	{
		x=0.0;
		y=0.0;
	}
	void set(GLfloat x1, GLfloat y1)   //set function to initialise x,y with the user given points
	{
		x=x1;y=y1;
	}
};
Point *ctrl_pnt;  //A pointer to class Point which stores all the control points

GLfloat fact(GLfloat v)  //Function to calculate and return the factorial of a number
{
	GLfloat f=1.0;
	if(v==0.0)
		f=1.0;
	else
		for(GLfloat i=1.0;i<=v;i++)
			f=f*i;
	return f;
}

void Draw() {                   //Function to draw the Bezier Curve
	glColor3f(1.0, 1.0, 1.0);
	GLfloat n1=n-1;
	while(t<=1.0)              //Parametric curve from t=0 to t=1
	{
		p1[0]=0.0;p1[1]=0.0;t1=0.0;r1=0.0;
		for(GLint r=0.0;r<=n1;r++)
		{
			t1=1.0-t;GLfloat r1=n1-r;
			fa=fact(n1);fb=fact(r1);fc=fact(r);
			p1[0] = p1[0] + fa/(fb*fc) * pow(t1,r1) * pow(t,r) * ctrl_pnt[r].x; //calculating the x value on the curve at given t
			p1[1] = p1[1] + fa/(fb*fc) * pow(t1,r1) * pow(t,r) * ctrl_pnt[r].y; //calculating the y value on the curve at given t
		}
		glBegin(GL_POINTS);   //Drawing the x,y points on the curve
			glVertex2fv(p1);
		glEnd();
		t=t+0.001;           //Incrementing t by 0.001
	}
	glFlush();
}
void Initialize() {                     //function to initialise the Matrix
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 250.0, 0.0, 250.0,0.0, 1.0);
}
//Main function
int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Beizer Curve Bernstein Polynomial");
	Initialize();
	printf("Enter no of control points\n");
	scanf("%f",&n);                                //Input number of control points on 'n'
	ctrl_pnt = (Point *)malloc(n*sizeof(Point));
	printf("\nEnter x,y co-ordinate values :\n");
	GLfloat x1,y1;
	for(GLint i=0;i<=(n-1);i++)
	{
		printf("Enter %d x co-ordinate:\n",i+1);
		scanf("%f",&x1);                         //Input x co-ordinate of the (i+1)th control point
		printf("Enter %d y co-ordinate:\n",i+1);
		scanf("%f",&y1);                        //Input x co-ordinate of the (i+1)th control point
		ctrl_pnt[i].set(x1,y1);                //calling the set function to initialise the Point class object ctrl_pnt
	}
	glutDisplayFunc(Draw);                    //calling Draw function
	glutMainLoop();
	return 0;
}
