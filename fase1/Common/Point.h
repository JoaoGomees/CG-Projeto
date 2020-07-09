#ifndef Point_h
#define Point_h

#include <string>



class Point
{
private:
    float _X;
    float _Y;
    float _Z;

public:
    
    Point(float x, float y, float z);
    
    float getX ();
    float getY ();
    float getZ ();
    
    void setPoint (float x, float y, float z);
    
    std::string to_string ();
};

#endif


