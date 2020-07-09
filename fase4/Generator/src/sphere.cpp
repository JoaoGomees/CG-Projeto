#include <iostream>
#include <math.h>
#include "../headers/sphere.h"
#include "../../Common/Point.h"

#define _USE_MATH_DEFINES
#include <math.h>

float coordenadaX(float radius, float alpha, float beta) {
    float answer = radius * cos(beta*M_PI / 180.0f) * sin (alpha*M_PI / 180.0f);
    return answer;
}

float coordenadaY(float radius, float alpha, float beta) {
    float answer = radius * sin (beta*M_PI / 180.0f);
    return answer;
}

float coordenadaZ(float radius, float alpha, float beta) {
    float answer = radius * cos(beta*M_PI / 180.0f) * cos (alpha*M_PI / 180.0f);
    return answer;
}

//função que calculas os vertices e os guarda num vetor. cada vetor corresponde a um ponto
std::vector<Point> drawSphere (float radius, int slices, int stacks)
{
    std::vector <Point> points;

    float currentSlice = 0.0f;
	float currentStack = 0.0f;
	float sliceInc = 1.0f/slices;
	float stacksInc = 1.0f/stacks;
    
    float alphaInc =  360.0f/ (float) slices;
    float BetaInc = 180.0f / (float) stacks;
       
    float beta = -90.0f;
       
    for (int i = 0; i < stacks; i++) {
        float alpha = 0.0f;
        float currentSlice = 0.0f;
        float nextBeta = beta + BetaInc;
        float nextStack = currentStack + stacksInc;
           
        for (int j = 0; j < slices; j++) {
            float nextAlpha = alpha + alphaInc;
            float nextSlice = currentSlice + sliceInc;
			// pontos
            Point p1 (coordenadaX(radius,alpha,beta),coordenadaY(radius,alpha,beta),coordenadaZ(radius,alpha,beta));
            Point p2 (coordenadaX(radius,nextAlpha,beta),coordenadaY(radius,nextAlpha,beta),coordenadaZ(radius,nextAlpha,beta));
            Point p3 (coordenadaX(radius,alpha,nextBeta),coordenadaY(radius,alpha,nextBeta),coordenadaZ(radius,alpha,nextBeta));
            Point p4 (coordenadaX(radius,nextAlpha,nextBeta),coordenadaY(radius,nextAlpha,nextBeta),coordenadaZ(radius,nextAlpha,nextBeta));
            
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p3);
            points.push_back(p2);
            points.push_back(p4);


			// normals
            Point p5 (coordenadaX(1,alpha,beta),coordenadaY(1,alpha,beta),coordenadaZ(1,alpha,beta));
            Point p6 (coordenadaX(1,nextAlpha,beta),coordenadaY(1,nextAlpha,beta),coordenadaZ(1,nextAlpha,beta));
            Point p7 (coordenadaX(1,alpha,nextBeta),coordenadaY(1,alpha,nextBeta),coordenadaZ(1,alpha,nextBeta));
            Point p8 (coordenadaX(1,nextAlpha,nextBeta),coordenadaY(1,nextAlpha,nextBeta),coordenadaZ(1,nextAlpha,nextBeta));

            points.push_back(p5);
            points.push_back(p6);
            points.push_back(p7);
            points.push_back(p7);
            points.push_back(p6);
            points.push_back(p8);

            Point t1(currentSlice,currentStack,0.0f);
            Point t2(nextSlice,currentStack,0.0f);
            Point t3(currentSlice,nextStack,0.0f);
            Point t4(currentSlice,nextStack,0.0f);
            Point t5(nextSlice,currentStack,0.0f);
            Point t6(nextSlice,nextStack,0.0f);

            points.push_back(t1);
            points.push_back(t2);
            points.push_back(t3);
            points.push_back(t4);
            points.push_back(t5);
            points.push_back(t6);

            currentSlice += sliceInc;
        
            alpha = nextAlpha;
        }
        
        beta = nextBeta;
        currentStack += stacksInc;
       }
    
    
    return points;
}

