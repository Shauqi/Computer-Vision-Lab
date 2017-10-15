#include <windows.h>        // For MS Windows
#include <GL/glut.h>        // GLUT, include glu.h and gl.h
#include <bits/stdc++.h>    // For C and C++ functionalities
using namespace std;


/* Declaring function prototypes */
void firstCoordinate();
void secondCoordinate();
void thirdCoordinate();
void fourthCoordinate();


/* Global variables */
int co_ordinate=0;          // selecting co_ordinate
int translationMode=0;      // for giving access to translation
int rotationMode=0;      // for giving access to rotation
int mirrorMode=0;
int xMode=0;
int yMode=0;
int zMode=0;

/*
       2   |   3
           |
     ------|------
           |
       0   |   1
*/
double front_wheel=0.0;
double back_wheel=0.0;
const double MAX_INTENSITY=255.0;
const double DEG2RAD = 3.14159/180;
char title[] = "Toy Horse";                         // title if the window


double trans_x[4]= {0.0f,0.0f,0.0f,0.0f};           // translation in x-axis of corresponding co-ordinate
double trans_y[4]= {0.0f,0.0f,0.0f,0.0f};           // translation in y-axis of corresponding co-ordinate
double trans_z[4]= {-10.0f,-10.0f,-10.0f,-10.0f};   // translation in z-axis of corresponding co-ordinate

double angle_x[4]= {0.0f,0.0f,0.0f,0.0f};
double angle_y[4]= {180,0.0f,0.0f,180};
double angle_z[4]= {0.0f,0.0f,180,180};

int multiplier=1;

int refreshMills = 150;                             // refresh interval in milliseconds
int w;                                              // width of screen
int h;                                              // height of screen
double basic_mat[16];


/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor((232/MAX_INTENSITY), (230/MAX_INTENSITY), (209/MAX_INTENSITY), 1.0f);    // set background color to black and opaque
    glClearDepth(1.0f);                      // set background depth to farthest
    glEnable(GL_DEPTH_TEST);                 // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void loadMatrix()
{
    memset(basic_mat,0,sizeof(basic_mat));
    for(int i=0;i<16;i+=5)basic_mat[i]=1;
}

void restoreModes(){
    translationMode=0;
    mirrorMode=0;
    rotationMode=0;
    xMode=0;
    yMode=0;
    zMode=0;
}


void mirrorOperation(){
    for(int i=0;i<4;i++)
    {
    trans_x[i]=trans_x[co_ordinate];
    trans_y[i]=trans_y[co_ordinate];
    trans_z[i]=trans_z[co_ordinate];

    angle_x[i]=angle_x[co_ordinate];
    angle_y[i]=angle_y[co_ordinate];
    angle_z[i]=angle_z[co_ordinate];

    }

    if(co_ordinate==0){
        trans_x[1]*=-1;   trans_y[2]*=-1;  trans_x[3]*=-1;  trans_y[3]*=-1;

        double xa= angle_x[0],  ya= angle_y[0],  za= angle_z[0] ;
        angle_y[1]=-180-ya;  angle_x[2]=-180-xa;   angle_y[2]=-ya;     angle_x[3]=-180-xa;   angle_y[3]+=180;
    }

    else if(co_ordinate==1){
        trans_x[0]*=-1;   trans_x[2]*=-1;  trans_y[2]*=-1;  trans_y[3]*=-1;

        double xa= angle_x[1],  ya= angle_y[1],  za= angle_z[1] ;
        angle_y[0]=-180-ya;  angle_x[2]=-180-xa;   angle_y[2]+=acos(-1); angle_x[3]=-180-xa;   angle_y[3]=-ya;

    }

    else if(co_ordinate==2){
        trans_y[0]*=-1;   trans_x[1]*=-1;  trans_y[1]*=-1;  trans_x[3]*=-1;

        double xa= angle_x[2],  ya= angle_y[2],  za= angle_z[2] ;
        angle_y[3]=-180-ya;  angle_x[0]=-180-xa;   angle_y[0]=-ya;     angle_x[1]=-180-xa;   angle_y[1]+=180;
    }

    else if(co_ordinate==3){
        trans_x[0]*=-1;   trans_y[0]*=-1;  trans_y[1]*=-1;  trans_x[2]*=-1;
        double xa= angle_x[0],  ya= angle_y[0],  za= angle_z[0] ;
        angle_y[2]=-180-ya;  angle_x[1]=-180-xa;   angle_y[1]=-ya;     angle_x[0]=-180-xa;   angle_y[0]+=180;
    }

}


