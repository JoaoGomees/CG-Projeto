#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "../headers/reader.h"
#include "../../Common/Point.h"

void getPoint (std::string line, std::vector <Point>& Points)
{
    char delim[] = " ";
    char *token;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    int i = 0;

    token = strtok( &line[0], delim);
    while( token != NULL )
    {
        if (i == 0) x = std::stof(token,NULL);
        else if (i == 1) y = std::stof(token,NULL);
        else if (i == 2) z = std::stof(token,NULL);
        
       token = strtok( NULL, delim);
        i++;
    }
    
    Point p(x,y,z);
    Points.push_back(p);
}


std::vector <Point> readFile (std::string filename)
{
    std::vector <Point> Points;
    std::string line;
    std::ifstream file (filename);
    
    if (file.is_open())
    {
      while (getline (file,line))
      {
          getPoint(line,Points);
      }
      file.close();
    }
    return Points;
}

