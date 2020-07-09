#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "../headers/writer.h"
#include "../../Common/Point.h"


void writeFile (std::vector <Point> points,std::string fileName, int stacks)
{
    std::ofstream outfile;
    outfile.open(fileName, std::ios::out | std::ios::trunc);
    
    //escrever os pontos para o ficheiro
    for(int i=0, j=0; i<points.size(); j++)
    {
        if(j==stacks+1) j = 0;

        if(stacks && j==0){
            outfile << points[i].to_string()
                    << ' '
                    << points[i+1].to_string()
                    << ' '
                    << points[i+2].to_string()
                    << std::endl;
            
            i += 3; 
        }
        else{
            outfile << points[i].to_string()
                    << ' '
                    << points[i+1].to_string()
                    << ' '
                    << points[i+2].to_string()
                    << ' '
                    << points[i+3].to_string()
                    << std::endl;

            i += 4; 
        }
    }
    outfile.close();
}


