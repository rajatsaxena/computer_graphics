#ifndef WIN32
#define WIN32
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

   static GLfloat spin = 0.0;
   static GLfloat torso_spin = 0.0;
   static GLfloat left_shoulder_spin = 0.0;
   static GLfloat right_shoulder_spin = 0.0;
   static GLfloat left_elbow_spin = 0.0;
   static GLfloat right_elbow_spin = 0.0;
   static GLfloat right_leg_spin = 0.0;
   static GLfloat left_leg_spin = 0.0;

    GLUquadricObj *qobj;

   int body1=0;
   int body1_color=0;

//Store the value for head
float octahedron_verts_head[][3] = {{-1.00,-0.75,0.45},{-0.29,-0.75,1.01},{-0.29,0.80,1.01},{-1.00,0.80,0.45},{0.60,-0.75,0.81},{0.60,0.80,0.81},{1.00,-0.75,0.01},{1.00,0.80,0.01},{0.60,-0.75,-0.80},{0.60,0.80,-0.80},{-0.29,-0.75,-1.00},{-0.29,0.80,-1.00},{-1.00,-0.75,-0.44},{-1.00,0.80,-0.44}};

int octahedron_faces_head[] = {0, 1, 2,3,-1,1,4,5,2,-1,4,6,7,5,-1,6,8,9,7,-1,8,10,11,9,-1,10,12,13,11,-1,12,0,3,13,-1,2,5,7,9,11,13,3,-2};



//Store the values for hand
float octahedron_verts_hand[][3]={{-0.81,-2.99,0.57},{-0.31,-2.99,0.95},{-0.31,3.01,0.95},{-0.81,3.01,0.57},{0.31,-2.99,0.95},{0.31,3.01,0.95},{0.81,-2.99,0.57},{0.81,3.01,0.57},{1.00,-2.99,-0.05},{1.00,3.01,-0.05},{0.81,-2.99,-0.67},{0.81,3.01,-0.67},{0.31,-2.99,-1.05},{0.31,3.01,-1.05},{-0.31,-2.99,-1.05},{-0.31,3.01,-1.05},{-0.81,-2.99,-0.67},{-0.81,3.01,-0.67},{-1.00,-2.99,-0.05},{-1.00,3.01,-0.05}};

int octahedron_faces_hand[] = {0,1,2,3,-1,1,4,5,2,-1,4,6,7,5,-1,6,8,9,7,-1,8,10,11,9,-1,10,12,13,11,-1,12,14,15,13,-1,14,16,17,15,-1,16,18,19,17,-1,18,0,3,19,-2};
// End of hnd code.



//Store the values for leg
float octahedron_verts_leg[][3]={{-1.10,-3.00,0.00},{-0.58,-3.00,1.05},{-0.58,3.00,1.05},{-1.10,3.00,0.00},{0.47,-3.00,1.05},{0.47,3.00,1.05},{1.00,-3.00,0.00},{1.00,3.00,0.00},{0.47,-3.00,-1.05},{0.47,3.00,-1.05},{-0.58,-3.00,-1.05},{-0.58,3.00,-1.05}};

int octahedron_faces_leg[] = {0, 1, 2,3,-1,1,4,5,2,-1,4,6,7,5,-1,6,8,9,7,-1,8,10,11,9,-1,10,0,3,11,-2};
// End of leg code


   void init(void)
   {
      glClearColor (0.0, 0.0, 0.0, 0.0);
      glClearDepth (1.0);


      glShadeModel (GL_FLAT);
   }

void draw_head(void)
{
   int head=0;
   int head_color=0;
 glBegin (GL_POLYGON);
   glColor4f(1, 1, 0, 0);

   while (octahedron_faces_head[head] != -2)
{
        if (octahedron_faces_head[head] == -1)
{
if(head_color == 1)
{
           head_color=0;
}
else
{
head_color++;
}
glEnd();

glBegin(GL_POLYGON);
if(head_color == 1)
{
glColor4f(1, 1, 1, 0);
}
else
{
glColor4f(1, 0, 0, 0);
}
}

else
{
glVertex3fv(octahedron_verts_head[octahedron_faces_head[head]]);
}
head++;
}
glEnd();
}



// This method is used to draw the body.
void draw_body(void)
{
body1=0;
body1_color=0;
   glBegin (GL_POLYGON);
   glColor4f(1, 1, 0, 0);

   while (octahedron_faces_head[body1] != -2)
{
        if (octahedron_faces_head[body1] == -1)
{
if(body1_color == 1)
{
           body1_color=0;
}
else
{
body1_color++;
}
            glEnd();
            glBegin(GL_POLYGON);
if(body1_color == 1)
{
glColor4f(1, 1, 1, 0);
}
else
{
glColor4f(1, 0, 0, 0);
}

        }
else
{
            glVertex3fv(octahedron_verts_head[octahedron_faces_head[body1]]);
       }
       body1++;
}
glEnd();
}


// Function to create the method hand
void hand_draw(void)
{
   glBegin (GL_POLYGON);
   glColor4f(1, 1, 0, 0);
body1=0;
body1_color=0;
   while (octahedron_faces_hand[body1] != -2)
{
        if (octahedron_faces_hand[body1] == -1)
{
if(body1_color == 1)
{
           body1_color=0;
}
else
{
body1_color++;
}
            glEnd();
            glBegin(GL_POLYGON);
if(body1_color == 1)
{
glColor4f(1, 1, 1, 0);
}
else
{
glColor4f(1, 0, 0, 0);
}

        }
else
{
            glVertex3fv(octahedron_verts_hand[octahedron_faces_hand[body1]]);
       }
       body1++;
}
glEnd();
}



