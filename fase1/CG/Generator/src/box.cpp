#include <iostream>
#include "../../../Common/Point.h"
#include "../headers/box.h"


std::vector<Point> drawBox(float largura, float comprimento, float profundidade, float divisions)
{
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
                    Point p4(l, c, p);
                    Point p5(dl, c, dp);
                    Point p6(l, c, dp);
                    
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                    points.push_back(p4);
                    points.push_back(p5);
                    points.push_back(p6);
                    
                    
                }

                if (i == (divisions - 1)) {
                    Point p7(dl, dc, dp);
                    Point p8(dl, dc, p);
                    Point p9(l, dc, p);

                    Point p10(l, dc, p);
                    Point p11(l, dc, dp);
                    Point p12(dl, dc, dp);
                    
                    points.push_back(p7);
                    points.push_back(p8);
                    points.push_back(p9);
                    points.push_back(p10);
                    points.push_back(p11);
                    points.push_back(p12);
                }

                if (j == 0) {
                    
                    Point p13(l, c, dp);
                    Point p14(l, dc, p);
                    Point p15(l, c, p);
                    Point p16(l, dc, p);
                    Point p17(l, c, dp);
                    Point p18(l, dc, dp);
                    
                    points.push_back(p13);
                    points.push_back(p14);
                    points.push_back(p15);
                    points.push_back(p16);
                    points.push_back(p17);
                    points.push_back(p18);
                
                    
                    
                }

                if (j == (divisions - 1)) {
                   
                    Point p19(dl, c, p);
                    Point p20(dl, dc, p);
                    Point p21(dl, dc, dp);
                    Point p22(dl, dc, dp);
                    Point p23(dl, c, dp);
                    Point p24(dl, c, p);
                    
                    points.push_back(p19);
                    points.push_back(p20);
                    points.push_back(p21);
                    points.push_back(p22);
                    points.push_back(p23);
                    points.push_back(p24);
                }

                if (k == 0) {
                    
                    Point p25(dl, dc, p);
                    Point p26(l, c, p);
                    Point p27(l, dc, p);
                    Point p28(l, c, p);
                    Point p29(dl, dc, p);
                    Point p30(dl, c, p);
                    
                    points.push_back(p25);
                    points.push_back(p26);
                    points.push_back(p27);
                    points.push_back(p28);
                    points.push_back(p29);
                    points.push_back(p30);
                    
                }

                if (k == (divisions - 1)) {
                  
                    Point p31(dl, c, dp);
                    Point p32(dl, dc, dp);
                    Point p33(l, dc, dp);
                    Point p34(l, dc, dp);
                    Point p35(l, c, dp);
                    Point p36(dl, c, dp);
                    
                    points.push_back(p31);
                    points.push_back(p32);
                    points.push_back(p33);
                    points.push_back(p34);
                    points.push_back(p35);
                    points.push_back(p36);
                }

                p = p + dentro;
            }

            l = l + lado;
        }
        c = c + up;

    }
    
    return points;
}
