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
#include "reader.cpp"
#include "../../../Common/Point.h"

std::vector <Point> answer;

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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    for (int i = 0; i < points.size(); i += 3)
    {
        glBegin(GL_TRIANGLES);
            glColor3f(255.0f,255.0f,255.0f);
            glVertex3f(points[i].getX(),points[i].getY(),points[i].getZ());
            glVertex3f(points[i + 1].getX(),points[i + 1].getY(),points[i + 1].getZ());
            glVertex3f(points[i + 2].getX(),points[i + 2].getY(),points[i + 2].getZ());
        glEnd();
    }
  
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    
    draw(answer);

    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int render(int argc, char **argv, std::vector <std::string> files) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1500,1500);
    glutCreateWindow("CG@DI-UM");
    
    for (int i = 0; i < files.size(); i++)
    {
        std::string fileName = "./";
        std::vector <Point> points = readFile(fileName.append(files[i]));
        getPoints(points);
    }
    
    
    
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

