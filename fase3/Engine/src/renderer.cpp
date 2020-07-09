#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "../headers/reader.h"
#include "../headers/catmull.h"
#include "../../Common/Point.h"
#include "../../Common/Object.h"
#include "../headers/renderer.h"


int startX, startY, tracking = 0;
float distRight = 0.0f;
float distLeft = 0.0f;
float distUp = 0.0f;
float distDown = 0.0f;
float distDentro = 0.0f;
float distFora = 0.0f;

float alfa = 0.0f, beta = 0.5f, radius = 200.0f;
float alpha = alfa, betta = beta, r = radius;
float camX = radius * cos(beta) * sin(alfa), camY = radius * sin(beta), camZ = radius * cos(beta) * cos(alfa);

GLuint indices;
unsigned int indexCount;

std::vector <Object> l;
std::vector <float> answer;
std::vector<unsigned int> ind;
std::vector <float> rotation;
std::vector <std::vector <float> > translates;
float tX, tY, tZ;
float sX, sY, sZ;
int lSize;

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


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX + distLeft - distRight, camY - distUp + distDown, camZ + distDentro - distFora,
              0.0 + distLeft - distRight,0.0 - distUp + distDown,0.0 + distDentro - distFora,
              0.0f,1.0f,0.0f);


    float tempos[l.size()];
    for (int i = 0; i < l.size(); i++)
    {
        answer.clear();
        ind.clear();
        
        translates = l[i].getTranslates();
        rotation = l[i].getRotations();
        tX = l[i].getTX();
        tY = l[i].getTY();
        tZ = l[i].getTZ();
        sX = l[i].getSX();
        sY = l[i].getSY();
        sZ = l[i].getSZ();
        answer = l[i].getPontos();
        ind = l[i].getIndex();

        //prepara vbo pontos
        GLuint vertices;
        glGenBuffers(1, &vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*answer.size(), &answer[0],GL_STATIC_DRAW);


        //prepara vbo indices
        glGenBuffers(1,&indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*ind.size(), ind.data(), GL_STATIC_DRAW);
        indexCount = ind.size();

        

        glPushMatrix();

        for(int k = 0; k < translates.size(); k++){
            float pos[3], deriv[3];
            std::vector<float> translate = translates[k];

            int ms = glutGet(GLUT_ELAPSED_TIME);
            float tempo = translate[0] * 1000;
            float t = ms / tempo;

            float** points = new float*[translate.size()];
            for(int j = 1, n = 0; j < translate.size(); n++, j+=3){
                points[n] = new float[3];
                points[n][0] = translate[j];
                points[n][1] = translate[j+1];
                points[n][2] = translate[j+2];

            }

            //renderCatmullRomCurve((translate.size()-1)/3, points);
            getGlobalCatmullRomPoint(t, pos, deriv, (translate.size()-1)/3, points);

            glTranslatef(pos[0], pos[1], pos[2]);

            float m[16];
            getMatrix(deriv, m);
            //glMultMatrixf(m);
            //glRotatef(90, 0, 1, 0);
        }

        glTranslatef(tX, tY, tZ);
    
        for (int j = 0; j < rotation.size(); j += 5) {
            if (!rotation[j])
                glRotatef(rotation[j+1], rotation[j+2], rotation[j+3], rotation[j+4]);
            else{
                int milisecs = glutGet(GLUT_ELAPSED_TIME);
                int time = rotation[j+1] * 1000;
                float ang = (360 * milisecs) / time;

                glRotatef(ang, rotation[j+2], rotation[j+3], rotation[j+4]);
            }
        }
        glScalef(sX, sY, sZ);
        

        //desenhar vbos
        glBindBuffer(GL_ARRAY_BUFFER, vertices);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);


        glPopMatrix();

    }

    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
    if(c == '-')
    {
        radius += 30.0f;
    }
    
    else if (c == '+')
    {
        radius -= 30.0f;
        if (radius < 1.0f)
            radius = 1.0f;
    }
    
    alpha = (alfa * 180) / 3.14; betta = (beta * 180) / 3.14; r = radius;
    camX = radius * cos(beta) * sin(alfa), camY = radius * sin(beta), camZ = radius * cos(beta) * cos(alfa);
    

}

void processMouseButtons(int button, int state, int xx, int yy)
{
    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            betta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }

}


void processMouseMotion(int xx, int yy)
{
    int deltaX, deltaY;
    int alfaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {

        alfaAux = alpha + deltaX;
        betaAux = betta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alfaAux = alpha;
        betaAux = betta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    radius = rAux; alfa = alfaAux * 3.14 / 180.0; beta = betaAux * 3.14 / 180.0;

    camX = rAux * sin(alfaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alfaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * sin(betaAux * 3.14 / 180.0);
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

    case GLUT_KEY_RIGHT:
            distLeft += 3.0f;; break;

    case GLUT_KEY_LEFT:
            distRight += 3.0f; break;

    case GLUT_KEY_UP:
            distDown += 3.0f;
        break;

    case GLUT_KEY_DOWN:
            distUp += 3.0f;
        break;

    case GLUT_KEY_F2: distDentro += 3.0f;
        break;

        case GLUT_KEY_F1: distFora += 3.0f; break;
    

    case GLUT_KEY_F3: radius += 30.0f; 
        alfa = 0.0f, beta = 0.5f, radius = 200.0f;
        distDentro = 0.0f, distFora = 0.0f, distUp = 0.0f, distDown = 0.0f, distRight = 0.0f, distLeft = 0.0f;
        break;
    }

    alpha = (alfa * 180) / 3.14; betta = (beta * 180) / 3.14; r = radius;
    camX = radius * cos(beta) * sin(alfa), camY = radius * sin(beta), camZ = radius * cos(beta) * cos(alfa);
}

int render(int argc, char **argv, std::vector <Object> files) {


    for (int i = 0; i < files.size(); i++)
        l.push_back(files[i]);
    
    lSize = l.size();

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1500,1500);
    glutCreateWindow("CG@DI-UM");

    #ifdef __APPLE__
    glewInit();
    #else
    glewInit();
    #endif
    
// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    
// mouse callbacks
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    
//  OpenGL settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    
// enter GLUT's main cycle
    glutMainLoop();
    
    return 0;
}

