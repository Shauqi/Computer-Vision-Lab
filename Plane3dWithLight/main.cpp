/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<bits/stdc++.h>
#include "Table.h"
#include "Operations.h"
using namespace std;

/* Global variables */
char title[] = "3D Plane";
GLUquadricObj *quadratic;
GLUquadricObj *quadratic2;
GLUquadricObj *quadratic3;

//const double MAX_INTENSITY=255.0;
float trans_x = 0.0;
float trans_y = 0.0;
float trans_z = -7.0;

// for giving access to rotation
float xMode=0.0;
float yMode=0.0;
float zMode=0.0;

// Global values for glulookat
// angle of rotation for the camera direction
float angle=0.0;
//Basic Matrix
double basic_mat[16];

/*float eye_x = 0.0, eye_y = 0.0, eye_z = 0.0;
float center_x = 0.0, center_y = 0.0, center_z = -1.0;
float up_x = 0.0, up_y = 1.0, up_z = 0.0;*/

// Angle for plane rotation
float planeAngle = 0.0;
int li_0=0;
int amb=0,diff=0,spec=0,shin=0;

double const pi = 3.1415926;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=0.0f;
// Reference position of camera
float center_y = 1.0;

// Transforming Basic Matrix into identity
void loadMatrix()
{
    memset(basic_mat,0,sizeof(basic_mat));
    for(int i=0; i<16; i+=5)basic_mat[i]=1;
}


void lookAt(int eyeX, int eyeY, int eyeZ ,int lookX, int lookY, int lookZ, int headX,int headY,int headZ)
{
    //Xv.clear();Yv.clear();Zv.clear();
    float ZvX=(eyeX-lookX);
    float ZvY=(eyeY-lookY);
    float ZvZ=(eyeZ-lookZ);
    //Zv.push_back(eyeZ-lookZ);
    //for(int i=0;i<3;i++)cout<<Zv[i]<<" ";

    int i1=headX, j1=headY, k1=headZ;
    int i2=ZvX, j2=ZvY, k2=ZvZ;

    float XvX=((k2)*(j1)-(j2)*(k1));
    float XvY=(-(k2)*(i1)+(i2)*(k1));
    float XvZ=((j2)*(i1)-(i2)*(j1));
//    for(int i=0;i<3;i++)cout<<Xv[i]<<" ";
//    cout<<endl;
    i1=ZvX, j1=ZvY, k1=ZvZ;
    i2=XvX, j2=XvY, k2=XvZ;
    float YvX=((k2)*(j1)-(j2)*(k1));
    float YvY=(-(k2)*(i1)+(i2)*(k1));
    float YvZ=((j2)*(i1)-(i2)*(j1));
    //for(int i=0;i<3;i++)cout<<Yv[i]<<" ";

    float nMod=sqrt(ZvX*ZvX+ZvY*ZvY+ZvZ*ZvZ);
    float uMod=sqrt(XvX*XvX+XvY*XvY+XvZ*XvZ);
    float vMod=sqrt(YvX*YvX+YvY*YvY+YvZ*YvZ);

    //cout<<endl;
    //cout<<nMod<<" "<<uMod<<" "<<vMod;
    XvX/=uMod; XvY/=uMod; XvZ/=uMod;
    YvX/=vMod; YvY/=vMod; YvZ/=vMod;
    ZvX/=nMod; ZvY/=nMod; ZvZ/=nMod;


    float rot[16]={XvX, YvX, ZvX, 0,
                   XvY, YvY, ZvY, 0,
                   XvZ, YvZ, ZvZ, 0,
                   0,       0,     0,   1
                   };

    //cout<<endl;cout<<endl;

  /*  for(int i=0;i<16;i++){
        cout<<rot[i]<<"    ";
    }
*/


    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(rot);



    glTranslatef(-eyeX,-eyeY,-eyeZ);
}





