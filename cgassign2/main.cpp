#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<gl/Gl.h>
#include<gl/glu.h>
#include<gl/glut.h>
#include <math.h> // math definitions

// escape key (for exit)
#define ESC 27

GLfloat rear = 0.0;
GLfloat center = 0.15;
GLfloat front = 0.33;
GLint count = 1;
GLint count1 = 1;
GLint flag = 0;
GLint j=0;
int i=0;


GLUquadricObj *qobj,*qobj2,*qobj3,*qobj4,*qobj5;

// Camera position
float x = 0.0, y = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

void changeSize(int w, int h)
{
	float ratio =  ((float) w) / ((float) h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

//function to draw worm and give motion
void  drawWorm()
    {
        //rear
        glColor3f(0,0.5,0); //set color to light green
        glPushMatrix();
        glTranslatef(rear+0.08,0.5,0);
        glRotated(-90,0.0,1.0,0.0);
        glutSolidSphere(0.01,27,16);
        glPopMatrix();

        //3 cylinder are created for body
        glColor3f(0,0.48,0);
        glPushMatrix();
        qobj2=gluNewQuadric(); //create a quadrics object
        gluQuadricDrawStyle(qobj2, GLU_FILL); //render qobj2 with polygon primitive and draw in counter clockwise fashion
        gluQuadricNormals(qobj2, GLU_SMOOTH); //generate normal for every vertex
        glTranslatef(rear+0.08,0.5,0);
        glRotated(+90, 0.0, 1.0, 0.0);
        gluCylinder(qobj2,0.01,0.01, 0.1, 15, 5); //draw a cylinder with qobj2
        glPopMatrix();


        glColor3f(0,0.46,0);
        glPushMatrix();
        qobj=gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glTranslatef(center,0.5,0);
        glRotated(+90, 0.0, 1.0, 0.0);
        gluCylinder(qobj,0.01,0.01, 0.1, 15, 5);
        glPopMatrix();


        glColor3f(0,0.48,0);
        glPushMatrix();
        qobj=gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glTranslatef(center+0.08,0.5,0);
        glRotated(+90, 0.0, 1.0, 0.0);
        gluCylinder(qobj, 0.01,0.01, 0.1, 15, 5);
        glPopMatrix();

        //create front part
        glColor3f(0,0.5,0);
        glPushMatrix();
        glTranslatef(front-0.015,0.5,0);
        glRotated(+90,0.0,1.0,0.0);
        glutSolidSphere(0.01,27,16);
        glPopMatrix();

        glutSwapBuffers();  //swap buffers

        //motion control of worm by keeping track of count
        if(count <= 10 && flag == 0)
            {
                front = front + 0.0003;
                count = count + 1;
            }

        else if(count > 1 && count <=11)
            {
                flag = 1;
                center = center + 0.0003;
                count = count - 1;
            }

        else
            {
                if(count1 <= 10)
                    {
                        rear = rear + 0.0003;
                        count1 = count1 + 1;
                    }
                else
                    {
                        count = 1;flag=0;count1 = 1;
                    }
            }


    }


void update(void)
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}

void renderScene(void)
{
	int i, j;

	// Clear color and depth buffers
	glClearColor(0, 0, 1.0, 0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(x, y, 1.0, x + lx, y + ly, 1.0, 0.0, 0.0, 1.0);



	// Draw ground
	glColor3f(1.0, 0.3, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(-100.0, -100.0, 0.0);
		glVertex3f(-100.0,  100.0, 0.0);
		glVertex3f( 100.0,  100.0, 0.0);
		glVertex3f( 100.0, -100.0, 0.0);
    glEnd();

	// Draw snow men

            glPushMatrix();
				glScalef(3,3,3);
				drawWorm();
			glPopMatrix();


	//glutSwapBuffers(); // Make it all visible
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
}

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.5; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5; break;
	}
}

void releaseSpecialKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.001; break;
		case GLUT_KEY_DOWN : deltaMove = 0.001; break;
	}
}


void mouseMove(int x, int y)
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("OpenGL Assignment 2");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(renderScene); // (re)display callback
	glutIdleFunc(update); // incremental update
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}
