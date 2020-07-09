
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include "Object.h"

Object::Object(std::vector <std::vector <float> > pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector<float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ, std::string textura, std::vector <float> diff, std::vector <float> spec, std::vector <float> emis, std::vector <float> amb)
{
    setObject (pontos, indices, translates, rotations, tX, tY, tZ, sX, sY, sZ, textura, diff, spec, emis, amb);
}

void Object::setObject (std::vector <std::vector <float> > pontos, std::vector <unsigned int> indices, std::vector <std::vector <float> > translates, std::vector <float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ, std::string textura, std::vector <float> diff, std::vector <float> spec, std::vector <float> emis, std::vector <float> amb)
{
    _PONTOS = pontos;
    _INDICES = indices;
    _TRANSLATES = translates;
    _ROTATIONS = rotations;
    _TX = tX;
    _TY = tY;
    _TZ = tZ;
    _SX = sX;
    _SY = sY;
    _SZ = sZ;
    _TEXTURA = textura;
    _DIFF = diff;
    _SPEC = spec;
    _EMIS = emis;
    _AMB = amb;
}

std::vector <std::vector <float> > Object::getPontos()
{
    return _PONTOS;
}

std::vector <unsigned int> Object::getIndex()
{
    return _INDICES;
}

std::vector <float> Object::getRotations()
{
    return _ROTATIONS;
}

std::vector <std::vector <float> > Object::getTranslates()
{
    return _TRANSLATES;
}

float Object::getTX()
{
    return _TX;
}

float Object::getTY()
{
    return _TY;
}

float Object::getTZ()
{
    return _TZ;
}

float Object::getSX()
{
    return _SX;
}

float Object::getSY()
{
    return _SY;
}

float Object::getSZ()
{
    return _SZ;
}

std::string Object::getTextura()
{
    return _TEXTURA;
}

std::vector <float> Object::getDiff()
{
    return _DIFF;
}

std::vector <float> Object::getSpec()
{
    return _SPEC;
}

std::vector <float> Object::getEmis()
{
    return _EMIS;
}

std::vector <float> Object::getAmb()
{
    return _AMB;
}
