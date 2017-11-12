// wire_frame demo
#include <GL/glut.h>
#include <math.h>

double const pi = 3.1415926;

float speed=0;

void drawCylinder()
{
    int ang;
    int delang = 10;
    float y0 = 0.0;
    float y1 = 0.3;
    float r0 = 0.4;
    float x,z,xold,zold;

    glBegin(GL_LINES);
    glColor3f(0.7,0.7,0.7);
    glVertex3f(r0,y0,0.0);
    glVertex3f(r0,y1,0.0);
    xold=r0;
    zold=0.0;
    int i = 0;
    for(ang=delang;ang<=360;ang+=delang)
    {
      x=(r0+r0/2.0*sin((double)ang*2.0*pi/360.0))*cos((double)ang*2.0*pi/360.0);
      z=r0*sin((double)ang*2.0*pi/360.0);
      glVertex3f(x,y0,z);
      glVertex3f(x,y1,z);
      glVertex3f(xold,y0,zold);
      glVertex3f(x,y0,z);
      glVertex3f(xold,y1,zold);
      glVertex3f(x,y1,z);
      xold=x;
      zold=z;
      if(i==0) break;
      i++;
    }
    glEnd();
}


void drawCircle()
{
    int vang,ang;
    int delang = 10;
    float r0 = 0.4;
    float x0,y0,z0,x1,y1,z1,x2,z2;

    glBegin(GL_LINES);

    for(vang=0;vang<=180;vang+=delang)
        {
             y0=r0*cos((double)(vang)*2.0*pi/360.0);
             y1=r0*cos((double)(vang+delang)*2.0*pi/360.0);
             x0=r0*sin((double)vang*2.0*pi/360.0);
             z0=0.0;
             for (ang=0;ang<=360;ang+=delang)
             {
                x1=r0*cos((double)ang*2.0*pi/360.0)*sin((double)vang*2.0*pi/360.0);
                x2=r0*cos((double)ang*2.0*pi/360.0)*sin((double)(vang+delang)*2.0*pi/360.0);
                z1=r0*sin((double)ang*2.0*pi/360.0)*sin((double)vang*2.0*pi/360.0);
                z2=r0*sin((double)ang*2.0*pi/360.0)*sin((double)(vang+delang)*2.0*pi/360.0);
                glColor3f((r0-x0)/r0,(r0-y0)/r0,(r0-z0)/r0);
                glVertex3f(x0,y0,z0);
                glVertex3f(x1,y0,z1);
                glVertex3f(x1,y0,z1);
                glVertex3f(x2,y1,z2);
                x0=x1;
                z0=z1;
             }
    }

    glEnd();
}


void drawObject()
{
      int ang,i;
      int delang = 10;
      float r[10] = {0.0,1.0,0.5,0.5,0.6,0.6,0.5,0.5,0.0};
      float y[10] = {0.0,0.0,0.1,0.8,0.8,1.0,1.0,0.9,0.9};
      float x1,x2,z1,z2,x3,z3;
      for (i=0;i<10;i++)
      {
          glBegin(GL_QUAD_STRIP);
          for(ang=0;ang<=360;ang+=delang)
          {
               x1=r[i]*cos((double)ang*2.0*pi/360.0);
               x2=r[i+1]*cos((double)ang*2.0*pi/360.0);
               z1=r[i]*sin((double)ang*2.0*pi/360.0);
               z2=r[i+1]*sin((double)ang*2.0*pi/360.0);
               x3=r[i]*cos((double)(ang+delang)*2.0*pi/360.0);
               z3=r[i]*sin((double)(ang+delang)*2.0*pi/360.0);
               glVertex3f(x1,y[i],z1);
               glVertex3f(x2,y[i+1],z2);
           }
        glEnd();
      }
}


 void display()
  {
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glPushMatrix();

     glRotated(speed,0,1,0);
     //glScalef(.1f,.2f,.2f);
     drawCylinder();
     glPopMatrix();
     glutSwapBuffers();
     glFlush();
  }

  static void timer(int value){
    //speed+=5;
    glutPostRedisplay();
    glutTimerFunc(500,timer,0);
  }
  void init()
  {
     glClearColor(0.0,0.0,0.2,1.0);
     glClearDepth(1.0);
     glEnable(GL_DEPTH_TEST);
     glMatrixMode(GL_PROJECTION);
  }



  int main(int argc, char** argv)
  {
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
     glutInitWindowSize(400,400);
     glutInitWindowPosition(0,0);
     glutCreateWindow("3D Rotation");
     glutDisplayFunc(display);
     glutIdleFunc(display);
     timer(0);
     init();
     glutMainLoop();
  }
