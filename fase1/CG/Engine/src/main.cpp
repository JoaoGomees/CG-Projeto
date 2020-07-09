#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "renderer.cpp"




 //funcao que calcula o numero de linhas do ficheiro xml

int numeroLinhas ()
{
    std::string line;
    std::ifstream file ("./config.xml");
    int nLines = 0;
    
        if (file.is_open())
        {
            while (getline (file,line))
            {
                nLines++;
            }
            file.close();
            
        }
    
    return nLines;
}

//funcao que recebe as linhas do xml e devolve só os nomes dos ficheiros
std::vector <std::string> parser (std::vector <std::string> names)
{
    std::vector <std::string> answer;
    
    char delim[] = "'";
    char *token;
    
    for (int i = 0; i < names.size(); i++)
    {
        std::string nova = names[i];
        token = strtok(&nova[0], delim);
        token = strtok(NULL, delim);
        std::string nova2 (token);
        answer.push_back(nova2);
    }
    
    return answer;
}


int main(int argc, char *argv[])
{
    int nLines = numeroLinhas();
    std::string line;
    std::vector <std::string> linhas; //vector que vai conter as strings que interessam do xml file
    int i = 0;
    
    //parte do codigo que lê o ficheiro xml e guarda todas as linhas que têm ficheiro
    std::ifstream file ("./config.xml");
    
    if (file.is_open())
    {
        while (getline (file,line))
        {
            if (i == 0 || i == (nLines - 1));
            else
            {
                linhas.push_back(line);
            }
            i++;
        }
            
        file.close();
        
    }
    
    std::vector <std::string> parsed = parser(linhas);
    render(argc,argv,parsed);
            
    
    
    
    
}
