#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include "../../Common/il.h"
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
float camXstart = radius * cos(beta) * sin(alfa), camYstart = radius * sin(beta), camZstart = radius * cos(beta) * cos(alfa);
int lightNumber = 0; // mantem track da proxima luz a ser usada, ate 8

GLuint indices, vertices, normais, texCoord, texID;
unsigned int indexCount;

std::vector <Object> l;
std::vector <float> answer, normals, textures;
std::vector<unsigned int> ind;
std::vector <float> rotation;
std::vector <std::vector <float> > translates;
float tX, tY, tZ;
float sX, sY, sZ;
int lSize;

std::string texture;
std::vector <float>  diff, spec, emis, amb;
std::vector <float> dirLightAux;
std::vector <float> pointLightAux;
std::vector <float> spotLightAux;

int figura = 0;
float camXnow = 0.0f, camYnow = 0.0f, camZnow = 0.0f;

void setUpLight ()
{
	//dar logo enable aos 8 luzes

    // fazer as directional lights first
    for (int i = 0; i < dirLightAux.size(); i += 3)
    {
		float pos [4] = {dirLightAux[i],dirLightAux[i+1],dirLightAux[i+2],0.0f};
		switch (lightNumber)
		{
			case 0:	glEnable(GL_LIGHT0);
					glLightfv(GL_LIGHT0, GL_POSITION, pos);
					lightNumber++;
					break;

			case 1:	glEnable(GL_LIGHT1);
					glLightfv(GL_LIGHT1, GL_POSITION, pos);
					lightNumber++;
					break;

			case 2:	glEnable(GL_LIGHT2);
					glLightfv(GL_LIGHT2, GL_POSITION, pos);
					lightNumber++;
					break;

			case 3:	glEnable(GL_LIGHT3);
					glLightfv(GL_LIGHT3, GL_POSITION, pos);
					lightNumber++;
					break;

			case 4:	glEnable(GL_LIGHT4);
					glLightfv(GL_LIGHT4, GL_POSITION, pos);
					lightNumber++;
					break;

			case 5:	glEnable(GL_LIGHT5);
					glLightfv(GL_LIGHT5, GL_POSITION, pos);
					lightNumber++;
					break;

			case 6:	glEnable(GL_LIGHT6);
					glLightfv(GL_LIGHT6, GL_POSITION, pos);
					lightNumber++;
					break;

			case 7:	glEnable(GL_LIGHT7);
					glLightfv(GL_LIGHT7, GL_POSITION, pos);
					lightNumber++;
					break;
		}

	}

	// fazer as point lights
	for (int i = 0; i < pointLightAux.size(); i += 4)
    {
		float pos [4] = {pointLightAux[i],pointLightAux[i+1],pointLightAux[i+2],1.0f};
		float atenuation = pointLightAux[i+3];
		switch (lightNumber)
		{
			case 0:	glEnable(GL_LIGHT0);
					glLightfv(GL_LIGHT0, GL_POSITION, pos);
					glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 1:	glEnable(GL_LIGHT1);
					glLightfv(GL_LIGHT1, GL_POSITION, pos);
					glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 2:	glEnable(GL_LIGHT2);
					glLightfv(GL_LIGHT2, GL_POSITION, pos);
					glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 3:	glEnable(GL_LIGHT3);
					glLightfv(GL_LIGHT3, GL_POSITION, pos);
					glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 4:	glEnable(GL_LIGHT4);
					glLightfv(GL_LIGHT4, GL_POSITION, pos);
					glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 5:	glEnable(GL_LIGHT5);
					glLightfv(GL_LIGHT5, GL_POSITION, pos);
					glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 6:	glEnable(GL_LIGHT6);
					glLightfv(GL_LIGHT6, GL_POSITION, pos);
					glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 7:	glEnable(GL_LIGHT7);
					glLightfv(GL_LIGHT7, GL_POSITION, pos);
					glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;
		}

	}

	// fazer as spotlights
	for (int i = 0; i < spotLightAux.size(); i += 9)
    {
		float pos [4] = {spotLightAux[i],spotLightAux[i+1],spotLightAux[i+2],1.0f};
		float dir [3] = {spotLightAux[i+3], spotLightAux[i+4], spotLightAux[i+5]};
		float atenuation = spotLightAux[i+6];
		float cut = spotLightAux[i+7];
		float exp = spotLightAux[i+8];

		switch (lightNumber)
		{
			case 0:	glEnable(GL_LIGHT0);
					glLightfv(GL_LIGHT0, GL_POSITION, pos);
					glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 1:	glEnable(GL_LIGHT1);
					glLightfv(GL_LIGHT1, GL_POSITION, pos);
					glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 2:	glEnable(GL_LIGHT2);
					glLightfv(GL_LIGHT2, GL_POSITION, pos);
					glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 3:	glEnable(GL_LIGHT3);
					glLightfv(GL_LIGHT3, GL_POSITION, pos);
					glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT3,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 4:	glEnable(GL_LIGHT4);
					glLightfv(GL_LIGHT4, GL_POSITION, pos);
					glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT4,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT4,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 5:	glEnable(GL_LIGHT5);
					glLightfv(GL_LIGHT5, GL_POSITION, pos);
					glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT5,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT5,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 6:	glEnable(GL_LIGHT6);
					glLightfv(GL_LIGHT6, GL_POSITION, pos);
					glLightfv(GL_LIGHT6,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT6,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT6,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;

			case 7:	glEnable(GL_LIGHT7);
					glLightfv(GL_LIGHT7, GL_POSITION, pos);
					glLightfv(GL_LIGHT7,GL_SPOT_DIRECTION,dir);
					glLightf(GL_LIGHT7,GL_SPOT_CUTOFF,cut);
					glLightf(GL_LIGHT7,GL_SPOT_EXPONENT,exp);
					glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, atenuation);
					lightNumber++;
					break;
		}

	}
}

