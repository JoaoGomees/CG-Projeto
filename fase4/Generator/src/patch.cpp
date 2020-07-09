#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include "../../Common/Point.h"
#include "../headers/patch.h"

std::vector <Point> drawPatch(std::string fileName, float tesselation)
{
    
    std::string line;
    std::ifstream file (fileName);
    std::vector <float> pointsF;
    char delim[] = ", ";
    char *token;
    int numberPatches;
    int numberPatches2;
    
    
    if (file.is_open())
    {
        //busca a linha que tem o numero de patches
        getline (file,line);
        numberPatches = std::atoi(line.c_str());
        numberPatches2 = numberPatches;
        
        
        //passamos para a frente as linhas com os patches
        while(getline (file,line) && numberPatches > 0)
        {
            numberPatches--;
        }
        
        //estamos nas linhas que contém os pontos
        while(getline (file,line))
        {
            token = strtok(&line[0],delim);
            
            while(token != NULL)
            {
                pointsF.push_back(std::stof(token,NULL));
                token = strtok(NULL,delim);
            }
        }
         
        file.close();
    }
    
    
    //neste ponto, o vector pointsF ja tem os floats todos
    std::vector <Point> points;
    
    for(int i = 0; i < pointsF.size(); i+=3)
    {
        Point p1 (pointsF[i],pointsF[i+1],pointsF[i+2]);
        points.push_back(p1);
    }

    
    //neste ponto o vector points já agrupou os floats todos em Point e guardou-os.    
    std::ifstream file2 (fileName);
    std::vector <Point> pointsReal; // vetor que vai conter os pontos para desenhar os triangulos
    if (file2.is_open())
    {
        //da skip à primeira linha
        getline(file2,line);
        
        while(getline(file2,line) && numberPatches2 > 0)
        {
            std::vector <Point> auxx = calcPoints(points,line, tesselation);
            numberPatches2--;
            for (int i = 0; i < auxx.size(); i++)
            {
                pointsReal.push_back(auxx[i]);
            }
                
        }
    }
    
    return pointsReal;
}

//funcao auxiliar que vai recebe 4 pontos, um float t e devolve o valor da curve de Belzier formada pelos 4 pontos em funçao do valor t
// t tem de obedecer à condiçao 0 <= t <= 1

Point calcBezierCuva (Point point0, Point point1, Point point2, Point point3, float t)
{
    float x = t*t*t*point3.getX() + 3*t*t*(1-t)*point2.getX() + 3*t*(1-t)*(1-t)*point1.getX() + (1-t)*(1-t)*(1-t)*point0.getX();
    float y = t*t*t*point3.getY() + 3*t*t*(1-t)*point2.getY() + 3*t*(1-t)*(1-t)*point1.getY() + (1-t)*(1-t)*(1-t)*point0.getY();
    float z = t*t*t*point3.getZ() + 3*t*t*(1-t)*point2.getZ() + 3*t*(1-t)*(1-t)*point1.getZ() + (1-t)*(1-t)*(1-t)*point0.getZ();
    
    Point result (x,y,z);
    return result;
}

//funcao que vai calcular os pontos dos triangulos para desenhar
std::vector <Point> calcPoints (std::vector <Point> points, std::string line, float tesselation)
{
    std::vector <Point> pointsAux;
    std::vector <Point> result;
    
    char delim[] = ", ";
    char *token;
    token = strtok(&line[0],delim);
    
    while(token != NULL)
    {
        int index = std::atoi(token);
        pointsAux.push_back(points[index]);
        token = strtok(NULL,delim);
    }
    
    //loop que vai percorrer as varias divisoes consoante o numero de tesselation dado pelo user
    float divisions = 1.0f / tesselation;
    
    for (float i = 0.0f; i < 1.0f; i += divisions)
    {
        float nextI = i + divisions;
        //calcular os pontos para os triangulos
        Point pi0 = calcBezierCuva(pointsAux[0],pointsAux[1],pointsAux[2],pointsAux[3],i);
        Point pi1 = calcBezierCuva(pointsAux[0],pointsAux[1],pointsAux[2],pointsAux[3],nextI);
        Point pi2 = calcBezierCuva(pointsAux[4],pointsAux[5],pointsAux[6],pointsAux[7],i);
        Point pi3 = calcBezierCuva(pointsAux[4],pointsAux[5],pointsAux[6],pointsAux[7],nextI);
        Point pi4 = calcBezierCuva(pointsAux[8],pointsAux[9],pointsAux[10],pointsAux[11],i);
        Point pi5 = calcBezierCuva(pointsAux[8],pointsAux[9],pointsAux[10],pointsAux[11],nextI);
        Point pi6 = calcBezierCuva(pointsAux[12],pointsAux[13],pointsAux[14],pointsAux[15],i);
        Point pi7 = calcBezierCuva(pointsAux[12],pointsAux[13],pointsAux[14],pointsAux[15],nextI);
        
        for(float v = 0.0f; v < 1.0f; v += divisions)
        {
            float nextV = v + divisions;
            Point pv0 = calcBezierCuva(pi0,pi2,pi4,pi6,v);
            Point pv1 = calcBezierCuva(pi0,pi2,pi4,pi6,nextV);
            Point pv2 = calcBezierCuva(pi1,pi3,pi5,pi7,v);
            Point pv3 = calcBezierCuva(pi1,pi3,pi5,pi7,nextV);
            
            result.push_back(pv0);
            result.push_back(pv2);
            result.push_back(pv1);
            result.push_back(pv3);
        }
        
        
        
    }
    
    return result;
    
}





