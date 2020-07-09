#include <iostream>
#include "../../Common/Point.h"
#include "../headers/box.h"


std::vector<Point> drawBox(float largura, float comprimento, float profundidade, float divisions)
{
    //largura - esquerda direita
    //comprimento - cima baixo
    //profundidade - frente trás
    
    std::vector <Point> points;
    divisions = divisions + 1;
    float lado = largura / divisions;
    float up = comprimento / divisions;
    float dentro = profundidade / divisions;

    float prop = 1 / (2 * largura + 2 * profundidade);
    float ed = profundidade * prop;          //percentagem da grelha para as faces da esquerda e da direita
    float ft = largura * prop;          //percentagem da grelha para as faces da frente e de trás

    float c = -(comprimento / 2.0f);

    for (int i = 0; i < divisions; i++) {

        float l = -(largura / 2.0f);
        float dc = c + up;

        for (int j = 0; j < divisions; j++) {

            float p = -(profundidade / 2.0f);
            float dl = l + lado;

            for (int k = 0; k < divisions; k++) {

                float dp = p + dentro;

                // face baixo
                if (i == 0) {

                	Point n1 (0.0f,-1.0f,0.0f);
                    Point p1(dl, c, dp);
                    Point p2(l, c, p);
                    Point p3(dl, c, p);
                    Point p4(l, c, dp);
                    
                    points.push_back(p3);
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p2);
                    points.push_back(p1);
                    points.push_back(p4);

                    points.push_back(n1);
                    points.push_back(n1);
                    points.push_back(n1);
                    points.push_back(n1);
                    points.push_back(n1);
                    points.push_back(n1);

                    Point t1( (j + 1) * (1.0f / divisions),  k      * (0.25f / divisions), 0.0f);
                    Point t2( (j + 1) * (1.0f / divisions), (k + 1) * (0.25f / divisions), 0.0f);
                    Point t3(  j      * (1.0f / divisions),  k      * (0.25f / divisions), 0.0f);
                    Point t4(  j      * (1.0f / divisions), (k + 1) * (0.25f / divisions), 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);

                }

                // face cima
                if (i == (divisions - 1)) {

                	Point n2 (0.0f,1.0f,0.0f);

                    Point p5(dl, dc, dp);
                    Point p6(dl, dc, p);
                    Point p7(l, dc, p);
                    Point p8(l, dc, dp);
                    
                    points.push_back(p6);
                    points.push_back(p7);
                    points.push_back(p5);
                    points.push_back(p5);
                    points.push_back(p7);
                    points.push_back(p8);

                    points.push_back(n2);
                    points.push_back(n2);
                    points.push_back(n2);
                    points.push_back(n2);
                    points.push_back(n2);
                    points.push_back(n2);

                    Point t1( (j + 1) * (1.0f / divisions),  k      * (0.25f / divisions) + 0.75f, 0.0f);
                    Point t2(  j      * (1.0f / divisions),  k      * (0.25f / divisions) + 0.75f, 0.0f);
                    Point t3( (j + 1) * (1.0f / divisions), (k + 1) * (0.25f / divisions) + 0.75f, 0.0f);
                    Point t4(  j      * (1.0f / divisions), (k + 1) * (0.25f / divisions) + 0.75f, 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);
                }

                // face esquerda
                if (j == 0) {

                    Point n3(-1.0f,0.0f,0.0f);
                    Point p9(l, c, dp);
                    Point p10(l, dc, p);
                    Point p11(l, c, p);
                    Point p12(l, dc, dp);
                    
                    points.push_back(p11);
                    points.push_back(p9);
                    points.push_back(p10);
                    points.push_back(p10);
                    points.push_back(p9);
                    points.push_back(p12);

                    points.push_back(n3);
                    points.push_back(n3);
                    points.push_back(n3);
                    points.push_back(n3);
                    points.push_back(n3);
                    points.push_back(n3);
    
                    Point t1(  k      * (ed / divisions),  i      * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t2( (k + 1) * (ed / divisions),  i      * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t3(  k      * (ed / divisions), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t4( (k + 1) * (ed / divisions), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);
                
                }

                // face direita
                if (j == (divisions - 1)) {

                   	Point n4(1.0f,0.0f,0.0f);

                    Point p13(dl, c, p);
                    Point p14(dl, dc, p);
                    Point p15(dl, dc, dp);
                    Point p16(dl, c, dp);
                    
                    points.push_back(p14);
                    points.push_back(p15);
                    points.push_back(p13);
                    points.push_back(p13);
                    points.push_back(p15);
                    points.push_back(p16);

                    points.push_back(n4);
                    points.push_back(n4);
                    points.push_back(n4);
                    points.push_back(n4);
                    points.push_back(n4);
                    points.push_back(n4);

                    Point t1( ed - ( k      * (ed / divisions)) + (ed+ft), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t2( ed - ((k + 1) * (ed / divisions)) + (ed+ft), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t3( ed - ( k      * (ed / divisions)) + (ed+ft),  i      * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t4( ed - ((k + 1) * (ed / divisions)) + (ed+ft),  i      * (0.50f / divisions) + 0.25f, 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);
                }

                // face trás
                if (k == 0) {

                    Point n5(0.0f,0.0f,-1.0f);

                    Point p17(dl, dc, p);
                    Point p18(l, c, p);
                    Point p19(l, dc, p);
                    Point p20(dl, c, p);
                    
                    points.push_back(p19);
                    points.push_back(p17);
                    points.push_back(p18);
                    points.push_back(p18);
                    points.push_back(p17);
                    points.push_back(p20);

                    points.push_back(n5);
                    points.push_back(n5);
                    points.push_back(n5);
                    points.push_back(n5);
                    points.push_back(n5);
                    points.push_back(n5);

                    Point t1( ft - ( j      * (ft / divisions)) + (ed*2+ft), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t2( ft - ((j + 1) * (ft / divisions)) + (ed*2+ft), (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t3( ft - ( j      * (ft / divisions)) + (ed*2+ft),  i      * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t4( ft - ((j + 1) * (ft / divisions)) + (ed*2+ft),  i      * (0.50f / divisions) + 0.25f, 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);
                }

                // face frente
                if (k == (divisions - 1)) {

                  	Point n6(0.0f,0.0f,1.0f);

                    Point p21(dl, c, dp);
                    Point p22(dl, dc, dp);
                    Point p23(l, dc, dp);
                    Point p25(l, c, dp);
                    
                    points.push_back(p22);
                    points.push_back(p23);
                    points.push_back(p21);
                    points.push_back(p21);
                    points.push_back(p23);
                    points.push_back(p25);

                    points.push_back(n6);
                    points.push_back(n6);
                    points.push_back(n6);
                    points.push_back(n6);
                    points.push_back(n6);
                    points.push_back(n6);

                    Point t1( (j + 1) * (ft / divisions) + ed, (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t2(  j      * (ft / divisions) + ed, (i + 1) * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t3( (j + 1) * (ft / divisions) + ed,  i      * (0.50f / divisions) + 0.25f, 0.0f);
                    Point t4(  j      * (ft / divisions) + ed,  i      * (0.50f / divisions) + 0.25f, 0.0f);

                    points.push_back(t1);
                    points.push_back(t2);
                    points.push_back(t3);
                    points.push_back(t3);
                    points.push_back(t2);
                    points.push_back(t4);
                }

                p = p + dentro;
            }

            l = l + lado;
        }
        c = c + up;

    }
    
    return points;
}
