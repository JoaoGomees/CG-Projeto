#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "../headers/reader.h"
#include "../../Common/Point.h"
#include "../../Common/Object.h"
#include "../headers/renderer.h"

float alfa = 0.0f, beta = 0.5f, radius = 200.0f;
std::vector <Point> answer;

std::vector <Object> l;
std::vector <float> rotation;
float tX, tY, tZ;
float sX, sY, sZ;

void getPoints(std::vector <Point>& points)
{
    for (int i = 0; i < points.size(); i++) {
        answer.push_back(points[i]);
    }
        

}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void draw (std::vector <Point> points)
{
    glPushMatrix();

    glTranslatef(tX, tY, tZ);
    
    for (int j = 0; j < rotation.size(); j += 4) {
        glRotatef(rotation[j], rotation[j+1], rotation[j+2], rotation[j+3]);
    }
    glScalef(sX, sY, sZ);    
   
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    for (int i = 0; i < points.size(); i += 3)
    {   
        glBegin(GL_TRIANGLES);
            
            glVertex3f(points[i].getX(), points[i].getY(), points[i].getZ());
            glVertex3f(points[i+1].getX(), points[i+1].getY(), points[i+1].getZ());
            glVertex3f(points[i+2].getX(), points[i+2].getY(), points[i+2].getZ());
        glEnd();
    }
  
    glPopMatrix();
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(radius * cos(beta) * sin(alfa),radius * sin(beta),radius * cos(beta) * cos(alfa),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);


    for (int i = 0; i < l.size(); i++)
    {
        answer.clear();
        rotation = l[i].getRotations();
        tX = l[i].getTX(); 
        tY = l[i].getTY();
        tZ = l[i].getTZ();
        sX = l[i].getSX(); 
        sY = l[i].getSY();
        sZ = l[i].getSZ();

        std::string fileName = "../../Demos/";
        std::vector <Point> points = readFile(fileName.append(l[i].getFilename()));
        getPoints(points);
        draw(answer);
    }
    //desenhar
    //draw(answer);
    
    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

    case GLUT_KEY_RIGHT:
        alfa -= 0.1; break;

    case GLUT_KEY_LEFT:
        alfa += 0.1; break;

    case GLUT_KEY_UP:
        beta += 0.1f;
        if (beta > 1.5f)
            beta = 1.5f;
        break;

    case GLUT_KEY_DOWN:
        beta -= 0.1f;
        if (beta < -1.5f)
            beta = -1.5f;
        break;

    case GLUT_KEY_F2: radius -= 30.0f;
        if (radius < 1.0f)
            radius = 1.0f;
        break;

    case GLUT_KEY_F1: radius += 30.0f; break;
    }
    glutPostRedisplay();

}

int render(int argc, char **argv, std::vector <Object> files) {


    for (int i = 0; i < files.size(); i++)
        l.push_back(files[i]);
    

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1500,1500);
    glutCreateWindow("CG@DI-UM");

    
// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    
// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
// enter GLUT's main cycle
    glutMainLoop();
    
    return 0;
}

