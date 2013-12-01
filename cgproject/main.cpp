#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


   static GLfloat spin = 0.0;
   static GLfloat flag = 0.0;

   static GLfloat body = 0.0;
   static GLfloat left_shoulder = 0.0;
   static GLfloat right_shoulder = 0.0;
   static GLfloat left_arm = 0.0;
   static GLfloat right_arm = 0.0;
   static GLfloat right_leg = 0.0;
   static GLfloat left_leg = 0.0;

  GLUquadricObj *qobj;

   void init(void)
   {

      glClearColor (0.5f, 0.5f, 0.5f, 1);
      glClearDepth (1.0);
      glShadeModel (GL_FLAT);
      glEnable(GL_FOG);
   }

   void draw_head(void)
   {
   glPushMatrix();
   glColor3f(1,0.55,0);
   glutSolidSphere(1.25,15,5);
   glPopMatrix();
   glEnd();
   }

   void draw_body(void)
   {
   glPushMatrix();
   qobj=gluNewQuadric();
   gluQuadricDrawStyle(qobj,GL_FILL);
   glRotatef(90,1,0,0);
   glColor3f(0,1,0);
   gluCylinder(qobj,1.05,1.05,1,10,5);
   glPopMatrix();
   glEnd();
   }


// Function to create the hand

   void hand_draw(void)
   {
   glPushMatrix();
   qobj=gluNewQuadric();
   gluQuadricDrawStyle(qobj,GL_FILL);
   glRotatef(90,1,0,0);
   glColor3f(0,0.8,0);
   gluCylinder(qobj,1.05,1.05,1,10,5);
   glPopMatrix();
   }


// Function to draw the Leg.
   void leg_draw(void)
   {
   glPushMatrix();
   qobj=gluNewQuadric();
   gluQuadricDrawStyle(qobj,GL_FILL);
   glRotatef(90,1,0,0);
   glColor3f(0,0,0.5);
   gluCylinder(qobj,1.05,1.05,3,10,5);
   glPopMatrix();
   glEnd();
   }

   void elbow_draw()
   {
   glPushMatrix();
   qobj=gluNewQuadric();
   gluQuadricDrawStyle(qobj,GL_FILL);
   glRotatef(90,1,0,0);
   glColor3f(1,0.55,0);
   gluCylinder(qobj,1.05,1.05,1,10,5);
   glPopMatrix();
   glEnd();
   }

   void display(void)
   {
    glPushMatrix();
    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 10.0f);
    glFogf(GL_FOG_END, 20.0f);
    glPopMatrix();

   glPushMatrix();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gluLookAt ( 0., 3, 12.0, 0., 0.5, 0., 0., 0.5, 0.5 );
   glEnable (GL_DEPTH_TEST);

   glPushMatrix();
   glRotatef(body, 0.0, 1.0, 0.0); // Rotate the whole body, which will move the arms and the shoulder.


    glPushMatrix();
    glScalef(1.75,2.25,2);
    draw_head();// Draw the head.
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-2,0);
    glScalef(3,9,3);
    draw_body();// Draw the body
    glPopMatrix();

    glPushMatrix();
    glRotatef(left_shoulder, 1, 0, 0);

    glPushMatrix();
    glTranslatef(-4,-3,0);// Left Shoulder
    glScalef(1.0,4.5,1.0);
    hand_draw();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4,-7.25,0);// Draw elbow.
    glRotatef(left_arm, 1.0, 0.0, 0.0);// Rotate for Elbow.
    glScalef(0.9,3,0.8);
    elbow_draw();
    glPopMatrix();// End of elbow.

    glPopMatrix();

    glPushMatrix();
    glRotatef(right_shoulder, 1, 0, 0);


    glPushMatrix();
    glTranslatef(4,-3,0);
    glScalef(1.0,4.5,1.0);
    hand_draw();//Draw Right Hand
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4,-7.25,0);// Drw the right elbow.
    glRotatef(right_arm, 1.0, 0.0, 0.0);// Rotate for the right elbow.
    glScalef(0.9,3,0.8);
    elbow_draw();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);

    glPushMatrix();
    glTranslatef(-1.3,-13,0);
    glRotatef(left_leg, 1.0, 0.0, 0.0);
    glScalef(1.0,2.5,1.0);
    leg_draw();//
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3,-13,0);
    glRotatef(right_leg, 1.0, 0.0, 0.0);
    glScalef(1.0,2.5,1.0);
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
       if(Key == 'a') // Movement of body
     {

          if(body<=25)
          {
          body = body + 2;
          glutPostRedisplay();
          }
     }

       else if (Key == 'd') // movement of body
     {

          if(body>=-25)
         {
           body = body - 2;
           glutPostRedisplay();
         }
     }
        else if(Key == 'w')// Movement of shoulder
     {

          if(left_shoulder<=5 && right_shoulder>=-5 && left_arm<=10 && right_arm >= -10 && right_leg<=10 && left_leg >= -10)
          {
          left_shoulder = left_shoulder + 1;
          right_shoulder = right_shoulder - 1;
          left_arm = left_arm + 2;
          right_arm = right_arm - 2;
          right_leg = right_leg + 2;
          left_leg = left_leg - 2;
          glutPostRedisplay();
          }
     }


       else if (Key == 's') // Movement of shoulder
     {

          if(left_shoulder>=-5 && right_shoulder<=5 && left_arm>=-10 && right_arm <=10 && right_leg>=-10 && left_leg <=10)
          {
          left_shoulder = left_shoulder - 1;
          right_shoulder = right_shoulder + 1;
          left_arm = left_arm - 2;
          right_arm = right_arm + 2;
          right_leg = right_leg - 2;
          left_leg = left_leg + 2;
          glutPostRedisplay();
          }
     }

     else if (Key == 'r')     //automated walking
{
          if(flag==0 && right_shoulder<=5)
{

          left_shoulder = left_shoulder - 1;
          right_shoulder = right_shoulder + 1;
          left_arm = left_arm - 2;
          right_arm = right_arm + 2;
          right_leg = right_leg - 3;
          left_leg = left_leg + 3;
          glutPostRedisplay();
          if(right_shoulder==5)
          flag=1;
}

          if(flag==1 && right_shoulder>=-5)

{

         left_shoulder = left_shoulder + 1;
         right_shoulder = right_shoulder - 1;
         left_arm = left_arm + 2;
         right_arm = right_arm - 2;
         right_leg = right_leg + 3;
         left_leg = left_leg - 3;
         glutPostRedisplay();
         if(right_shoulder==-5)
         flag=0;
}

     }

  }


   int main(int argc, char** argv)
   {
     glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize (720, 640);
     glutInitWindowPosition (150, 50);
     glutCreateWindow (argv[0]);
     init ();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutKeyboardFunc(special);
     glutMainLoop();
     return 0;
   }
