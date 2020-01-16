//
//  main.cpp
//  Perlin
//
//  Created by Kyle Burns on 1/14/20.
//  Copyright © 2020 Kyle Burns. All rights reserved.
//


#include "Tile.h"
#include "MeshData.h"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0.0f;

float lx = 1.0f; float lz = 1.0f; float ly = 1.0f;

float x = 0.0; float z = 0.0f; float y = 8.0f;

float fraction = 0.6f;

Map n(100, 100, 8);
MeshData mesh(100, 100);
void processNormalKeys(unsigned char key, int x, int y)
{
    if ( key == 27 || key == 'q') exit(0);
    else if ( key == 'w' || key == 'W' )
    {
        y += ly * fraction;
    }
    else if ( key == 's' || key == 'S' ) y -= ly * fraction;
    glutPostRedisplay();
}

void processSpecialKeys(int key, int ex, int y)
{
    
    switch(key)
    {
        case GLUT_KEY_LEFT:
//            angle -= 0.05f;
//            lx = sin(angle);
//            lz = -cos(angle);
            x -= lx * fraction;
            break;
        case GLUT_KEY_RIGHT:
//            angle += 0.05f;
//            lx = sin(angle);
//            lz = -cos(angle);
            x += lx * fraction;
            break;
        case GLUT_KEY_UP:
//            z += lz * fraction;
//            x += lx * fraction;
            z -= lz * fraction;
            break;
        case GLUT_KEY_DOWN:
//            x -= lx * fraction;
//            z -= lz * fraction;
            z += lz * fraction;
            break;
    }
}

GLuint* textures;
void init()
{
    textures = new GLuint[n.w * n.h];
    *textures = 0;
    int counter = 0;
    for (int i = 0; i < n.h; i++)
    {
        for(int k = 0; k < n.w; k++, counter++)
        {
            textures[counter] = counter;
            glGenTextures(1, &textures[counter]);
            glBindTexture(GL_TEXTURE_2D, textures[counter]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n.tsize, n.tsize, 0, GL_RGB, GL_FLOAT, n.field[k][i]->pixels);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, n.tsize, n.tsize, GL_RGB, GL_FLOAT,  n.field[k][i]->pixels);
        }
    }
    
}
void renderScene(void)
{
//    glClearColor(0,0,0,1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
    //gluOrtho2D(0., 800.0, 0., 800.0);
//    gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
//    glPushMatrix();
//    glColor3f(1,1,1);
//
//    glTranslatef((float)(map.currentpos.x-map.start.x) / map.Win.x, (float)(map.start.y-map.currentpos.y) / map.Win.y , -1);
//
//    glutSolidSphere(.4, 10, 10);
//    glPopMatrix();
//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-2, 2, -2, 2, -1, 1); // don't know what the deal is with this
//    gluLookAt(1.0f, 20.0f, z, x + lx, 0.0f, z + lz, 0.0f, 1.0f, 0.0f);
    gluLookAt(z, 5.0, x, -1.0, -1.0f, -1.0, 0.0f, 1.0f, 0.0f);
    //glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0, 0, 20.0f, 0.0f, 5.0f, .0f, 0.0f, 1.0, 0.0f);
    int counter = 0;
    for ( int y = 0; y < n.h - 1; y++ )
        for ( int x = 0; x < n.w - 1; x++, counter += 6 )
        {
            
            glBegin(GL_TRIANGLES);
            glColor3f(n.field[x][y]->pixels[0].r, n.field[x][y]->pixels[0].g, n.field[x][y]->pixels[0].b );
            //    glVertex3f((float)(map.currentpos.x-map.start.x) / map.Win.x, (float)(map.start.y-map.currentpos.y) / map.Win.y, -5);
//            glVertex3f((float) 4 * x / n.w - 2.0f, 4 * (float) -y / n.h + 2.0f, mesh.triangles[counter]);
//            glVertex3f((float) 4 * (x + 1) / n.w - 2.0f, 4 * (float) (-y-1) / n.h + 2.0f, mesh.triangles[counter + 1]);
//            glVertex3f((float) 4 * x / n.w - 2.0f, 4 * (float) (-y-1) / n.h + 2.0f, mesh.triangles[counter + 2]);
//            glVertex3f((float) 4 * (x +1 ) / n.w - 2.0f, 4 * (float) (-y-1) / n.h + 2.0f, mesh.triangles[counter + 3]);
//            glVertex3f((float) 4 * x / n.w - 2.0f, 4 * (float) y / n.h + 2.0f, mesh.triangles[counter + 4]);
//            glVertex3f((float) 4 * (x + 1) / n.w - 2.0f, 4 * (float) y / n.h + 2.0f, mesh.triangles[counter + 5]);
            //std::cout << "x, y: " << x << ", " << y << "\n";
            glVertex3f((float) 4 * x / n.w - 2.0f, mesh.triangles[counter],  4 * (float) -y / n.h + 2.0f);
            //std::cout << "mesh.triangles[counter]: " << mesh.triangles[counter] << "\n";
            glVertex3f((float) 4 * (x + 1) / n.w - 2.0f, mesh.triangles[counter + 1], 4 * (float) (-y-1) / n.h + 2.0f);
            //std::cout << "mesh.triangles[counter + 1]: " << mesh.triangles[counter + 1] << "\n";
            glVertex3f((float) 4 * x / n.w - 2.0f, mesh.triangles[counter + 2], 4 * (float) (-y-1) / n.h + 2.0f);
            //std::cout << "mesh.triangles[counter + 2]: " << mesh.triangles[counter + 2] << "\n";
            
            
            //glEnd();
            //glColor3f(n.field[x][y]->pixels[0].r, n.field[x][y]->pixels[0].g, n.field[x][y]->pixels[0].b );
            //glBegin(GL_TRIANGLES);
            
            glVertex3f((float) 4 * (x + 1 ) / n.w - 2.0f, mesh.triangles[counter + 3], 4 * (float) (-y-1) / n.h + 2.0f);
            //std::cout << "mesh.triangles[counter + 3]: " << mesh.triangles[counter + 3] << "\n";
            glVertex3f((float) 4 * x / n.w - 2.0f, mesh.triangles[counter + 4], 4 * (float) -y / n.h + 2.0f);
            //std::cout << "mesh.triangles[counter + 4]: " << mesh.triangles[counter + 4] << "\n";
            glVertex3f((float) 4 * (x + 1) / n.w - 2.0f, mesh.triangles[counter + 5], 4 * (float) -y / n.h + 2.0f);
            std::cout << "mesh.triangles[counter + 5]: " << mesh.triangles[counter + 5] << "\n";
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
void display(void)
{
    int counter = 0;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    glColor3ub( 255, 255, 255 );
    glPointSize((float) 2 * n.Win.x/n.w);
    for (int y = 0; y < n.h; y ++)
        for (int x = 0; x < n.w; x++, counter++)
        {
            glBindTexture( GL_TEXTURE_2D, textures[counter] );
            glBegin(GL_POINTS);
            glTexCoord2f((float)4*x/n.w - 1.0f - (float) 2 / n.w, (float)4*y/n.h - 2.0f - (float) 2 / n.h);
            glVertex2f((float)4*x/n.w - 2.0f  - (float) 2 / n.w, (float)4*y/n.h - 2.0f - (float) 2 / n.h);
            glEnd();
        }
    glutSwapBuffers();
}

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
    //init();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

int main(int argc, char ** argv) {
    //out.open("debug.txt");
    run(argc, argv);

    std::cout << "Hello, World!\n";
    //out.close();
    return 1;
}
