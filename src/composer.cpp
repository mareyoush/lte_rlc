#include "composer.h"
#include <fstream>
#include <iostream>
#include <sstream>


//Autor: Jakub Nowak
int loadSduFile(std::string filename, RlcSduS *rlcSdu_p)
{
    std::string line;
    
    
    std::ifstream file(filename.c_str());
    
    getline(file, line);
    

    std::istringstream var(line);
    std::string mode = "", type_or_data = "";
    int pool = 0, sizePdu=0;
    var >> mode >> type_or_data >> pool >> sizePdu;

    if(mode == "T")
    {
        rlcSdu_p->mode = T;
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
            //std::cout << rlcSdu_p->data[i++];
        }
        
    } 
    else if(mode == "A")
    {
        rlcSdu_p->mode = A;
        if(type_or_data == "D")
        {
            rlcSdu_p->type = D;
            rlcSdu_p->pool = pool;
            rlcSdu_p->sizePdu = sizePdu;
            while(getline(file, line))
            {
                rlcSdu_p->data.push_back(line);
            }
            
        }
        else if(type_or_data == "C")
        {
            std::string tmp_SN;
            while(getline(file, line))
            {
                tmp_SN += line + " ";
            }
            rlcSdu_p->data.push_back(tmp_SN);
        }
    }
    else if(mode == "U5")
    {
        rlcSdu_p->mode = U5;

        rlcSdu_p->sizePdu = stoi(type_or_data);

        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }
    else if(mode == "U10")
    {
        rlcSdu_p->mode = U10;
        
        rlcSdu_p->sizePdu = stoi(type_or_data);
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }

    file.close();

    std::cout << std::endl;
    return 0;
}

