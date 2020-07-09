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

void grupo(int argc, char *argv[], XMLElement* groupElement, std::vector <float> rotate, float tX, float tY, float tZ, float sX, float sY, float sZ) {

    XMLElement* translateElement = groupElement->FirstChildElement( "translate" );
    if (translateElement != nullptr){
        float tx = 0.0f, ty = 0.0f, tz = 0.0f;
        translateElement->QueryAttribute( "X", &tx );
        translateElement->QueryAttribute( "Y", &ty );
        translateElement->QueryAttribute( "Z", &tz );

        tX += tx; tY += ty; tZ += tz;
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
        float angle = 0.0f, aX = 0.0f, aY = 0.0f, aZ = 0.0f;
        rotateElement->QueryAttribute( "angle", &angle );
        rotateElement->QueryAttribute( "axisX", &aX );
        rotateElement->QueryAttribute( "axisY", &aY );
        rotateElement->QueryAttribute( "axisZ", &aZ );

        rotate.push_back(angle);
        rotate.push_back(aX);
        rotate.push_back(aY);
        rotate.push_back(aZ);
    }

    XMLElement* modelsElement = groupElement->FirstChildElement( "models" );
    if (modelsElement != nullptr){
        XMLElement* modelElement = modelsElement->FirstChildElement( "model" );

        while(modelElement != nullptr){
            std::string filename = modelElement->Attribute( "file" );

            Object o (filename, rotate, tX, tY, tZ, sX, sY, sZ);
            lista.push_back(o);

            modelElement = modelElement->NextSiblingElement();
        }
    }

    XMLElement* subgroupElement = groupElement->FirstChildElement( "group" );
    while(subgroupElement != nullptr){
        grupo(argc, argv, subgroupElement, rotate, tX, tY, tZ, sX, sY, sZ);

        subgroupElement = subgroupElement->NextSiblingElement();
    }

}

int main(int argc, char *argv[])
{
    XMLDocument doc;  
    doc.LoadFile("../../Demos/config.xml");
    
    if(doc.ErrorID() != 0) {
        std::cout << "Erro a dar load ao documento." << std::endl;}
    
    else{
        XMLElement* groupElement = doc.FirstChildElement( "scene" )->FirstChildElement( "group" );
        
        while(groupElement != nullptr){

            std::vector <float> rotate;
            grupo(argc, argv, groupElement, rotate, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

            groupElement = groupElement->NextSiblingElement();
        
        }

        render(argc, argv, lista);
    }
}
