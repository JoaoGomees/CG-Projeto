#include <iostream>
#include <math.h>
#include "../headers/cone.h"
#include "../../Common/Point.h"
#include <cmath>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

std::vector<Point> drawCone (float radius, float height, int slices, int stacks)
{
    std::vector <Point> Points;

    float beta = atan(height/radius);
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

                // pontos
                Point p5 (0.0f,0.0f,0.0f);
                Point p6 (_radius * sin(rad1),0.0f,_radius * cos(rad1));
                Point p7 (_radius * sin(rad2),0.0f,_radius * cos(rad2));

                Points.push_back(p6);
                Points.push_back(p5);
                Points.push_back(p7);

				//normals
				Point n1(0.0f,-1.0f,0.0f);

                Points.push_back(n1);
                Points.push_back(n1);
                Points.push_back(n1);

                //textures

                Point t1(0.0f,0.0f,0.0f);
                Point t2(i * (1.0f/slices),0.25f,0.0f);
                Point t3((i+1) * (1.0f/slices), 0.25f,0.0f);

                Points.push_back(t2);
                Points.push_back(t1);
                Points.push_back(t3);
                
            }
            
            //pontos
            Point p1 (_radius * sin(rad1),_height,_radius * cos(rad1));
            Point p2 (nextRadius * sin(rad2),nextHeight,nextRadius * cos(rad2));         
            Point p3 (nextRadius * sin(rad1),nextHeight,nextRadius * cos(rad1));
            Point p4 (_radius * sin(rad2),_height,_radius * cos(rad2));

			Points.push_back(p3);
            Points.push_back(p1);
            Points.push_back(p2);
            Points.push_back(p2);
            Points.push_back(p1);
			Points.push_back(p4);

			//normals

           	float* a = (float*) malloc(3*sizeof(float));
           	a[0] = cos(beta) * sin(rad1); a[1] = sin(beta); a[2] = cos(beta) * cos(rad1);
           	normalize(a);

		   	Point n2 (a[0],a[1],a[2]);
			Point n3 (a[0],a[1],a[2]);
			Point n6 (a[0],a[1],a[2]);
			a[0] = cos(beta) * sin(rad2); a[1] = sin(beta); a[2] = cos(beta) * cos(rad2);
           	normalize(a);
            Point n4 (a[0],a[1],a[2]);
			Point n5 (a[0],a[1],a[2]);
			Point n7 (a[0],a[1],a[2]);

			free(a);


			Points.push_back(n2);
			Points.push_back(n3);
			Points.push_back(n4);
			Points.push_back(n5);
			Points.push_back(n6);
			Points.push_back(n7);

			// textures
			Point t1 ( i      * (1.0f / slices), (j + 1) * (0.75f / stacks) + 0.25f, 0.0f);
			Point t2 ( i      * (1.0f / slices),  j      * (0.75f / stacks) + 0.25f, 0.0f);
			Point t3 ((i + 1) * (1.0f / slices), (j + 1) * (0.75f / stacks) + 0.25f, 0.0f);
			Point t4 ((i + 1) * (1.0f / slices),  j      * (0.75f / stacks) + 0.25f, 0.0f);


			Points.push_back(t1);
			Points.push_back(t2);
			Points.push_back(t3);
			Points.push_back(t3);
			Points.push_back(t2);
			Points.push_back(t4);
    
            _radius = nextRadius;
            _height += heightInc;
        }
            
        angle += inc;
    }
    
    return Points;
}