int loadTexture(std::string s) {

    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;
	std::string path = "../../Texturas/";
	std::string nomeCompleto = path.append(s);
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)nomeCompleto.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1,&texID);

    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,    GL_TEXTURE_WRAP_S,        GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,    GL_TEXTURE_WRAP_T,        GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,    GL_TEXTURE_MAG_FILTER,       GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,    GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

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

void applyMaterial(){

    if(diff.size() > 0){
        float diffuse [4] = {diff[0], diff[1], diff[2], 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    }
    else{ 
        float diffuse [4] = {0.8f, 0.8f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    }

    if (spec.size() > 0)
    {
        float specular [4] = {spec[0], spec[1], spec[2], 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    }
    else{
        float specular [4] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    }

    if (emis.size() > 0)
    {
        float emission [4] = {emis[0], emis[1], emis[2], 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
    else{
        float emission [4] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }

    if (amb.size() > 0)
    {
        float ambient [4] = {amb[0], amb[1], amb[2], 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    }
    else{
        float ambient [4] = {0.2f, 0.2f, 0.2f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    }
}

void transformacoes(float * posic){
    // translate com catmull
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

        // guardar informaçao para fazer following
        posic[0] += pos[0];
        posic[1] += pos[1];
        posic[2] += pos[2];


        float m[16];
        getMatrix(deriv, m);
        //glMultMatrixf(m);
        //glRotatef(90, 0, 1, 0);
    }

    // translate normal
    glTranslatef(tX, tY, tZ);

    // guardar informaçao para fazer following
    posic[0] += tX;
    posic[1] += tY;
    posic[2] += tZ;

    // rotates
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

    //scale
    glScalef(sX, sY, sZ);
}

void preparaVBO(){
    //prepara vbo pontos
        glGenBuffers(1, &vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*answer.size(), &answer[0], GL_STATIC_DRAW);

        /* //prepara vbo indices
        glGenBuffers(1,&indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*ind.size(), ind.data(), GL_STATIC_DRAW);
        indexCount = ind.size();*/

        //prepara vbo das normals
        glGenBuffers(1, &normais);
		glBindBuffer(GL_ARRAY_BUFFER,normais);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);

    if(texture.size() > 0){
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    	//preparar vbo das textures
    	glGenBuffers(1, &texCoord);
    	glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textures.size(), &textures[0], GL_STATIC_DRAW);
    }
    else 
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void desenhaVBO(){
   
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);*/

    //normals
    glBindBuffer(GL_ARRAY_BUFFER,normais);
    glNormalPointer(GL_FLOAT,0,0);

    
    if(texture.size() > 0){
        //textures
        glBindTexture(GL_TEXTURE_2D, texID);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, textures.size()/2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, answer.size()/3);
    }


}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //tentativa de fixar a luz
 /*   gluLookAt(camXstart, camYstart, camZstart,
              0.0, 0.0, 0.0,
              0.0f,1.0f,0.0f);

    // set up lights
	setUpLight();       */
    
    // set the camera
    glLoadIdentity();
    gluLookAt(camX + distLeft - distRight + camXnow, camY - distUp + distDown + camYnow, camZ + distDentro - distFora + camZnow,
              0.0 + distLeft - distRight + camXnow, 0.0 - distUp + distDown + camYnow,0.0 + distDentro - distFora + camZnow,
              0.0f,1.0f,0.0f);

    // set up lights
	setUpLight(); 

    // draw list of objects
    float tempos[l.size()];
    for (int i = 0; i < l.size(); i++)
    {
        // make sure que está tudo limpo
        answer.clear();
        ind.clear();
        normals.clear();
        diff.clear(); spec.clear(); emis.clear(); amb.clear();
        textures.clear();
        texture = "";

        // retira informação
        translates = l[i].getTranslates();
        rotation = l[i].getRotations();
        tX = l[i].getTX();
        tY = l[i].getTY();
        tZ = l[i].getTZ();
        sX = l[i].getSX();
        sY = l[i].getSY();
        sZ = l[i].getSZ();

        std::vector <std::vector <float> > info = l[i].getPontos();
        answer = info[0];
        normals = info[1];

        std::vector <float> texturesAux = info[2];
        ind = l[i].getIndex();

		for (int i = 0; i < texturesAux.size(); i += 3)
		{
			textures.push_back(texturesAux[i]);
			textures.push_back(texturesAux[i+1]);
		}

        texture = l[i].getTextura();

        diff = l[i].getDiff();
        spec = l[i].getSpec();
        emis = l[i].getEmis();
        amb = l[i].getAmb();


        // implementa materiais
        applyMaterial();

        // prepara as vbos
        preparaVBO();

    	texID = loadTexture(texture);

        float posic[3] = {0,0,0};


        glPushMatrix();

        // transformaçoes geometricas
        transformacoes(posic);
        
        // desenhar vbos
        desenhaVBO();

        glPopMatrix();


        //fazer following
        if((i+1) == figura){
            camXnow = posic[0];
            camYnow = posic[1];
            camZnow = posic[2];
        }

        //escrever se está following
        char texto [50];
        if(figura == 0) sprintf(texto, "Normal view.");
        else sprintf(texto, "Following figure %d.", figura);
        glutSetWindowTitle(texto);
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

    case GLUT_KEY_F2: 
            distDentro += 3.0f;
        break;

    case GLUT_KEY_F1: 
            distFora += 3.0f; 
        break;
    
    case GLUT_KEY_F3: 
            radius += 30.0f; 
            alfa = 0.0f, beta = 0.5f, radius = 200.0f;
            distDentro = 0.0f, distFora = 0.0f, distUp = 0.0f, distDown = 0.0f, distRight = 0.0f, distLeft = 0.0f;
            figura = 0;
        break;
    
    case GLUT_KEY_F4:
            figura++;
            if(figura == lSize + 1) figura = 0;
            else{
                distRight = 0.0f;
                distLeft = 0.0f;
                distUp = 0.0f;
                distDown = 0.0f;
                distDentro = 0.0f;
                distFora = 0.0f;
            }
        break;
    }

    alpha = (alfa * 180) / 3.14; betta = (beta * 180) / 3.14; r = radius;
    camX = radius * cos(beta) * sin(alfa), camY = radius * sin(beta), camZ = radius * cos(beta) * cos(alfa);
}

void copyLight (std::vector <float> pointlight, std::vector <float> dirlight, std::vector <float> spotlight)
{
	if (pointlight.size() > 0)
	{
		for (int i = 0; i < pointlight.size(); i++)
			pointLightAux.push_back(pointlight[i]);
	}

	if (dirlight.size() > 0)
	{
		for (int i = 0; i < dirlight.size(); i++)
			dirLightAux.push_back(dirlight[i]);
	}

	if (spotlight.size() > 0)
	{
		for (int i = 0; i < spotlight.size(); i++)
			spotLightAux.push_back(spotlight[i]);
	}
}

int render(int argc, char **argv, std::vector <Object> files, std::vector <float> pointlight, std::vector <float> dirlight, std::vector <float> spotlight) {

    
    for (int i = 0; i < files.size(); i++)
        l.push_back(files[i]);
    
    lSize = l.size();
	copyLight(pointlight,dirlight,spotlight);

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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
	

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glEnable(GL_TEXTURE_2D);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
// enter GLUT's main cycle
    glutMainLoop();
    
    return 0;
}

