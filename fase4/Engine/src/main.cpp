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
            std::vector <std::vector <float> > info = readFile(fileName.append(filename));

            std::string textura = "";
            std::vector <float> diff, spec, emis, amb;

            if(modelElement->Attribute( "texture" )){
                textura = modelElement->Attribute( "texture" );
            }

            if(modelElement->Attribute( "diffR" ) || modelElement->Attribute( "diffG" ) || modelElement->Attribute( "diffB" ) ){
                float diffR = 0.0f, diffG = 0.0f, diffB = 0.0f;
                modelElement->QueryAttribute( "diffR", &diffR );
                modelElement->QueryAttribute( "diffG", &diffG );
                modelElement->QueryAttribute( "diffB", &diffB );
                diff.push_back(diffR);
                diff.push_back(diffG);
                diff.push_back(diffB);
            }


            if(modelElement->Attribute( "specR" ) || modelElement->Attribute( "specG" ) || modelElement->Attribute( "specB" ) ){
                float specR = 0.0f, specG = 0.0f, specB = 0.0f;
                modelElement->QueryAttribute( "specR", &specR );
                modelElement->QueryAttribute( "specG", &specG );
                modelElement->QueryAttribute( "specB", &specB );
                spec.push_back(specR);
                spec.push_back(specG);
                spec.push_back(specB);
            }

            if(modelElement->Attribute( "emisR" ) || modelElement->Attribute( "emisG" ) || modelElement->Attribute( "emisB" ) ){
                float emisR = 0.0f, emisG = 0.0f, emisB = 0.0f;
                modelElement->QueryAttribute( "emisR", &emisR );
                modelElement->QueryAttribute( "emisG", &emisG );
                modelElement->QueryAttribute( "emisB", &emisB );
                emis.push_back(emisR);
                emis.push_back(emisG);
                emis.push_back(emisB);
            }

            if(modelElement->Attribute( "ambR" ) || modelElement->Attribute( "ambG" ) || modelElement->Attribute( "ambB" ) ){
                float ambR = 0.0f, ambG = 0.0f, ambB = 0.0f;
                modelElement->QueryAttribute( "ambR", &ambR );
                modelElement->QueryAttribute( "ambG", &ambG );
                modelElement->QueryAttribute( "ambB", &ambB );
                amb.push_back(ambR);
                amb.push_back(ambG);
                amb.push_back(ambB);
            }

            Object o(info, getIndex(), translate, rotate, tX, tY, tZ, sX, sY, sZ, textura, diff, spec, emis, amb);
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
    int nrLights = 0;
    
    if(doc.ErrorID() != 0) {
        std::cout << "Erro a dar load ao documento." << std::endl;}
    
    else{
        std::vector <float> point, directional, spot;

        XMLElement* lightsElement = doc.FirstChildElement( "scene" )->FirstChildElement( "lights" );

        if (lightsElement != nullptr){

            XMLElement* lightElement = lightsElement->FirstChildElement( "light" );

            while(lightElement != nullptr){
                
                std::string type = lightElement->Attribute( "type" );

                if(!type.compare("POINT")){
                    float posX = 0.0f, posY = 0.0f, posZ = 0.0f, aten = 0.0f;
                    lightElement->QueryAttribute( "posX", &posX );
                    lightElement->QueryAttribute( "posY", &posY );
                    lightElement->QueryAttribute( "posZ", &posZ ); 
                    lightElement->QueryAttribute( "at", &aten);   
                      
                    point.push_back(posX); point.push_back(posY); point.push_back(posZ);
                    point.push_back(aten);                 
                }

                if(!type.compare("DIRECTIONAL")){
                    float dirX = 0.0f, dirY = 0.0f, dirZ = 0.0f;
                    lightElement->QueryAttribute( "dirX", &dirX );
                    lightElement->QueryAttribute( "dirY", &dirY );
                    lightElement->QueryAttribute( "dirZ", &dirZ );

                    directional.push_back(dirX); directional.push_back(dirY); directional.push_back(dirZ);
                }

                if(!type.compare("SPOT")){
                    float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
                    lightElement->QueryAttribute( "posX", &posX );
                    lightElement->QueryAttribute( "posY", &posY );
                    lightElement->QueryAttribute( "posZ", &posZ );

                    float dirX = 0.0f, dirY = 0.0f, dirZ = 0.0f;
                    lightElement->QueryAttribute( "dirX", &dirX );
                    lightElement->QueryAttribute( "dirY", &dirY );
                    lightElement->QueryAttribute( "dirZ", &dirZ );

                    float aten = 0.0f, cut = 45.0f, exp = 0.0f;
                    lightElement->QueryAttribute( "at", &aten);
                    lightElement->QueryAttribute( "cut", &cut);
                    lightElement->QueryAttribute( "exp", &exp);

                    spot.push_back(posX); spot.push_back(posY); spot.push_back(posZ);
                    spot.push_back(dirX); spot.push_back(dirY); spot.push_back(dirZ);
                    spot.push_back(aten); spot.push_back(cut); spot.push_back(exp); 
                }

                lightElement = lightElement->NextSiblingElement();
                nrLights++;
            }

            if(nrLights > 8){
                std::cout << "Ficheiro contém demasiados lights." << std::endl;
                return 0;
            }
        }


        XMLElement* groupElement = doc.FirstChildElement( "scene" )->FirstChildElement( "group" );
        
        while(groupElement != nullptr){

            std::vector <float> rotate;
            std::vector <std::vector <float> > translate;
            grupo(argc, argv, groupElement, translate, rotate, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

            groupElement = groupElement->NextSiblingElement();
        
        }

        if(!stop)
            render(argc, argv, lista, point, directional, spot);
    }
}