/* Drawing circle using LINE_LOOP */
void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}



/* Drawing circle using LINE_LOOP */
void drawWheel(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}
void drawBody()
{
    // Head
    glBegin(GL_POLYGON);
    glColor3f((39/MAX_INTENSITY), (34/MAX_INTENSITY), (28/MAX_INTENSITY));
    glVertex2f(-1.1f, 0.18f);
    glVertex2f(-1.1f, 2.0f);
    glVertex2f(-2.6f, 0.4f);
    glVertex2f(-2.6f, 0.18);

    glEnd();

    /* Body of Plane */
    glBegin(GL_POLYGON);
    glColor3f((39/MAX_INTENSITY), (34/MAX_INTENSITY), (28/MAX_INTENSITY));
    glVertex2f(-1.1f, 0.18f);/*1*/
    glVertex2f(-1.1f, 2.0f);//2
    glVertex2f(2.6f, 2.0f);//3
    glVertex2f(3.1f, 0.18f);//4
    glEnd();

    //window
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(-1.1f, 1.2f);
    glVertex2f(-1.1f, 1.6f);
    glVertex2f(-1.5f, 1.6f);
    glVertex2f(-1.9f, 1.2f);


    glEnd();


    //wing2
    glBegin(GL_POLYGON);
    glColor3f((136/MAX_INTENSITY), (0/MAX_INTENSITY), (21/MAX_INTENSITY));     // Red

    glVertex2f(-0.3f, 2.0f);
    glVertex2f(1.8f, 3.0f);
    glVertex2f(2.5f, 3.0f);
    glVertex2f(1.6f, 2.0f);

    glEnd();

    //wing1
    glBegin(GL_POLYGON);
    glColor3f((136/MAX_INTENSITY), (0/MAX_INTENSITY), (21/MAX_INTENSITY));     // Red

    glVertex2f(-0.5f, 0.9f);
    glVertex2f(1.5f, 0.9f);
    glVertex2f(3.0f, -0.7f);
    glVertex2f(2.4f, -0.7f);

    glEnd();



    /* Tail*/
    glBegin(GL_POLYGON);
    glColor3f((39/MAX_INTENSITY), (34/MAX_INTENSITY), (28/MAX_INTENSITY));     //Gray

    glVertex2f(2.6f, 2.0f);
    glVertex2f(3.1f, 0.18f);
    glVertex2f(4.5f, 3.0f);
    glVertex2f(3.5f, 3.0f);

    glEnd();




    /* Front Leg */
    glBegin(GL_POLYGON);
    glColor3f((39/MAX_INTENSITY), (34/MAX_INTENSITY), (28/MAX_INTENSITY));     // Red

    glVertex2f(-0.1f, 0.16f);
    glVertex2f(-0.1f, -1.38f);
    glVertex2f(0.1f, -1.38f);
    glVertex2f(0.1f, 0.16f);

    glEnd();


    /* Back leg */
    glBegin(GL_POLYGON);
    glColor3f((39/MAX_INTENSITY), (34/MAX_INTENSITY), (28/MAX_INTENSITY));     // Red

    glVertex2f(1.8f, -.32f);
    glVertex2f(1.6f, -.32f);
    glVertex2f(1.6f, -1.38f);
    glVertex2f(1.8f, -1.38f);

    glEnd();



    /* Base */
    glBegin(GL_POLYGON);
    glColor3f((136/MAX_INTENSITY), (0/MAX_INTENSITY), (21/MAX_INTENSITY));     // Red


    glVertex2f(-1.32f, -1.3f);
    glVertex2f(-1.32f, -1.7f);
    glVertex2f(2.9f, -1.7f);
    glVertex2f(2.9f, -1.3f);

    glEnd();



    /* Front wheel*/
    glPushMatrix();


    glTranslatef(-0.62f, -1.475f, 0);
    glRotatef(front_wheel, 0.0f, 0.0f, 1.0f);
    glTranslatef(.62f,1.475f, 0);


    glColor3f(0,0,0);
    drawWheel(-0.62f,-1.475f,0.4f,10000);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(-1.02f,-1.475f);
    glVertex2f(-0.22f,-1.475f);
    glVertex2f(-0.62f,-1.875f);
    glVertex2f(-0.62f,-1.075f);
    glEnd();

    glPopMatrix();




    /* Back wheel */
    glPushMatrix();

    glTranslatef(2.22f, -1.475f, 0.0f);
    glRotatef(back_wheel, 0.0f, 0.0f, 1.0f);
    glTranslatef(-2.22f,1.475f, 0);


    glColor3f(0,0,0);
    drawWheel(2.22f,-1.475f,0.4f,10000);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(1.82f,-1.475f);
    glVertex2f(2.62f,-1.475f);
    glVertex2f(2.22f,-1.875f);
    glVertex2f(2.22f,-1.075f);
    glEnd();
    glPopMatrix();

}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    firstCoordinate();
    secondCoordinate();
    thirdCoordinate();
    fourthCoordinate();
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}


