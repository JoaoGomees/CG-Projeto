#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "../headers/writer.h"
#include "../../Common/Point.h"


void writeFile (std::vector <Point> points,std::string fileName)
{
    std::ofstream outfile;
    outfile.open(fileName, std::ios::out | std::ios::trunc);
    
    //escrever os pontos para o ficheiro
    for(int i=0;i<points.size();i++)
    {
        outfile << points[i].to_string()
                << std::endl;
    }
    outfile.close();
}


