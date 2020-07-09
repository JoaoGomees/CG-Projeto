#ifndef Object_h
#define Object_h

#include <string>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>

class Object
{
private:
    std::vector <float> _PONTOS;
    std::vector <unsigned int> _INDICES;
    std::vector <float> _ROTATIONS;
    std::vector <std::vector <float> > _TRANSLATES;
    float _TX;
    float _TY;
    float _TZ;
    float _SX;
    float _SY;
    float _SZ;

public:
    
    Object (std::vector <float> pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector <float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ);
    
    std::vector <float> getPontos();
    std::vector <unsigned int> getIndex();
    std::vector <float> getRotations();
    std::vector <std::vector <float> > getTranslates();
    float getTX ();
    float getTY ();
    float getTZ ();
    float getSX ();
    float getSY ();
    float getSZ ();

    void setObject (std::vector <float> pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector <float> rotations, float tX, float tY, float tZ,  float sX, float sY, float sZ);
    
};

#endif
