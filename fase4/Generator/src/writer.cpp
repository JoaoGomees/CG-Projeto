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

			outfile << points[i+3].to_string()
					<< ' '
					<< points[i+4].to_string()
					<< ' '
					<< points[i+5].to_string()
					<< std::endl;

			outfile << points[i+6].to_string()
					<< ' '
					<< points[i+7].to_string()
					<< ' '
					<< points[i+8].to_string()
					<< std::endl;
            
            i += 9;
        }
        else{
            outfile << points[i].to_string()
                    << ' '
                    << points[i+1].to_string()
                    << ' '
                    << points[i+2].to_string()
                    << ' '
                    << points[i+3].to_string()
                    << ' '
                    << points[i+4].to_string()
                    << ' '
                    << points[i+5].to_string()
                    << std::endl;

			outfile << points[i+6].to_string()
                    << ' '
                    << points[i+7].to_string()
                    << ' '
                    << points[i+8].to_string()
                    << ' '
                    << points[i+9].to_string()
                    << ' '
                    << points[i+10].to_string()
                    << ' '
                    << points[i+11].to_string()
                    << std::endl;

			outfile << points[i+12].to_string()
                    << ' '
                    << points[i+13].to_string()
                    << ' '
                    << points[i+14].to_string()
                    << ' '
                    << points[i+15].to_string()
                    << ' '
                    << points[i+16].to_string()
                    << ' '
                    << points[i+17].to_string()
                    << std::endl;

            i += 18;
        }
    }
    outfile.close();
}


