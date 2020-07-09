#ifndef renderer_h
#define renderer_h

#include <vector>
#include <string>
#include "../../Common/Point.h"
#include "../../Common/Object.h"


void getPoints(std::vector <Point>& points);
void draw (std::vector <Point> points);
int render(int argc, char **argv, std::vector <Object> files, std::vector <float> pointlight, std::vector <float> dirlight, std::vector <float> spotlight);

#endif /* renderer_h */
