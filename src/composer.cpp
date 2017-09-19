#include "composer.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

int loadSduFile(std::string filename, RlcSduS *rlcSdu_p)
{
    std::string line;
    std::string delimiter = " ";
    
    std::ifstream file(filename.c_str());
    
    getline(file, line);
    
    //int i = 0;

    if(std::regex_search(line, std::regex("^T")))
    {
        std::istringstream var(line);
        std::string a = "",b = "";
        int c = 0, d=0;

        var >> a >> b >> c >> d;

        std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl; 

        rlcSdu_p->mode = T;
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
            //std::cout << rlcSdu_p->data[i++];
        }
        
    } 
    else if(std::regex_search(line, std::regex("^A")))
    {
        rlcSdu_p->mode = A;
        if(std::regex_search(line, std::regex("D")))
        {
            rlcSdu_p->type = D;
            
            std::istringstream var(line);
            std::string a,b;
            int c, d;

            var >> a >> b >> c >> d;

            std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl; 
            
            /*std::string::iterator end_pos = std::remove(pool.begin(), pool.end(), ' ');
            pool.erase(end_pos, pool.end());
            rlcSdu_p->pool = stoi(pool);*/
        }
        else if(std::regex_search(line, std::regex("C")))
        {
            std::string tmp_SN;
            while(getline(file, line))
            {
                tmp_SN += line + " ";
            }
            rlcSdu_p->data.push_back(tmp_SN);
        }
    }
    else if(std::regex_search(line, std::regex("^U5")))
    {
        rlcSdu_p->mode = U5;

        std::string sizePdu = line.substr(line.find(delimiter));

        std::string::iterator end_pos = std::remove(sizePdu.begin(), sizePdu.end(), ' ');
        sizePdu.erase(end_pos, sizePdu.end());
        rlcSdu_p->sizePdu = stoi(sizePdu);

        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }
    else if(std::regex_search(line, std::regex("^U10")))
    {
        rlcSdu_p->mode = U10;
        
        std::string sizePdu = line.substr(line.find(delimiter));
        std::string::iterator end_pos = std::remove(sizePdu.begin(), sizePdu.end(), ' ');
        sizePdu.erase(end_pos, sizePdu.end());
        rlcSdu_p->sizePdu = stoi(sizePdu);
        std::cout << sizePdu;
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }

    file.close();

    std::cout << std::endl;
    return 0;
}

