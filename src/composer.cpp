#include "composer.h"
#include <fstream>
#include <iostream>

int loadSduFile(const std::string filename)//, RlcSduS *rlcSdu_p)
{
    char character;
    std::ifstream file(filename.c_str());
    while(file.get(character)){ 
        std::cout << character;
    }  
    file.close();
    std::cout << std::endl;
    return 0;
}

