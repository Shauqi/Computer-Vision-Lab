#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <bits/stdc++.h>
#include <windows.h>        // For MS Windows
#include <GL/glut.h>        // GLUT, include glu.h and gl.h

using namespace std;

const double MAX_INTENSITY=255.0;
/* Drawing circle using LINE_LOOP */
void drawWheel(float cx, float cy, float cz, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, y + cy, cz);//output vertex
    }
    glEnd();
}


void drawCube(double tr_x, double tr_y,  double bl_x, double bl_y,  double front_z, double back_z)
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_INDEX_ARRAY );

    GLfloat vertices[] = {tr_x,  tr_y,  front_z, // front top right corner
                          bl_x,  tr_y,  front_z, // front top left corner
                          bl_x,  bl_y,  front_z, // front bottom left corner
                          tr_x,  bl_y,  front_z, // back bottom right corner
                          tr_x,  tr_y,  back_z,  // back top right corner
                          bl_x,  tr_y,  back_z,  // back top left corner
                          bl_x,  bl_y,  back_z,  // back bottom left corner
                          tr_x,  bl_y,  back_z   // back bottom right corner
                         }; // bottom right corner

    GLubyte indices[] = {0,1,2,3, // first triangle (bottom left - top left - top right)
                         4,0,3,7,
                         4,5,6,7,
                         1,5,6,2,
                         0,4,5,1,
                         2,6,7,3
                        }; // second triangle (bottom left - top right - bottom right)

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
}




void drawCube(double tr_x, double tr_y,  double bl_x, double bl_y,  double front_z, double back_z, int i)
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_INDEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY);

    float vertexColors[24] = {  // An RGB color value for each vertex
           228/MAX_INTENSITY,228/MAX_INTENSITY,228/MAX_INTENSITY,   228/MAX_INTENSITY,228/MAX_INTENSITY,228/MAX_INTENSITY,   0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,   228/MAX_INTENSITY,228/MAX_INTENSITY,228/MAX_INTENSITY,   0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,   228/MAX_INTENSITY,228/MAX_INTENSITY,228/MAX_INTENSITY,   0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,   0/MAX_INTENSITY,0/MAX_INTENSITY,0/MAX_INTENSITY,};

    GLfloat vertices[] = {tr_x,  tr_y,  front_z, // front top right corner
                          bl_x,  tr_y,  front_z, // front top left corner
                          bl_x,  bl_y,  front_z, // front bottom left corner
                          tr_x,  bl_y,  front_z, // back bottom right corner
                          tr_x,  tr_y,  back_z,  // back top right corner
                          bl_x,  tr_y,  back_z,  // back top left corner
                          bl_x,  bl_y,  back_z,  // back bottom left corner
                          tr_x,  bl_y,  back_z   // back bottom right corner
                         }; // bottom right corner

    GLubyte indices[] = {0,1,2,3, // first triangle (bottom left - top left - top right)
                         4,0,3,7,
                         4,5,6,7,
                         1,5,6,2,
                         0,4,5,1,
                         2,6,7,3
                        }; // second triangle (bottom left - top right - bottom right)

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer( 3, GL_FLOAT, 0, vertexColors );
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_COLOR_ARRAY);
}

void my_pyramid(double x1,double y1,double z1,
             double x2,double y2,double z2,
             double x3,double y3,double z3,
             double x4,double y4,double z4,
             double x5,double y5,double z5)
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_INDEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    GLfloat vertices[] = {
          x1,  y1,  z1,
          x2,  y2,  z2,
          x3,  y3,  z3,
          x4,  y4,  z4,
          x5,  y5,  z5
    };

    GLubyte indices[] = {0,1,2,
                         0,2,3,
                         0,3,4,
                         0,4,1
                        };

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_COLOR_ARRAY);
}


#endif // SHAPE_H_INCLUDED
