#include "composer.h"
#include <fstream>
#include <iostream>
#include <regex>

int loadSduFile(const std::string filename)//, RlcSduS *rlcSdu_p)
{
    char character;
    std::ifstream file(filename.c_str());
    /*while(file.get(character)){ 
        if (character == ' ')
            continue;
        std::cout << character;
    } */ 
    std::string line;
    getline(file, line);
    //std::cout << line;

    std::regex pattern("^T");

    if(std::regex_search(line, pattern))
    {
        file.get(character);
        std::cout << character << std::endl;
    } 

    file.get(character);
    std::cout << character;

    file.close();

    std::cout << std::endl;
    return 0;
}

