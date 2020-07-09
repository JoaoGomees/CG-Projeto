#include "Point.h"
#include <iostream>
#include <sstream>

Point::Point (float x, float y, float z)
{
    setPoint (x,y,z);
}

void Point::setPoint (float x, float y, float z)
{
    _X = x;
    _Y = y;
    _Z = z;
}

float Point::getX()
{
    return _X;
}

float Point::getY()
{
    return _Y;
}

float Point::getZ()
{
    return _Z;
}

std::string Point::to_string ()
{
    std::ostringstream sstream;
    sstream
        << _X << ' '
        << _Y << ' '
        << _Z;
    return sstream.str();
}