void light()
{
    GLfloat light_ambient[]  = {.50, .50, .50, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_position[] = { 0.0, 20.0, 0.0, 1.0 };

    glEnable( GL_LIGHT0);
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv( GL_LIGHT0, GL_POSITION, light_position);
            GLfloat spot_direction[] = { 0.0, -1, 0.0 };
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
            glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
    if(li_0==1)
    glDisable( GL_LIGHT0);
}


void metarial_color_shine(float a,float b,float c,float d)
{
    if(amb==0)
    {
        GLfloat mat_ambient[] = {   a/2,b/2,c/2, 1.0 };
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    }
    else
    {
        GLfloat mat_ambient[] = {   0.0,0.0,0.0, 1.0 };
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    }

    if(diff==0)
    {
        GLfloat mat_diffuse[] = { a,b,c, 1.0 };
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    }
    else
        {
         GLfloat mat_diffuse[] = {   0.0,0.0,0.0, 1.0 };
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        }

    if(spec==0)
    {

        GLfloat mat_specular[] = { .10, .10, .10, 1.0 };

 glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    }
    else{
        GLfloat mat_specular[] = { 0,0,0, 1.0 };

 glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    }

         GLfloat mat_shininess[] = {d};
       glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

}



/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor((180/MAX_INTENSITY), (200/MAX_INTENSITY),(200/MAX_INTENSITY), 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void drawHalfSphere(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];
   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
 }


void drawCylinder()
{

    quadratic = gluNewQuadric();
    gluCylinder(quadratic,0.5f,0.5f,3.0f,32,32);
}


void drawCylinder2()
{
    quadratic2 = gluNewQuadric();
    gluCylinder(quadratic,0.5f,0.1f,0.8f,32,32);
}


void drawWing()
{
    // Backwing left right
    //glColor3f(255/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY);
    metarial_color_shine(255/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,1.0);

    glBegin(GL_POLYGON);
    glVertex3f(0.0f,0.5f,-1.0f);
    glVertex3f(0.0f,1.0f,0.3f);
    glVertex3f(0.0f,1.0f,1.0f);
    glVertex3f(0.0f,-1.0f,1.0f);
    glVertex3f(0.0f,-1.0f,0.3f);
    glVertex3f(0.0f,-0.5f,-1.0f);
    glEnd();

    // Backwing up down
    glBegin(GL_POLYGON);
    glVertex3f(0.5f,0.0f,-1.0f);
    glVertex3f(1.0f,0.0f,0.3f);
    glVertex3f(1.0f,0.0f,0.8f);
    glVertex3f(0.0f,0.0f,1.0f);
    glEnd();

    // LeftWing
    glBegin(GL_POLYGON);
    glVertex3f(0.0f,0.5f,-2.8f);
    glVertex3f(-0.8f,3.0f,-1.8f);
    glVertex3f(-0.8f,3.0f,-1.0f);
    glVertex3f(0.0f,0.0f,-1.4f);
    glEnd();

    //RightWing
    glBegin(GL_POLYGON);
    glVertex3f(0.0f,-0.5f,-2.8f);
    glVertex3f(-0.8f,-3.0f,-1.8f);
    glVertex3f(-0.8f,-3.0f,-1.0f);
    glVertex3f(0.0f,0.0f,-1.4f);
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


void drawCylinderMy()
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
    }
    glEnd();
}

void drawPlane()
{
    // Draw Base
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-2.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(90.0,0.0,1.0,0.0);
    metarial_color_shine(255/MAX_INTENSITY,255/MAX_INTENSITY,0/MAX_INTENSITY,1);
    drawCylinder();
    glPopMatrix();

    // Draw Head
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,0.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(-90.0,0.0,0.0,1.0);
    metarial_color_shine(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawHalfSphere(30,30,.5);
    glPopMatrix();

    // Draw Tail
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-2.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(-90.0,0.0,1.0,0.0);
    metarial_color_shine(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawCylinder2();
    glPopMatrix();

    // Draw Wing
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-2.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(-90.0,0.0,1.0,0.0);
    glRotatef(90.0,0.0,0.0,1.0);
    drawWing();
    glPopMatrix();
}


void drawTable()
{
    //glColor3f(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY);
    // Base
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-1.5,-2.0,0.0);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,6.0,0.3,4.0);
    glMultMatrixd(basic_mat);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();

    //Left Front Leg
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-5.8,-4.3,2.5);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,0.5,2.0,0.5);
    glMultMatrixd(basic_mat);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();



    //Right Front Leg
    glPushMatrix();

    loadMatrix();
    translate(basic_mat,3.0,-4.3,2.5);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,0.5,2.0,0.5);
    glMultMatrixd(basic_mat);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();


    //Left Back Leg
    glPushMatrix();

    loadMatrix();
    translate(basic_mat,-5.8,-4.3,-2.5);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,0.5,2.0,0.5);
    glMultMatrixd(basic_mat);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();


    //Right Back Leg
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,3.0,-4.3,-2.5);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,0.5,2.0,0.5);
    glMultMatrixd(basic_mat);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();
}


