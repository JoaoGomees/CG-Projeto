#ifndef sphere_h
#define sphere_h
#include <iostream>
#include <vector>
#include "../../Common/Point.h"


float coordenadaX (float radius, float alpha, float beta);
float coordenadaY (float radius, float alpha, float beta);
float coordenadaZ (float radius, float alpha, float beta);

std::vector<Point> drawSphere (float radius, int slices, int stacks);

#endif
