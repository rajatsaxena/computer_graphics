#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<gl/Gl.h>
#include<gl/glu.h>
#include<gl/glut.h>

GLfloat rear = 0.0;
GLfloat center = 0.15;
GLfloat front = 0.33;
GLint count = 1;
GLint j=0;
int i=0;


GLUquadricObj *qobj,*qobj2,*qobj3,*qobj4,*qobj5;


//function to create table leg using solidcube
void tableLeg( double thick, double len)
    {
        glPushMatrix();    //push the current matrix
        glTranslated(0,len/2,0); //translation
        glScaled(thick/1.75,len,thick/2);  //scaling
        glutSolidCube(1.0);  //create solid cube
        glPopMatrix();  //pop the current matrix
    }


//function to draw worm and give motion
void  drawWorm()
    {
        //rear
        glColor3f(0,0.5,0); //set color to light green
        glPushMatrix();
        glTranslatef(rear+0.08,0.5,0);
        //glRotated(-90,0.0,1.0,0.0);
        glutSolidSphere(0.01,27,16);
        glPopMatrix();

        //3 cylinder are created for body
        glColor3f(0,0.48,0);
        glPushMatrix();
        qobj2=gluNewQuadric(); //create a quadrics object
        gluQuadricDrawStyle(qobj2, GLU_FILL); //render qobj2 with polygon primitive and draw in counter clockwise fashion
        glTranslatef(rear+0.08,0.5,0);
        glRotated(+90, 0.0, 1.0, 0.0);
        gluCylinder(qobj2,0.01,0.01, 0.1, 15, 5); //draw a cylinder with qobj2
        glPopMatrix();


        glColor3f(0,0.46,0);
        glPushMatrix();
        qobj=gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL);
        glTranslatef(center,0.5,0);
        glRotated(+90, 0.0, 1.0, 0.0);
        gluCylinder(qobj,0.01,0.01, 0.1, 15, 5);
        glPopMatrix();


        glColor3f(0,0.48,0);
        glPushMatrix();
        qobj=gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
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


        //motion control of worm by keeping track of count
        if(count > 1 && count <=11)
            {
                front = front + 0.003;
                count = count + 1;
                i++;
                    if(i==100)
                        exit(0);
            }

        else if(count > 11 && count <=21)
            {
                center = center + 0.003;
                count = count + 1;
            }

        else if(count > 21 && count <=31)
            {
                rear = rear + 0.003;
                count = count + 1;
            }

        else
            count = 2;


    }


//function to create table and pass parameter to tabel leg
void table(double tableWid, double tableThick, double legThick, double legLen)
    {
        //create table leg
        glColor3f(0.5,0.1,0.1);  //set color to brown
        double d = 0.95*tableWid/2.0 - legThick/2.0;
        glPushMatrix();
        glTranslated(d,0, d);
        tableLeg(legThick,legLen);
        glPushMatrix();
        glTranslated(-2*d,0, 0);
        tableLeg(legThick,legLen);
        glPushMatrix();
        glTranslated(0,0,-2*d);
        tableLeg(legThick,legLen);
        glPushMatrix();
        glTranslated(2*d,0,0);
        tableLeg(legThick,legLen);

        //create chair leg
        glPushMatrix();
        glColor3f(1,0.4,0);
        glTranslated(-d,-0.02,d/0.45);
        tableLeg(legThick/1.75,0.7);
        glPopMatrix();

        //create table top
        glPushMatrix();
        glColor3f(0.3,0,0);
        glTranslatef(-tableWid/2.0+legThick-tableWid/20 ,legLen,tableWid/2.0-legThick/2.0  );
        glScaled(tableWid,tableThick,tableWid);
        glutSolidCube(1);
        glPopMatrix();

        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

    }


//function to draw chair
void drawchair(double thick,double len)
    {
        glPushMatrix();
        glTranslated(-0.2*len,2.3*len,0.3);
        glRotated(25,1,0,0);
        glScaled(2.5*thick,1.05*len,thick/4);
        glutSolidCube(1.0);
        glPopMatrix();
   }




//function to draw teapot using solidteapot function
void drawteapot(double thick, double len)
    {
        glPushMatrix();      //push the current matrix
        glTranslated(0.35,0.3,0.5);   //multiply current matrix with the translation matrix
        glScaled(thick/3,len/3,thick/3);  //multiply with the scaling matrix
        glutSolidTeapot(1);                     // draw the teapot
        glPopMatrix();   //pop the current matrix
    }


//function to create glass filled with juice
void drawglass()
    {
        glPushMatrix();
        qobj3=gluNewQuadric();
        gluQuadricDrawStyle(qobj3, GLU_FILL);
        glTranslatef(0.2,0.3,0.5);
        glRotated(90,1.0,0.0,0.0);
        gluCylinder(qobj3,0.05,0.04, 0.1, 15, 5);
        glPushMatrix();
        glColor3f(1,0.4,0);
        glTranslatef(0,0,0.06);
        gluCylinder(qobj3,0.045,0.04, 0.08, 15, 5);
        glPopMatrix();
        glPopMatrix();
    }


