#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


GLint flag=0,k=0;
GLfloat bez_t=0.0;
GLfloat bez_x=0.0;
GLfloat bez_y=0.0;
GLfloat ctrl_pnt[4][2]={{50.0,100.0},{100.0,200.0},{150.0,200.0},{200.0,100.0}}; //Initialize four control points
GLfloat bez_pnt[4][2] ={{50.0,100.0},{100.0,200.0},{150.0,200.0},{200.0,100.0}}; //Array to store the four control points

GLint i,j,x1,y1;

GLfloat decasteljau(GLfloat t,GLfloat v,GLfloat v1) //Function for de-casteljau's algorithm
{
	return ((1-t)*v + t*v1);
}

void pointer(GLint button, GLint state, GLint x, GLint y) //mouse function to get the co-ordinate of the mouse click
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //If Left Mouse click is encountered
	{
		//printf("%d %d\n",x,249-y);
		printf("Position to new point and right click \n");
		for(GLint m=0;m<4;m++)
		{
			x1=ctrl_pnt[m][0];y1=249-ctrl_pnt[m][1];
			if(x<=(x1+2) && x>=(x1-2) && y<=(y1+2) && y>=(y1-2)) //If Left Mouse click is on any valid control point within a +1/-1 range
			{
				k=m;flag=1;
				break;
			}
			else
			{
				flag=0;
			}
		}
	}
	if(flag==1)
	{
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) //On Right Mouse Click
		{
			ctrl_pnt[k][0]=x;ctrl_pnt[k][1]=249-y;flag=0;bez_t=0.0; //Setting the co-ordinate of Right Mouse Click as a control point
			for(GLint m=0;m<4;m++)                  //updating the curve
			{
				bez_pnt[m][0]=ctrl_pnt[m][0];
				bez_pnt[m][1]=ctrl_pnt[m][1];
			}
			glutPostRedisplay();
		}
	}
}
void Draw() {                           //Function to Draw the BEzier Curve
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);                 //Drawing the Four control points
	glVertex2fv(bez_pnt[0]);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2fv(bez_pnt[1]);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2fv(bez_pnt[2]);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2fv(bez_pnt[3]);
	glEnd();
	while(bez_t <= 1)                //Parametric curve from t=0 to t=1
	{
		i=3;
		while(i>0)
		{
			for(j=0;j<i;j++)
			{
				bez_pnt[j][0]=decasteljau(bez_t,bez_pnt[j][0],bez_pnt[j+1][0]);
				bez_pnt[j][1]=decasteljau(bez_t,bez_pnt[j][1],bez_pnt[j+1][1]);
			}
			i=i-1;
		}
		glColor3f(0.0, 0.0, 1.0);
		glPointSize(1.0);
		glBegin(GL_POINTS);                     //Draw the points on curve
		glVertex2fv(bez_pnt[0]);
		glEnd();
		bez_t=bez_t+0.00001;                   //Increment t by 0.00001
	}
	glFlush();
}


void Initialize() {                           //Initialise the matrix
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 250.0, 0.0, 250.0,0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int iArgc, char** cppArgv) {           //main function
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Beizer Curve (Editable)");
	Initialize();                               //calling initialise
	glutMouseFunc(pointer);                     //calling the mouse function
	glutDisplayFunc(Draw);                      //calling the Draw function
	glutMainLoop();
	return 0;
}

