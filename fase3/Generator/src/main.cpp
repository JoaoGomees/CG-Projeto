#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "../headers/sphere.h"
#include "../headers/cone.h"
#include "../headers/plane.h"
#include "../headers/box.h"
#include "../headers/writer.h"
#include "../headers/patch.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        
        if(strcmp(argv[1],"patch") == 0)
        {
            std::string patchFile (argv[2]);
            float tesselation = std::stof(argv[3]);
            std::string folder1 = "../../Patches/";
            std::string folder2 = "../../Demos/";
            
            std::vector <Point> points = drawPatch(folder1.append(patchFile),tesselation);
            writeFile(points,folder2.append(argv[4]),0);
        }
        
        else if (strcmp(argv[1], "sphere") == 0)
        {
            float radius = std::stof (argv[2]);
            int slices = std::atoi(argv[3]);
            int stacks = std::atoi(argv[4]);
            
            std::string fileName = "../../Demos/";
            
            std::vector<Point> points = drawSphere(radius, slices, stacks);
            writeFile(points, fileName.append(argv[5]), 0);
        }
        
        else if (strcmp(argv[1], "cone") == 0)
        {
            float radius = std::stof (argv[2]);
            float height = std::stof (argv[3]);
            int slices = std::atoi(argv[4]);
            int stacks = std::atoi(argv[5]);
            
            std::string fileName = "../../Demos/";
            
            std::vector<Point> points = drawCone(radius, height, slices, stacks);
            writeFile(points, fileName.append(argv[6]), stacks);
        }
        
        
        else if (strcmp(argv[1], "plane") == 0)
        {
            float dimension = std::stof (argv[2]);
            
            std::string fileName = "../../Demos/";
            
            std::vector<Point> points = drawPlane(dimension);
            writeFile(points, fileName.append(argv[3]), 0);
        }
        
        else if (strcmp(argv[1], "box") == 0)
        {
            float x = std::stof (argv[2]);
            float y = std::stof (argv[3]);
            float z = std::stof (argv[4]);
            float divisions = std::stof(argv[5]);
            
            std::string fileName = "../../Demos/";
            
            std::vector<Point> points = drawBox(x,y,z,divisions);
            writeFile(points, fileName.append(argv[6]), 0);
        }
        
        
    }
            
    return 0;
}
