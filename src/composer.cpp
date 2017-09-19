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

    if(std::regex_match(line, std::regex("^T")))
    {
        
    } 
    else if(std::regex_match(line, std::regex("^A")))
    {

    }
    else if(std::regex_match(line, std::regex("^U5")))
    {

    }
    else if(std::regex_match(line, std::regex("^U10")))
    {
        
    }

    file.close();

    std::cout << std::endl;
    return 0;
}