void firstCoordinate()
{
    glViewport(0, 0, w/2, h/2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix


    glLoadIdentity();

    glTranslated(trans_x[0],trans_y[0],trans_z[0]);

    glRotated(angle_x[0],1,0,0);
    glRotated(angle_y[0],0,1,0);
    glRotated(angle_z[0],0,0,1);


    if(mirrorMode==1 && co_ordinate!=0)mirrorOperation();
    drawBody();

}


void secondCoordinate()
{
    glViewport(w/2, 0, w/2, h/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    loadMatrix();

    glTranslated(trans_x[1],trans_y[1],trans_z[1]);

    glRotated(angle_x[1],1,0,0);
    glRotated(angle_y[1],0,1,0);
    glRotated(angle_z[1],0,0,1);


    if(mirrorMode==1 && co_ordinate!=1)mirrorOperation();
    drawBody();
}


void thirdCoordinate()
{
    glViewport(0, h/2, w/2, h/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    loadMatrix();

    glTranslated(trans_x[2],trans_y[2],trans_z[2]);

    glRotated(angle_x[2],1,0,0);
    glRotated(angle_y[2],0,1,0);
    glRotated(angle_z[2],0,0,1);

    if(mirrorMode==1 && co_ordinate!=2)mirrorOperation();
    drawBody();
}


void fourthCoordinate()
{
    glViewport(w/2, h/2, w/2, h/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    loadMatrix();

    glTranslated(trans_x[3],trans_y[3],trans_z[3]);

    glRotated(angle_x[3],1,0,0);
    glRotated(angle_y[3],0,1,0);
    glRotated(angle_z[3],0,0,1);

    if(mirrorMode==1 &&co_ordinate!=3)mirrorOperation();
    drawBody();
}



/* Called back when timer expired */
void timer(int value)
{
    //anglePyramid += 0.5f;
    front_wheel+=10.0f;
    back_wheel+=10.0f;
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void my_keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {

    // Selecting Co-ordinate
    case '1':  co_ordinate=0; cout<<"1st ViewPort Selected"<<endl; restoreModes(); break;
    case '2':  co_ordinate=1; cout<<"2nd ViewPort Selected"<<endl; restoreModes(); break;
    case '3':  co_ordinate=2; cout<<"3rd ViewPort Selected"<<endl; restoreModes(); break;
    case '4':  co_ordinate=3; cout<<"4th ViewPort Selected"<<endl; restoreModes(); break;

    // Translate if translation mode is on
    case 'I':  if(translationMode==1)trans_y[co_ordinate]+=.5f; else cout<<"Select translation mode"<<endl; break;
               if(mirrorMode==1)trans_y[co_ordinate]+=.5f; else cout<<"Select translation mode"<<endl; break;

    case 'J':  if(translationMode==1)trans_x[co_ordinate]-=.5f; else cout<<"Select translation mode"<<endl; break;
    case 'K':  if(translationMode==1)trans_y[co_ordinate]-=.5f; else cout<<"Select translation mode"<<endl; break;
    case 'L':  if(translationMode==1)trans_x[co_ordinate]+=.5f; else cout<<"Select translation mode"<<endl; break;

    // Accessing rotation
    case 'R':  if(rotationMode==0){rotationMode=1;  cout<<"Rotation Mode Activated"<<endl;}
               else {rotationMode=0;   cout<<"Rotation Mode Deactivated"<<endl;}
               break;

    // Accessing translation
    case 'T':  if(translationMode==0){translationMode=1;   cout<<"Translation Mode Activated"<<endl;}
               else {translationMode=0;    cout<<"Translation Mode Deactivated"<<endl;}
               break;

    // Accessing x direction
    case 'X':
               if(rotationMode==1){
               cout<<"X Mode Activated"<<endl;
               xMode=1;  yMode=0;   zMode=0;}
               else cout<<"Select Rotation Mode"<<endl;
               break;

    // Accessing y direction
    case 'Y':  if(rotationMode==1){
               cout<<"Y Mode Activated"<<endl;
               xMode=0;  yMode=1;   zMode=0;}
               else cout<<"Select Rotation Mode"<<endl;
               break;
    // Accessing z direction
    case 'Z':  if(rotationMode==1){
               cout<<"Z Mode Activated"<<endl;
               xMode=0;  yMode=0;   zMode=1;}
               else cout<<"Select Rotation Mode"<<endl;
               break;


    // Rotating clockwise
    case 'c':   if(rotationMode==1)
                {
                    if(xMode==1){
                        angle_x[co_ordinate] -= 5;
                    }
                    else if(yMode==1){
                        angle_y[co_ordinate] -= 5;
                    }
                    else if(zMode==1){
                        angle_z[co_ordinate] -= 5;
                    }
                    else cout<<"Select x,y or z mode"<<endl;
                }
                else cout<<"Select rotation mode"<<endl;
                break;

    //counter counter-clockwise
    case 'C':   if(rotationMode==1)
                {
                    if(xMode==1){
                        angle_x[co_ordinate] += 5;
                    }
                    else if(yMode==1){
                        angle_y[co_ordinate] += 5;
                    }
                    else if(zMode==1){
                        angle_z[co_ordinate] += 5;
                    }
                    else cout<<"Select x,y or z mode"<<endl;
                }
                else cout<<"Select rotation mode"<<endl;
                break;

    // Flip operation
    case 'F':
            cout<<"Flip Mode Activated"<<endl;
            angle_y[co_ordinate]+=180;
        break;

    // Mirror operation
    case 'M':
            cout<<"Mirror Mode Activated"<<endl;
            mirrorMode=1;

            mirrorOperation();

        /*
        trans_x[(co_ordinate+1)%4]=-trans_x[co_ordinate];
        trans_y[(co_ordinate+2)%4]=-trans_y[co_ordinate];

        trans_x[(co_ordinate+3)%4]=-trans_x[co_ordinate];
        trans_y[(co_ordinate+3)%4]=-trans_y[co_ordinate];
        */


/*
        angle_y[(co_ordinate+1)%4]-=acos(-1);
        angle_y[(co_ordinate+2)%4]+=acos(-1);
        angle_y[(co_ordinate+3)%4]+=0;

        angle_z[(co_ordinate+1)%4]+=0;
        angle_z[(co_ordinate+2)%4]+=acos(-1);
        angle_z[(co_ordinate+3)%4]+=acos(-1);
*/
        break;


    case 'q':
        exit(0);			// exit
    }

    glutPostRedisplay();		// redraw the image now
}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)    // GLsizei for non-negative integer
{
    // Compute aspect ratio of the new window
    w=width;
    h=height;
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
int main(int argc, char** argv)
{
    glutInit(&argc, argv);               // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);    // Enable double buffered mode
    glutInitWindowSize(640, 480);        // Set the window's initial width & height
    glutInitWindowPosition(50, 50);      // Position the window's initial top-left corner
    glutCreateWindow(title);             // Create window with the given title
    glutDisplayFunc(display);            // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);            // Register callback handler for window re-size event
    glutKeyboardFunc(my_keyboard);		// call keyboard() when key is hit
    initGL();                            // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);          // First timer call immediately [NEW]
    glutMainLoop();                      // Enter the infinite event-processing loop
    return 0;
}