// Draw the Leg.
void leg_draw(void)
{
   glBegin (GL_POLYGON);
   glColor4f(1, 1, 0, 0);
body1=0;
body1_color=0;
   while (octahedron_faces_leg[body1] != -2)
{
        if (octahedron_faces_leg[body1] == -1)
{
if(body1_color == 1)
{
           body1_color=0;
}
else
{
body1_color++;
}
            glEnd();
            glBegin(GL_POLYGON);
if(body1_color == 1)
{
glColor4f(1, 1, 1, 0);
}
else
{
glColor4f(1, 0, 0, 0);
}

        }
else
{
            glVertex3fv(octahedron_verts_leg[octahedron_faces_leg[body1]]);
       }
       body1++;
}
glEnd();
}


 void display(void)
  {

     glPushMatrix();
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     gluLookAt ( 0., 3, 12.0, 0., 0.5, 0., 0., 0.5, 0.5 );
     glEnable (GL_DEPTH_TEST);


    glPushMatrix();
    glRotatef(torso_spin, 0.0, 1.0, 0.0);// Rotate the whole torso, which will move the hand , arms and the shoulder.


    glPushMatrix();
    glScalef(1.75,1.5,1);
    draw_head();// Draw the head.
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(3,5,3);
    draw_body();// Draw the torso
    glPopMatrix();

    glPushMatrix();
    glRotatef(left_shoulder_spin, 1, 0, 0);

    glPushMatrix();
    glTranslatef(-4,-4,0);// Left Shoulder
    hand_draw();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4,-9,0);// Draw elbow.
    glRotatef(left_elbow_spin, 1.0, 0.0, 0.0);// Rotate for Elbow.
    hand_draw();
    glPopMatrix();// End of elbow.

    glPopMatrix();

    glPushMatrix();
    glRotatef(right_shoulder_spin, 1, 0, 0);


    glPushMatrix();
    glTranslatef(4,-4,0);
    hand_draw();//Draw Right Hand
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4,-9,0);// Drw the right elbow.
    glRotatef(right_elbow_spin, 1.0, 0.0, 0.0);// Rotate for the right elbow.
    hand_draw();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);

    glPushMatrix();
    glTranslatef(0,-11,0);
    glScalef(3,3,3);
    draw_body();// Draw Hip
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.3,-17,0);
    glRotatef(left_leg_spin, 1.0, 0.0, 0.0);
    leg_draw();//
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3,-17,0);
    glRotatef(right_leg_spin, 1.0, 0.0, 0.0);
    leg_draw();//
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();

   }

  void reshape(int w, int h)
  {
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(120.0, 1.0, 0.1, 12000000.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
  }

  void special(unsigned char Key, int x,int y)
  {
       if(Key == 't') // Movement of torso
     {
          torso_spin = torso_spin + 2;
          if(torso_spin<=25){glutPostRedisplay();}
     }
       else if (Key == 'T') // movement of torso backwards
     {
          torso_spin = torso_spin - 2;
          if(torso_spin>=-25)
         {
           glutPostRedisplay();
         }
     }

        else if(Key == 's')// Movement of shoulder
     {
          left_shoulder_spin = left_shoulder_spin + 1;
          right_shoulder_spin = right_shoulder_spin - 1;
          left_elbow_spin = left_elbow_spin + 2;
          right_elbow_spin = right_elbow_spin - 2;
          right_leg_spin = right_leg_spin + 2;
          left_leg_spin = left_leg_spin - 2;
          if(left_shoulder_spin<=10 && right_shoulder_spin>=-10 && left_elbow_spin<=10 && right_elbow_spin >= -10 && right_leg_spin<=10 && left_leg_spin >= -10)
          {glutPostRedisplay();}
     }
       else if (Key == 'S') // Movement of shoulder  Backwards
     {
          left_shoulder_spin = left_shoulder_spin - 1;
          right_shoulder_spin = right_shoulder_spin + 1;
          left_elbow_spin = left_elbow_spin - 2;
          right_elbow_spin = right_elbow_spin + 2;
          right_leg_spin = right_leg_spin - 2;
          left_leg_spin = left_leg_spin + 2;
          if(left_shoulder_spin>=-10 && right_shoulder_spin<=10 && left_elbow_spin>=-10 && right_elbow_spin <=10 && right_leg_spin>=-10 && left_leg_spin <=10)
          {glutPostRedisplay();}
          else
          {
              glutDisplayFunc(display);
          }
     }

        /*else if(Key == 'e')// Movement of elbow
     {
          left_elbow_spin = left_elbow_spin + 2;
          right_elbow_spin = right_elbow_spin - 2;
          if(left_elbow_spin<=10 && right_elbow_spin >= -10)
          {glutPostRedisplay();}
     }
       else if (Key == 'E') // Movement of elbow
     {
          left_elbow_spin = left_elbow_spin - 2;
          right_elbow_spin = right_elbow_spin + 2;
          if(left_elbow_spin>=-10 && right_elbow_spin <=10)
          {glutPostRedisplay();}
     }*/
  }

/*
*  Request double buffer display mode.
*  Register mouse input callback functions
*/
   int main(int argc, char** argv)
   {
glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize (720, 640);
     glutInitWindowPosition (100, 100);
     glutCreateWindow (argv[0]);
     init ();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
//     glutSpecialFunc(special);
     glutKeyboardFunc(special);
     glutMainLoop();
     return 0;

   }