void drawBed()
{
    //Base
    glPushMatrix();
    //glColor3f(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY);
    metarial_color_shine(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    glTranslatef(-2.3,-1.0,1.0);
    glScalef(0.4,0.2,1.0);
    drawBaseCube();
    glPopMatrix();

    //BedSheet
    glPushMatrix();
    //glColor3f(255/MAX_INTENSITY,155/MAX_INTENSITY,0/MAX_INTENSITY);
    metarial_color_shine(255/MAX_INTENSITY,155/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    glTranslatef(-2.3,-0.8,1.0);
    glScalef(0.4,0.05,1.0);
    drawBaseCube();
    glPopMatrix();
}

void drawTv()
{

    glPushMatrix();
    glTranslatef(2.3,0.8,1.0);
    glScalef(0.01,0.6,0.85);
    metarial_color_shine(124/MAX_INTENSITY,155/MAX_INTENSITY,124/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.29,0.8,1.0);
    glScalef(0.01,0.45,0.75);
    metarial_color_shine(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
    drawBaseCube();
    glPopMatrix();
}



void rotateAroundLine(double start_x, double start_y, double start_z,
                      double end_x, double end_y, double end_z)
{
// inverse translate
    //glTranslatef(start_x,start_y,start_z);
    loadMatrix();
    translate(basic_mat,start_x,start_y,start_z);
    glMultMatrixd(basic_mat);


// inverse align
    loadMatrix();
    double a=end_x-start_x, b=end_y-start_y, c=end_z-start_z;
    double lambda= sqrt(b*b+c*c);
    double v_mod= sqrt(a*a+b*b+c*c);

    basic_mat[0]=lambda/v_mod;
    basic_mat[1]= -(a*b) /(lambda*v_mod);
    basic_mat[2]= -(a*c) /(lambda*v_mod);
    basic_mat[5]= c/lambda;
    basic_mat[6]= -b/lambda;
    basic_mat[8]=a/v_mod;
    basic_mat[9]= b/v_mod;
    basic_mat[10]= c/v_mod;

    glMultMatrixd(basic_mat);


    // rotate
    glRotatef(planeAngle,0,0,1);


    // Aligning with Z axis
    loadMatrix();
    basic_mat[0]=lambda/v_mod;
    basic_mat[2]=a/v_mod;
    basic_mat[4]= -(a*b) /(lambda*v_mod);
    basic_mat[5]= c/lambda;
    basic_mat[6]= b/v_mod;
    basic_mat[8]= -(a*c) /(lambda*v_mod);
    basic_mat[9]= -b/lambda;
    basic_mat[10]= c/v_mod;

    glMultMatrixd(basic_mat);

// Translate
    glTranslatef(-start_x,-start_y,-start_z);



// draw Line
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(start_x,start_y,start_z);
    glVertex3f(end_x,end_y,end_z);

    glEnd();


}



void drawObject()
{
      int ang,i;
      int delang = 10;
      float r[10] = {0.0,0.8,0.8,0.5,0.5,0.6,0.6,0.5,0.5,0.0};
      float y[10] = {0.0,0.0,0.15,0.15,0.8,0.8,1.0,1.0,0.9,0.9};
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




/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();

   light();

    loadMatrix();
    translate(basic_mat,trans_x,trans_y,trans_z);
    glMultMatrixd(basic_mat);  // Move right and into the screen



    loadMatrix();
    rotateX(basic_mat,xMode);
    glMultMatrixd(basic_mat);

    loadMatrix();
    rotateY(basic_mat,yMode);
    glMultMatrixd(basic_mat);

    loadMatrix();
    rotateZ(basic_mat,zMode);
    glMultMatrixd(basic_mat);

   gluLookAt(x,1.0f,z,  x+lx,center_y,z+lz, 0.0f,1.0,0.0f);


   glPushMatrix();
   loadMatrix();
   scale(basic_mat,0.2,0.2,0.2);
   glMultMatrixd(basic_mat);
   glTranslatef(0.0,1.0,0.0);
   drawTable();
   glPopMatrix();

   glPushMatrix();
   loadMatrix();
   scale(basic_mat,0.2,0.2,0.2);
   glMultMatrixd(basic_mat);
   glTranslatef(-5.0,0.5,-0.0);
   rotateAroundLine(-5.0,5.0,0.0,-1.0,-5.0,0.0);
   glRotatef(15,0.0,0.0,1.0);
   drawPlane();
   glPopMatrix();

   glPushMatrix();
   drawBed();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.58,0.0,0.0);
   drawTv();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0,-1.2,0.0);
   glScalef(5,.06,2.5);
   metarial_color_shine(0/MAX_INTENSITY,0/MAX_INTENSITY,80/MAX_INTENSITY,.1);
   drawBaseCube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0,0.7,-2.4);
   glScalef(5,2,0.1);
   metarial_color_shine(200/MAX_INTENSITY,119/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
   drawBaseCube();
   glPopMatrix();


   glPushMatrix();
   glTranslatef(5.0,0.7,-2.4);
   glScalef(0.1,2.0,5.0);
   metarial_color_shine(200/MAX_INTENSITY,119/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
   drawBaseCube();
   glPopMatrix();

   glPushMatrix();
   metarial_color_shine(255/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,1.0);
   glTranslated(0,-.12,0);
   glScaled(.27,.42,.27);
   drawObject();
   glPopMatrix();


   glPushMatrix();
   metarial_color_shine(255/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,100);
   glTranslated(2.0,0.0,0.0);
   glutSolidSphere(.2,100,100);
   glPopMatrix();


   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}



void my_keyboard(unsigned char k, int x, int y)
{
    float fraction = 0.1f;
    switch (k)
    {
        case 'I':  trans_y+=.5f; break;
        case 'J':  trans_x-=.5f; break;
        case 'K':  trans_y-=.5f; break;
        case 'L':  trans_x+=.5f; break;

        // Accessing x direction
        case 'X':   xMode+=0.1;
                    break;

        // Accessing y direction
        case 'Y':  yMode+=0.1;
                   break;
        // Accessing z direction
        case 'Z':  zMode+=0.1;
                   break;

        case 'x':  xMode-=0.1;
                   break;

        // Accessing y direction
        case 'y':  yMode-=0.1;
                   break;
        // Accessing z direction
        case 'z':  zMode-=0.1;
                   break;
        case 'q':
            exit(0);			// exit

        case ',':
            if(li_0==0)
                li_0=1;
            else
                li_0=0;
            break;

        case '.':
            if(amb==0)
                amb=1;
            else
                amb=0;
            break;

        case '/':
            if(diff==0)
                diff=1;
            else
                diff=0;
            break;

        case 'n':
            if(spec==0)
                spec=1;
            else
                spec=0;
            break;

        case '4' :
			angle -= 0.01f;
			lx = sin(angle);     // Polar Coordinate to Euclidean Coordinate
			lz = -cos(angle);
			break;
		case '6' :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case '8' :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case '5' :
			x -= lx * fraction;
			z -= lz * fraction;
			break;

        case '1':
            center_y += 0.01; break;
        case '0':
            center_y -= 0.01; break;


    }

    glutPostRedisplay();		// redraw the image now
}



void timer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(150, timer, 0); // next timer call milliseconds later
}



/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutKeyboardFunc(my_keyboard);
   glEnable(GL_LIGHTING);
   glutTimerFunc(0, timer, 0);          // First timer call immediately [NEW]

   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
