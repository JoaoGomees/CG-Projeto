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

    Point p5 (0.0f, 1.0f,0.0f); // normal é sempre igual num plano

	//textures
    Point t1(0.0f,1.0f,0.0f);
	Point t2(0.0f,0.0f,0.0f);
	Point t3(1.0f,1.0f, 0.0f);
	Point t4(1.0f,1.0f, 0.0f);
	Point t5(0.0f,0.0f, 0.0f);
	Point t6(1.0f,0.0f, 0.0f);

    //pontos
    points.push_back(p3);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p2);
    points.push_back(p1);
    points.push_back(p4);

    //normals
    points.push_back(p5);
    points.push_back(p5);
    points.push_back(p5);
    points.push_back(p5);
    points.push_back(p5);
    points.push_back(p5);

    // textures
    points.push_back(t1);
    points.push_back(t2);
    points.push_back(t3);
    points.push_back(t4);
    points.push_back(t5);
    points.push_back(t6);
    
    return points;
    
}
