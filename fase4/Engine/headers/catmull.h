#ifndef catmull_h
#define catmull_h

#include <vector>
#include <string>
#include <tuple>

void buildRotMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normalize(float* a);
void multMatrixVector(float* m, float* v, float* res);
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, int POINT_COUNT, float ** p);
void renderCatmullRomCurve(int POINT_COUNT, float** p);
void getMatrix(float* deriv, float* m);
void setPoints(std::vector <float> translate);


#endif /* catmull_h */
