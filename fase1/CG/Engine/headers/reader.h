#ifndef reader_h
#define reader_h

#include <vector>
#include <string>
#include "Point.h"

//funcao que lê um file e devolve um vector de points a partir das coordenadas do ficheiro
std::vector <Point> readFile (std::string filename);

//funcao que recebe uma linha, vai lhe dar parse e criar os points
void getPoints (std::string line, std::vector <Point>& Points);

#endif
