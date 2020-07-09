#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../headers/sphere.h"
#include "../headers/cone.h"
#include "../headers/plane.h"
#include "../headers/box.h"
#include "../headers/writer.h"


void criaXML ()
{
    std::ofstream outfile;
    outfile.open("./config.xml", std::ios::out | std::ios::trunc);
            
    outfile << "<scene>" << std::endl;
    outfile << "</scene>" << std::endl;
        
    outfile.close();
}


int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        criaXML();
        
        if (strcmp(argv[1], "sphere") == 0)
        {
            float radius = std::stof (argv[2]);
            int slices = std::atoi(argv[3]);
            int stacks = std::atoi(argv[4]);
            
            std::string fileName = "./";
            
            std::vector<Point> points = drawSphere(radius, slices, stacks);
            writeFile(points, fileName.append(argv[5]));
        }
        
        else if (strcmp(argv[1], "cone") == 0)
        {
            float radius = std::stof (argv[2]);
            float height = std::stof (argv[3]);
            int slices = std::atoi(argv[4]);
            int stacks = std::atoi(argv[5]);
            
            std::string fileName = "./";
            
            std::vector<Point> points = drawCone(radius, height, slices, stacks);
            writeFile(points, fileName.append(argv[6]));
        }
        
        
        else if (strcmp(argv[1], "plane") == 0)
        {
            float dimension = std::stof (argv[2]);
            
            std::string fileName = "./";
            
            std::vector<Point> points = drawPlane(dimension);
            writeFile(points, fileName.append(argv[3]));
        }
        
        else if (strcmp(argv[1], "box") == 0)
        {
            float x = std::stof (argv[2]);
            float y = std::stof (argv[3]);
            float z = std::stof (argv[4]);
            
            std::string fileName = "./";
            
            std::vector<Point> points = drawBox(x,y,z);
            writeFile(points, fileName.append(argv[5]));
        }
        
        
    }
            
    return 0;
}
