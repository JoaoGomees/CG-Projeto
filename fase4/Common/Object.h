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
    std::vector <std::vector <float> > _PONTOS;
    std::vector <unsigned int> _INDICES;
    std::vector <float> _ROTATIONS;
    std::vector <std::vector <float> > _TRANSLATES;
    float _TX;
    float _TY;
    float _TZ;
    float _SX;
    float _SY;
    float _SZ;
    std::string _TEXTURA;
    std::vector <float> _DIFF;
    std::vector <float> _SPEC;
    std::vector <float> _EMIS;
    std::vector <float> _AMB;

public:
    
    Object (std::vector <std::vector <float> > pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector <float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ, std::string textura, std::vector <float> diff, std::vector <float> spec, std::vector <float> emis, std::vector <float> amb);
    
    std::vector <std::vector <float> > getPontos();
    std::vector <unsigned int> getIndex();
    std::vector <float> getRotations();
    std::vector <std::vector <float> > getTranslates();
    float getTX ();
    float getTY ();
    float getTZ ();
    float getSX ();
    float getSY ();
    float getSZ ();
    std::string getTextura();
    std::vector <float> getDiff();
    std::vector <float> getSpec();
    std::vector <float> getEmis();
    std::vector <float> getAmb();

    void setObject (std::vector <std::vector <float> > pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector <float> rotations, float tX, float tY, float tZ,  float sX, float sY, float sZ, std::string textura, std::vector <float> diff, std::vector <float> spec, std::vector <float> emis, std::vector <float> amb);
    
};

#endif
