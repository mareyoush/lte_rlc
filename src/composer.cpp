#include "composer.h"
#include <fstream>
#include <iostream>
#include <regex>

int loadSduFile(std::string filename, RlcSduS *rlcSdu_p)
{
    std::ifstream file(filename.c_str());
    /*while(file.get(character)){ 
        if (character == ' ')
            continue;
        std::cout << character;
    } */ 
    std::string line;
    getline(file, line);
    //std::cout << line;

    if(std::regex_search(line, std::regex("^T")))
    {
        int i = 0;
        rlcSdu_p->mode = T;
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
            std::cout << rlcSdu_p->data[i++];
        }
    } 
    else if(std::regex_search(line, std::regex("^A")))
    {

    }
    else if(std::regex_search(line, std::regex("^U5")))
    {

    }
    else if(std::regex_search(line, std::regex("^U10")))
    {
        
    }

    file.close();

    std::cout << std::endl;
    return 0;
}

