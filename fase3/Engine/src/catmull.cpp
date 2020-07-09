#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <tuple>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


# define POINT_COUNTS = 5;
// Points that make up the loop for catmull-rom interpolation
float pp[5][3] = { {-1,-1,0},{-1,1,0},{1,1,0},{0,0,0},{1,-1,0} };


void buildRotMatrix(float* x, float* y, float* z, float* m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}


void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

    // catmull-rom matrix
    float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                      { 1.0f, -2.5f,  2.0f, -0.5f},
                      {-0.5f,  0.0f,  0.5f,  0.0f},
                      { 0.0f,  1.0f,  0.0f,  0.0f} };

    // Compute A = M * P
    float aX[4], aY[4], aZ[4];

    float pX[4] = { p0[0], p1[0], p2[0], p3[0] };
    multMatrixVector(*m, pX, aX);

    float pY[4] = { p0[1], p1[1], p2[1], p3[1] };
    multMatrixVector(*m, pY, aY);

    float pZ[4] = { p0[2], p1[2], p2[2], p3[2] };
    multMatrixVector(*m, pZ, aZ);

    float tv[4] = { t * t * t, t * t, t, 1 };


    // Compute pos = T * A
    pos[0] = tv[0] * aX[0] + tv[1] * aX[1] + tv[2] * aX[2] + tv[3] * aX[3];
    pos[1] = tv[0] * aY[0] + tv[1] * aY[1] + tv[2] * aY[2] + tv[3] * aY[3];
    pos[2] = tv[0] * aZ[0] + tv[1] * aZ[1] + tv[2] * aZ[2] + tv[3] * aZ[3];

    // compute deriv = T' * A
    float tvl[4] = { 3 * t * t, 2 * t, 1, 0 };

    deriv[0] = tvl[0] * aX[0] + tvl[1] * aX[1] + tvl[2] * aX[2] + tvl[3] * aX[3];
    deriv[1] = tvl[0] * aY[0] + tvl[1] * aY[1] + tvl[2] * aY[2] + tvl[3] * aY[3];
    deriv[2] = tvl[0] * aZ[0] + tvl[1] * aZ[1] + tvl[2] * aZ[2] + tvl[3] * aZ[3];
}


void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, int POINT_COUNT, float** p) {

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}


void renderCatmullRomCurve(int POINT_COUNT, float** p) {

    // draw curve using line segments with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);

    for (float gt = 0.0; gt < 1; gt += 0.01) {
        float pos[3], deriv[3];

        getGlobalCatmullRomPoint(gt, pos, deriv, POINT_COUNT, p);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}


void getMatrix(float* deriv, float* m){
    normalize(deriv);
    float cr[3] = { 0, 1, 0 };
    float rY[3], rZ[3];
    cross(deriv, cr, rY);
    normalize(rY);
    cross(rY, cr, rZ);
    normalize(rZ);

    buildRotMatrix(deriv, rY, rZ, m);
}