#include <iostream>
#include "../../Common/Point.h"
#include "../headers/box.h"


std::vector<Point> drawBox(float largura, float comprimento, float profundidade, float divisions)
{
    //largura - esquerda direita
    //comprimento - frente trás
    //profundida - cima baixo
    
    std::vector <Point> points;
    divisions = divisions + 1;
    float lado = largura / divisions;
    float up = comprimento / divisions;
    float dentro = profundidade / divisions;

    float c = -(comprimento / 2.0f);

    for (int i = 0; i < divisions; i++) {

        float l = -(largura / 2.0f);
        float dc = c + up;

        for (int j = 0; j < divisions; j++) {

            float p = -(profundidade / 2.0f);
            float dl = l + lado;

            for (int k = 0; k < divisions; k++) {

                float dp = p + dentro;

                if (i == 0) {
                    Point p1(dl, c, dp);
                    Point p2(l, c, p);
                    Point p3(dl, c, p);
                    Point p4(l, c, dp);
                    
                    points.push_back(p3);
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p4);
                    
                }

                if (i == (divisions - 1)) {
                    Point p5(dl, dc, dp);
                    Point p6(dl, dc, p);
                    Point p7(l, dc, p);
                    Point p8(l, dc, dp);
                    
                    points.push_back(p6);
                    points.push_back(p7);
                    points.push_back(p5);
                    points.push_back(p8);
                }

                if (j == 0) {
                    
                    Point p9(l, c, dp);
                    Point p10(l, dc, p);
                    Point p11(l, c, p);
                    Point p12(l, dc, dp);
                    
                    points.push_back(p11);
                    points.push_back(p9);
                    points.push_back(p10);
                    points.push_back(p12);
                
                }

                if (j == (divisions - 1)) {
                   
                    Point p13(dl, c, p);
                    Point p14(dl, dc, p);
                    Point p15(dl, dc, dp);
                    Point p16(dl, c, dp);
                    
                    points.push_back(p14);
                    points.push_back(p15);
                    points.push_back(p13);
                    points.push_back(p16);
                }

                if (k == 0) {
                    
                    Point p17(dl, dc, p);
                    Point p18(l, c, p);
                    Point p19(l, dc, p);
                    Point p20(dl, c, p);
                    
                    points.push_back(p19);
                    points.push_back(p17);
                    points.push_back(p18);
                    points.push_back(p20);                    
                }

                if (k == (divisions - 1)) {
                  
                    Point p21(dl, c, dp);
                    Point p22(dl, dc, dp);
                    Point p23(l, dc, dp);
                    Point p25(l, c, dp);
                    
                    points.push_back(p22);
                    points.push_back(p23);
                    points.push_back(p21);
                    points.push_back(p25);
                }

                p = p + dentro;
            }

            l = l + lado;
        }
        c = c + up;

    }
    
    return points;
}
