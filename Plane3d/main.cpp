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
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;
// Reference position of camera
float center_y = 1.0;



// Automatic Variable for  rotation
int automatic = 0;
float radius = 1.0;
// Reference point for rotation
float refer = 1.0;

//Basic Matrix
double basic_mat[16];

/*float eye_x = 0.0, eye_y = 0.0, eye_z = 0.0;
float center_x = 0.0, center_y = 0.0, center_z = -1.0;
float up_x = 0.0, up_y = 1.0, up_z = 0.0;*/

// Angle for plane rotation
float planeAngle = 0.0;


// Transforming Basic Matrix into identity
void loadMatrix()
{
    memset(basic_mat,0,sizeof(basic_mat));
    for(int i=0; i<16; i+=5)basic_mat[i]=1;
}


/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor((255/MAX_INTENSITY), (255/MAX_INTENSITY),(255/MAX_INTENSITY), 1.0f); // Set background color to black and opaque
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
    glColor3f(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,0.5f,0.5f,3.0f,32,32);
}


void drawCylinder2()
{
    glColor3f(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY);
    quadratic2 = gluNewQuadric();
    gluCylinder(quadratic,0.5f,0.1f,0.8f,32,32);
}


void drawWing()
{
    // Backwing left right
    glColor3f(255/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY);
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



void drawPlane()
{
    // Draw Base
    glPushMatrix();
    glColor3f(0.0,1.0,0.0);
    loadMatrix();
    translate(basic_mat,-2.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(90.0,0.0,1.0,0.0);
    drawCylinder();
    glPopMatrix();

    // Draw Head
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,0.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(-90.0,0.0,0.0,1.0);
    drawHalfSphere(30,30,.5);
    glPopMatrix();

    // Draw Tail
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-2.5,0.0,0.0);
    glMultMatrixd(basic_mat);
    glRotatef(-90.0,0.0,1.0,0.0);
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
    glColor3f(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY);

    // Base
    glPushMatrix();
    loadMatrix();
    translate(basic_mat,-1.5,-2.0,0.0);
    glMultMatrixd(basic_mat);
    loadMatrix();
    scale(basic_mat,6.0,0.3,4.0);
    glMultMatrixd(basic_mat);
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


    drawBaseCube();
    glPopMatrix();
}


void drawBed()
{
    //Base
    glPushMatrix();
    glColor3f(102/MAX_INTENSITY,51/MAX_INTENSITY,0/MAX_INTENSITY);
    glTranslatef(-2.3,-1.0,1.0);
    glScalef(0.4,0.2,1.0);
    drawBaseCube();
    glPopMatrix();

    //BedSheet
    glPushMatrix();
    glColor3f(255/MAX_INTENSITY,155/MAX_INTENSITY,0/MAX_INTENSITY);
    glTranslatef(-2.3,-0.8,1.0);
    glScalef(0.4,0.05,1.0);
    drawBaseCube();
    glPopMatrix();
}

void drawTv()
{
    glPushMatrix();
    glColor3f(128/MAX_INTENSITY,128/MAX_INTENSITY,128/MAX_INTENSITY);
    glTranslatef(2.3,0.8,1.0);
    glScalef(0.01,0.5,0.8);
    drawBaseCube();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY);
    glTranslatef(2.29,0.8,1.0);
    glScalef(0.01,0.45,0.75);
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





/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();


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
   drawTable();
   glPopMatrix();

   glPushMatrix();
    loadMatrix();
    scale(basic_mat,0.2,0.2,0.2);
    glMultMatrixd(basic_mat);
   rotateAroundLine(-5.0,5.0,0.0,-5.0,-5.0,0.0);
   drawPlane();
   glPopMatrix();

   glPushMatrix();
   drawBed();
   glPopMatrix();

   glPushMatrix();
   drawTv();
   glPopMatrix();

   glPushMatrix();
   glColor3f(220/MAX_INTENSITY,224/MAX_INTENSITY,224/MAX_INTENSITY);
   loadMatrix();
   scale(basic_mat,5,1.7,10);
   glMultMatrixd(basic_mat);
   drawAnotherCube();
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
        case 'X':  cout<<"X Mode Activated"<<endl;
                   xMode+=5.0;
                   break;

        // Accessing y direction
        case 'Y':  cout<<"Y Mode Activated"<<endl;
                   yMode+=5.0;
                   break;
        // Accessing z direction
        case 'Z':  cout<<"Z Mode Activated"<<endl;
                   zMode+=5.0;
                   break;

        case 'x':  cout<<"X Mode Activated"<<endl;
                   xMode-=5.0;
                   break;

        // Accessing y direction
        case 'y':  cout<<"Y Mode Activated"<<endl;
                   yMode-=5.0;
                   break;
        // Accessing z direction
        case 'z':  cout<<"Z Mode Activated"<<endl;
                   zMode-=5.0;
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

        case 'M':
            automatic = 1; break;

        case 'm':
            automatic = 0; break;

        case 'q':
            exit(0);			// exit
    }

    glutPostRedisplay();		// redraw the image now
}



void timer(int value)
{
    planeAngle+=5.0;
    if(automatic==1)
    {

        radius = sqrt(x*x+z*z);
        if((x+refer*.5)>=radius) refer=-1.0;
        else if(x+refer*.5<=(-radius)) refer=1.0;

        x = x+refer*.5;

        if(x<=radius && x>=-radius)
            z= -refer*sqrt(radius*radius-x*x);

        lx = -x;
        lz = -z;
    }
    //if(automatic==1)rotation+=5;
    //anglePyramid += 0.5f;
    //front_wheel+=10.0f;
    //back_wheel+=10.0f;
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
   glutTimerFunc(0, timer, 0);          // First timer call immediately [NEW]

   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