//functin to draw lamp
void drawlamp()
    {
        glPushMatrix();

        glTranslatef(0.4,0.5,0.25);
        glScalef(1.7,0.1,1.7);
        glutSolidCube(0.09);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1,0.3,0.5);
        qobj3=gluNewQuadric();
        gluQuadricDrawStyle(qobj3, GLU_FILL);
        glTranslatef(0.4,0.7,0.25);
        glRotated(90,1.0,0.0,0.0);
        gluCylinder(qobj3,0.032,0.032, 0.18, 15, 5);
        glPopMatrix();


        glPushMatrix();
        //flickering
        j++;
        if(j%2==0)
            glColor3f(1,0.5,0);
        else
            glColor3f(1,1,0);

        qobj3=gluNewQuadric();
        gluQuadricDrawStyle(qobj3, GLU_FILL);
        glTranslatef(0.4,0.8,0.25);
        glRotated(90,1.0,0.0,0.0);
        gluCylinder(qobj3,0.06,0.1, 0.1, 15, 5);
        glPopMatrix();


    }

//function to create wall
void drawwall()
    {
        glPushMatrix();
        glutSolidCube(2.5);
        glPopMatrix();
    }


//function to draw book
void drawbook1(double thick,double len)
    {
        glPushMatrix();
        glTranslated(2*len,len,-0.4*len);
        glScaled(thick/3,len/14,thick/3);
        glutSolidCube(2.8);
        glPopMatrix();
    }


//function to draw book
void drawbook2(double thick,double len)
    {
        glPushMatrix();
        glTranslated(2.2*len,1.2*len,-0.45*len);
        glScaled(thick/3,len/14,thick/3);
        glutSolidCube(2.25);
        glPopMatrix();
    }


//display function
void display()
    {
        glMatrixMode(GL_PROJECTION);  //sets current matrix mode to projection matrix
        glLoadIdentity();  //replaces current matrix with identity matrix
        glMatrixMode(GL_MODELVIEW);   //sets current matrix mode to model view matrix

        glScalef(1.2,1.2,1.2);  //scaling

        table(0.85,0.15,0.15,0.45);
        glTranslatef(-0.2,0.07,0); //translation

        glColor3f(0.4,0,0.7);
        drawwall();

        glColor3f(1,0,0.15);   //draw chair
        drawchair(0.15,0.35);

        glColor3f(0.0,1,0.0);  //set color to green
        drawWorm();             //draw worm

        glColor3f(0.8,0.1,0.5); //set color to blue
        drawteapot(0.25,0.55);      //draw teapot


        glPushMatrix();
        glColor3f(1,0.95,0.8);  //set color
        glTranslated(0,0,0.15);
        drawbook1(0.25,0.25);    //draw book1
        glPopMatrix();

        glPushMatrix();     //drawbook2
        glColor3f(0.93,0.86,0.51);
        glTranslated(0,0,0.15);
        drawbook2(0.25,0.25);
        glPopMatrix();

        glColor3f(0.7,0.7,0.7);  //set color to white
        drawglass();   //draw glass

        glColor3f(0,0,0);
        drawlamp();

        glColor3f(1,1,1); //set color to white

        glTranslatef(0.2,-0.07,0);
        glTranslatef(-0.0,0.45+0.09,-0.25);
        glRotated(90,0,1,0);

        glRotated(-90,0,1,0);
        glTranslatef(0.0,-0.45-0.09,0.25);
        glScalef(1/1.2,1/1.2,1/1.2);

        glEnd();
        glFlush(); //forces execution of opengl functions in finite time
    }


void myinit()
    {
        glClearColor(0.0,0.0,0.0,0.0);  //set the clear color
        glColor3f(0.0,0.0,1.0);         //set the drawing color
        glMatrixMode(GL_PROJECTION); //sets the current matrix to pojection matrix
        glLoadIdentity();  //replace the pojection matrix with identity matrix

        glOrtho(0,1, 0, 1, 0, 1);  //multiply the current matrix with orthographic matrix
        glMatrixMode(GL_MODELVIEW); //sets the current matrix to modelview matrix
        gluLookAt(0.2,0.75,0.2,0.5,0.5,0.5, 0.0,1.0,0.0);  //viewing transformation
        glShadeModel(GL_SMOOTH); //smooth shading
    }


void Timer(int iUnused)
    {
        glutPostRedisplay(); //redisplay the current window
        glutTimerFunc(50, Timer, 0);   //set a timer callback of atleast 50msec
    }


int main(int argc, char** argv)
    {
        glutInit(&argc,argv);     //intialize glut library
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  //single buffereed and rgb window mode
        glutInitWindowSize(650,650);   //initial window position
        glutInitWindowPosition(100,150);  //width and height of drawing region
        glutCreateWindow("cg");     //create window with name CG
        glutDisplayFunc(display);  //function to draw to screen
        myinit();   //call to myinit
        Timer(0);   //call to timer
        glutMainLoop();   //displays the glut window and start the UI loop
        return 0;
    }
