#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include "../../Common/tinyxml2.h"
#include "../../Common/Object.h"
#include "../headers/renderer.h"
#include "../headers/reader.h"


using namespace tinyxml2;

std::vector <Object> lista;
bool stop = false;

void grupo(int argc, char *argv[], XMLElement* groupElement, std::vector <std::vector <float> > translate, std::vector <float> rotate, float tX, float tY, float tZ, float sX, float sY, float sZ) {

    XMLElement* translateElement = groupElement->FirstChildElement( "translate" );
    if (translateElement != nullptr){

        if(translateElement->Attribute( "time" )){

            float time = 0.0f;
            translateElement->QueryAttribute( "time", &time );

            std::vector <float> nTranslate;
            nTranslate.push_back(time);
            
            XMLElement* pointElement = translateElement->FirstChildElement( "point" );
            while (pointElement != nullptr){
                float px = 0.0f, py = 0.0f, pz = 0.0f;
                pointElement->QueryAttribute( "X", &px );
                pointElement->QueryAttribute( "Y", &py );
                pointElement->QueryAttribute( "Z", &pz );

                nTranslate.push_back(px);
                nTranslate.push_back(py);
                nTranslate.push_back(pz);

                pointElement = pointElement->NextSiblingElement();
            }
            if(nTranslate.size() < 4*3 +1){
                std::cout << "Pontos insuficientes." << std::endl;
                stop = true;
                return;
            }

            translate.push_back(nTranslate);
        }
        else{
            float tx = 0.0f, ty = 0.0f, tz = 0.0f;
            translateElement->QueryAttribute( "X", &tx );
            translateElement->QueryAttribute( "Y", &ty );
            translateElement->QueryAttribute( "Z", &tz );

            tX += tx; tY += ty; tZ += tz;
        }
    }

    XMLElement* scaleElement = groupElement->FirstChildElement( "scale" );
    if (scaleElement != nullptr){
        float sx = 1.0f, sy = 1.0f, sz = 1.0f;
        scaleElement->QueryAttribute( "X", &sx );
        scaleElement->QueryAttribute( "Y", &sy );
        scaleElement->QueryAttribute( "Z", &sz );

        sX *= sx; sY *= sy; sZ *= sz;
    }

    XMLElement* rotateElement = groupElement->FirstChildElement( "rotate" );
    if (rotateElement != nullptr){
        float time = 0.0f, angle = 0.0f, aX = 0.0f, aY = 0.0f, aZ = 0.0f;
        
        if(rotateElement->Attribute( "time" )){
            rotateElement->QueryAttribute( "time", &time );
            rotate.push_back(1);
            rotate.push_back(time);
        }
        else{
            rotateElement->QueryAttribute( "angle", &angle );
            rotate.push_back(0);
            rotate.push_back(angle);
        }

        rotateElement->QueryAttribute( "axisX", &aX );
        rotateElement->QueryAttribute( "axisY", &aY );
        rotateElement->QueryAttribute( "axisZ", &aZ );

        rotate.push_back(aX);
        rotate.push_back(aY);
        rotate.push_back(aZ);
    }

    XMLElement* modelsElement = groupElement->FirstChildElement( "models" );
    if (modelsElement != nullptr){
        XMLElement* modelElement = modelsElement->FirstChildElement( "model" );

        while(modelElement != nullptr){
            std::string filename = modelElement->Attribute( "file" );

            std::string fileName = "../../Demos/";
            std::vector <float> points = readFile(fileName.append(filename));

            Object o(points, getIndex(), translate, rotate, tX, tY, tZ, sX, sY, sZ);
            lista.push_back(o);

            modelElement = modelElement->NextSiblingElement();
        }
    }

    XMLElement* subgroupElement = groupElement->FirstChildElement( "group" );
    while(subgroupElement != nullptr){
        grupo(argc, argv, subgroupElement, translate, rotate, tX, tY, tZ, sX, sY, sZ);

        subgroupElement = subgroupElement->NextSiblingElement();
    }

}

int main(int argc, char *argv[])
{
    XMLDocument doc;
    std::string folder = "../../XML/";
    std::string file = folder.append(argv[1]);
    doc.LoadFile(file.c_str());
    
    if(doc.ErrorID() != 0) {
        std::cout << "Erro a dar load ao documento." << std::endl;}
    
    else{
        XMLElement* groupElement = doc.FirstChildElement( "scene" )->FirstChildElement( "group" );
        
        while(groupElement != nullptr){

            std::vector <float> rotate;
            std::vector <std::vector <float> > translate;
            grupo(argc, argv, groupElement, translate, rotate, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

            groupElement = groupElement->NextSiblingElement();
        
        }
        if(!stop)
            render(argc, argv, lista);
    }
}
