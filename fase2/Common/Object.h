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
    std::string _FILE;
    std::vector <float> _ROTATIONS;
    float _TX;
    float _TY;
    float _TZ;
    float _SX;
    float _SY;
    float _SZ;

public:
    
    Object (std::string filename, std::vector <float> rotations, float tX, float tY, float tZ, float sX, float sY, float sZ);
    
    std::string getFilename();
    std::vector <float> getRotations();
    float getTX ();
    float getTY ();
    float getTZ ();
    float getSX ();
    float getSY ();
    float getSZ ();

    void setObject (std::string filename, std::vector <float> rotations, float tX, float tY, float tZ,  float sX, float sY, float sZ);
    
};

#endif
