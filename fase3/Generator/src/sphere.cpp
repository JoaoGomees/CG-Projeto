#include <iostream>
#include <math.h>
#include "../headers/sphere.h"
#include "../../Common/Point.h"

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
    
    float alphaInc =  360.0f/ (float) slices;
    float BetaInc = 180.0f / (float) stacks;
       
    float beta = -90.0f;
       
    for (int i = 0; i < stacks; i++) {
        float alpha = 0.0f;
        float nextBeta = beta + BetaInc;
           
        for (int j = 0; j < slices; j++) {
            float nextAlpha = alpha + alphaInc;
            Point p1 (coordenadaX(radius,alpha,beta),coordenadaY(radius,alpha,beta),coordenadaZ(radius,alpha,beta));
            Point p2 (coordenadaX(radius,nextAlpha,beta),coordenadaY(radius,nextAlpha,beta),coordenadaZ(radius,nextAlpha,beta));
            Point p3 (coordenadaX(radius,alpha,nextBeta),coordenadaY(radius,alpha,nextBeta),coordenadaZ(radius,alpha,nextBeta));
            Point p4 (coordenadaX(radius,nextAlpha,nextBeta),coordenadaY(radius,nextAlpha,nextBeta),coordenadaZ(radius,nextAlpha,nextBeta));
            
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);
        
            alpha = nextAlpha;
        }
        
        beta = nextBeta;
       }
    
    
    return points;
}

