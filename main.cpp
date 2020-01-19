//
//  main.cpp
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//


#include "Tile.h"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Shader.h"
#define PI 3.14159265


float angle = PI / 4; float theta = PI / 4; float a = 1.2f; float deltaAnglex = 0.0f; float deltaAngley = 0.0f;

int state;

float lx = a * sin(angle); float lz = - a * cos(angle); float ly = 0.0f;

float x = 0.0; float z = 0.0f; float y = 1.2f;

float fraction = 0.6f;
// Define sun location
float Sunx = 4.0f; float Suny = 2.0f; float Sunz = 0.0f;


Map n(400, 400, 4, 800, 800);
Shader shader(400, 400, 4);
void processNormalKeys(unsigned char key, int ex, int why)
{
    if ( key == 27 || key == 'q') exit(0);
    else if ( key == 'w' || key == 'W' )
    {
        x += a * sin(angle) * fraction; z += - a * cos(angle) * fraction;
    }
    else if ( key == 's' || key == 'S' )
    {
        x -= a * sin(angle) * fraction; z += a * cos(angle) * fraction;
    }
    else if ( key == 'a' || key == 'A' )
    {
        x += a * sin(angle - PI / 2) * fraction; z -= a * cos(angle - PI / 2) * fraction;
    }
    else if ( key == 'd' || key == 'D' )
    {
        x += a * sin(angle + PI / 2) * fraction; z -= a * cos(PI / 2 + angle) * fraction;;
    }
    else if ( key == 32 )
    {
        if ( glutGetModifiers() == GLUT_ACTIVE_SHIFT )
        {
            y -= fraction;
            a = y / tan(theta);
            lx = a * sin(angle);
            lz = - a * cos(angle);
        }
        else
        {
            y += fraction;
            a = y / tan(theta);
            lx = a * sin(angle);
            lz = - a * cos(angle);
        }
    }
    
    //glutPostRedisplay();
}

void mouseMove(int p, int q)
{
    if (state == GLUT_LEFT) return; // if mouse is outside of window, don't allow passive control
    deltaAnglex = (p - n.Win.x / 2.0f) * 0.001f;
    deltaAngley = (q - n.Win.y / 2.0f) * 0.001f;
   // this is like an airplane
//    x += a * sin(angle + deltaAngley) * .01;
//    z -= a * cos(angle + deltaAngley) * .01;
    if ( theta + deltaAngley >= PI / 2 || theta + deltaAngley <= 0.001 ) goto sec;
    a = y / tan(theta + deltaAngley);
    //theta += deltaAngley;
    sec:
    lx = a * sin(angle + deltaAnglex);
    lz = - a * cos(angle + deltaAnglex);
    //angle += deltaAnglex;
    
}

void mouseEntry(int s)
{
    state = s;
}

void processSpecialKeys(int key, int ex, int why)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            angle -= 0.05f;
            lx = a * sin(angle);
            lz = -a * cos(angle);
            break;
        case GLUT_KEY_RIGHT:
            angle += 0.05f;
            lx = a * sin(angle);
            lz = -a * cos(angle);
            break;
        case GLUT_KEY_UP:
            theta -= 0.05f;
            a = y / tan(theta);
            lx = a * sin(angle);
            lz = - a * cos(angle);
            break;
        case GLUT_KEY_DOWN:
            theta += 0.05f;
            a = y / tan(theta);
            lx = a * sin(angle);
            lz = - a * cos(angle);
           // std::cout << "theta, lx, lz, a: " << theta << ", " << lx << ", " << lz << ", " << a << "\n";
            break;
    }
}

//GLuint* textures;
//void init()
//{
//    textures = new GLuint[n.w * n.h];
//    *textures = 0;
//    int counter = 0;
//    for (int i = 0; i < n.h; i++)
//    {
//        for(int k = 0; k < n.w; k++, counter++)
//        {
//            textures[counter] = counter;
//            glGenTextures(1, &textures[counter]);
//            glBindTexture(GL_TEXTURE_2D, textures[counter]);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n.tsize, n.tsize, 0, GL_RGB, GL_FLOAT, n.field[k][i]->pixels);
//            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, n.tsize, n.tsize, GL_RGB, GL_FLOAT,  n.field[k][i]->pixels);
//        }
//    }
//
//}

void renderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-2, 2, -2, 2, -1, 1); // don't know what the deal is with this
//    gluLookAt(1.0f, 20.0f, z, x + lx, 0.0f, z + lz, 0.0f, 1.0f, 0.0f);
    gluLookAt(x, y + 1.2, z, x + lx, y, z + lz, 0.0f, 1.0f, 0.0f);
    //glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0, 0, 20.0f, 0.0f, 5.0f, .0f, 0.0f, 1.0, 0.0f);
    
    //draw sun
   glPushMatrix();
   glColor3f(246.0f / 255, 228.0f / 255, 123.0f / 255);
   glTranslatef(Sunx, Suny, Sunz); // move to sun location
   glutSolidSphere(.2f, 20, 20);
   glPopMatrix();
    
    for (int i = 0; i < 2 * (n.h - 1) * (n.w - 1); i++)
        {
            glBegin(GL_TRIANGLES);
            
            /* HERE change functions to accept parameters from the meshdata->vectex triangle objects.*/
            glColor3f(n.meshdata->vectex[i].color.r, n.meshdata->vectex[i].color.g, n.meshdata->vectex[i].color.b);
//
            glVertex3f(n.meshdata->vectex[i].vertices[0].x, n.meshdata->vectex[i].vertices[0].y, n.meshdata->vectex[i].vertices[0].z);
            //std::cout << "this: " << 4 * (float)n.meshdata->vectex[i].vertices[0].x / n.w - 2.0f << " color: " << n.meshdata->vectex[i].color.r << "\n";
            glVertex3f(n.meshdata->vectex[i].vertices[1].x, n.meshdata->vectex[i].vertices[1].y, n.meshdata->vectex[i].vertices[1].z);
            
            glVertex3f(n.meshdata->vectex[i].vertices[2].x, n.meshdata->vectex[i].vertices[2].y, n.meshdata->vectex[i].vertices[1].z);
            glEnd();
        }
    
    glutSwapBuffers();
    
   
    
    
}

//in case widow isn't square
void changeSize(int width, int height)
{
    if ( height == 0) height = 1;
    float ratio = (float) width / height;
    //use projection matrix
    glMatrixMode(GL_PROJECTION);
    //resets matrix
    glLoadIdentity();
    //set viewport to be entire window
    glViewport(0, 0, 2*width, 2*height);
    //set correct perspective
    gluPerspective(45, ratio, 1, 50);
    
    //glOrtho(0.0f, map.Win.x, map.Win.y, 0.0f, 0.0f, 1.0f); I can't figure out how it works.. possibly need ot use gldrawpixels?
    //get back to the modelview
    glMatrixMode(GL_MODELVIEW);
}
//void display(void)
//{
//    int counter = 0;
//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-2, 2, -2, 2, -1, 1);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glEnable( GL_TEXTURE_2D );
//    glColor3ub( 255, 255, 255 );
//    glPointSize((float) 2 * n.Win.x/n.w);
//    for (int y = 0; y < n.h; y ++)
//        for (int x = 0; x < n.w; x++, counter++)
//        {
//            glBindTexture( GL_TEXTURE_2D, textures[counter] );
//            glBegin(GL_POINTS);
//            glTexCoord2f((float)4*x/n.w - 1.0f - (float) 2 / n.w, (float)4*y/n.h - 2.0f - (float) 2 / n.h);
//            glVertex2f((float)4*x/n.w - 2.0f  - (float) 2 / n.w, (float)4*y/n.h - 2.0f - (float) 2 / n.h);
//            glEnd();
//        }
//    glutSwapBuffers();
//}

void test(void)
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
}
void run(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(n.Win.x, n.Win.y);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Perlin");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    
    glutPassiveMotionFunc(mouseMove);
    //glutMotionFunc(mouseMove);
    glutEntryFunc(mouseEntry);
    
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

int main(int argc, char ** argv) {
    //out.open("debug.txt");
    // apply shading to all tiles
    shader.Shade(Sunx, Suny, Sunz, n.meshdata);
    run(argc, argv);

    std::cout << "Hello, World!\n";
    //out.close();
    return 1;
}
