#include <iostream>
#include <math.h>
#include "../headers/cone.h"
#include "../../Common/Point.h"


std::vector<Point> drawCone (float radius, float height, int slices, int stacks)
{
    std::vector <Point> Points;
    
    float angle = 0.0f;
    float inc = (float)360.0f / slices;
    float radiusDec = radius / stacks;
    float heightInc = height / stacks;
    
    for (int i = 0; i < slices; i++) {
        float _radius = radius;
        float _height = 0.0f;
        
        for (int j = 0; j < stacks; j++) {
            float rad1 = (angle * M_PI) / 180.0f;
            float rad2 = ((angle + inc) * M_PI) / 180.0f;
            
            float nextRadius = _radius - radiusDec;
            float nextHeight = _height + heightInc;
            
            if (j == 0) {
                
                Point p5 (0.0f,0.0f,0.0f);
                Point p6 (_radius * sin(rad1),0.0f,_radius * cos(rad1));
                Point p7 (_radius * sin(rad2),0.0f,_radius * cos(rad2));

                //guardar triangulo da base
                Points.push_back(p6);
                Points.push_back(p5);
                Points.push_back(p7);
                
            }
            
            
            Point p1 (_radius * sin(rad1),_height,_radius * cos(rad1));
            Point p2 (nextRadius * sin(rad2),nextHeight,nextRadius * cos(rad2));
            Point p3 (nextRadius * sin(rad1),nextHeight,nextRadius * cos(rad1));
            Point p4 (_radius * sin(rad2),_height,_radius * cos(rad2));
            
            Points.push_back(p3);
            Points.push_back(p1);
            Points.push_back(p2);
            Points.push_back(p4);
    
            _radius = nextRadius;
            _height += heightInc;
        }
            
        angle += inc;
    }
    
    return Points;
}
