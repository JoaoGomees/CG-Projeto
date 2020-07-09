#include <iostream>
#include "../headers/plane.h"
#include "../../Common/Point.h"


std::vector<Point> drawPlane (float dimension)
{
    std::vector <Point> points;
    float aux = dimension / 2.0f;
    
    Point p1 (-aux,0.0f, aux);
    Point p2 ( aux,0.0f,-aux);
    Point p3 (-aux,0.0f,-aux);
    Point p4 ( aux,0.0f, aux);
    //guardar triangulo 1
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    
    //guardar triangulo 2
    points.push_back(p1);
    points.push_back(p4);
    points.push_back(p2);
    
    return points;
    
}
