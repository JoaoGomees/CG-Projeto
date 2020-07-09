#include <vector>
#include <string>
#include <iostream>
#include "../../Common/Point.h"

std::vector <Point> drawPatch(std::string fileName, float tesselation);
Point calcBezierCuva (Point point0, Point point1, Point point2, Point point3, float t);
std::vector <Point> calcPoints (std::vector <Point> points, std::string line, float tesselation);
