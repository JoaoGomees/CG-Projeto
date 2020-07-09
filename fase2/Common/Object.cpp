
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include "Object.h"

Object::Object(std::string filename, std::vector<float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ)
{
    setObject (filename, rotations, tX, tY, tZ, sX, sY, sZ);
}

void Object::setObject (std::string filename, std::vector <float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ)
{
    _FILE = filename;
    _ROTATIONS = rotations;
    _TX = tX;
    _TY = tY;
    _TZ = tZ;
    _SX = sX;
    _SY = sY;
    _SZ = sZ;
}

std::string Object::getFilename()
{
    return _FILE;
}

std::vector <float> Object::getRotations()
{
    return _ROTATIONS;
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
