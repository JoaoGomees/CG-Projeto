#ifndef reader_h
#define reader_h

#include <vector>
#include <string>
#include "../../Common/Point.h"

//funcao que lê um file e devolve um vector de points a partir das coordenadas do ficheiro
std::vector <float> readFile (std::string filename);

//funçao que devolve o vector de indexes criado no getPoint
std::vector <unsigned int> getIndex ();

//funcao que recebe uma linha, vai lhe dar parse e criar os points
void getPoint (std::string line, std::vector <float>& Points);

#endif
