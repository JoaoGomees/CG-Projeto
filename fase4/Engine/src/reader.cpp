#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "../headers/reader.h"
#include "../../Common/Point.h"

std::vector<unsigned int> inds;
int lastInd = 0;

void getPoint (std::string line, std::vector <float>& Points)
{
    char delim[] = " ";
    char *token;
    int j = 0; //i=0;

    token = strtok( &line[0], delim);
    while( token != NULL )
    {   

        Points.push_back(std::stof(token,NULL));
        token = strtok( NULL, delim);


        j++;
    }
    
    inds.push_back(lastInd + 0);
    inds.push_back(lastInd + 1);
    inds.push_back(lastInd + 2);

    if (j > 9){
        inds.push_back(lastInd + 2);
        inds.push_back(lastInd + 1);
        inds.push_back(lastInd + 3);
        lastInd++;
    }

    lastInd += 3;
}

void getInfo(std::string line, std::vector <float>& inf)
{
    char delim[] = " ";
    char* token;

    token = strtok(&line[0], delim);
    while (token != NULL)
    {
        inf.push_back(std::stof(token, NULL));
        token = strtok(NULL, delim);
    }
}

std::vector <unsigned int> getIndex(){
    return inds;
}

std::vector <std::vector <float> > readFile (std::string filename)
{
    std::vector <std::vector <float> > info;
    std::vector <float> Points, Normals, Textures;
    std::string line;
    std::ifstream file (filename);
    
    inds.clear();
    lastInd = 0;

    if (file.is_open())
    {
      while (getline (file,line))
      {
          getPoint(line,Points);

          getline(file, line);
          getInfo(line, Normals);

          getline(file, line);
          getInfo(line, Textures);
      }
      file.close();
    }

    info.push_back(Points);
    info.push_back(Normals);
    info.push_back(Textures);
    return info;
}

