#include "composer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

//Author: Dawid Bryłka
//Modified by Adam Ziołecki
std::string decToBin(int dec, int bitsNumber)
{
    std::string output = "";
    while(dec != 0) 
    {
        if(dec % 2)
        {
            output += "1";
            dec--;
        }
        else
            output += "0";
        dec /= 2;
    }
    if (output.length() != (unsigned int)bitsNumber)
    {
        int temp = bitsNumber - output.length();
        for(int i = 0; i < temp; i++)
        {
            output += "0";
        }
    }

    std::reverse(output.begin(), output.end());
    return output;
}

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
    else
    {
        return 1;   //Blad. Nie poprawny format pliku
    }
    file.close();

    std::cout << std::endl;
    return 0;
}

int rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    std::string dataPdu = "";
    unsigned int SN = 0;

    std::string FI = "";
    std::string E = "";
    std::vector<std::string> LI;


    if (rlcSdu_p->mode == U5)
    {
        int i = 0;
        int headerSize = 8;
        int extHeaderSize = 12;
        int tempPduSize = rlcSdu_p->sizePdu;
        int sizeSdu = std::stoi(rlcSdu_p->data[i].substr(0, rlcSdu_p->data[i].find(' ')));
        for (unsigned int i = 0; i < rlcSdu_p->data.size(); i++)
        {
            if(rlcSdu_p->sizePdu == sizeSdu)
            {
                dataPdu += "000";   // FI = 00; E = 0
                dataPdu += decToBin(SN, 5);
                SN++;
            }
            else if(rlcSdu_p->sizePdu > sizeSdu)
            {
                do
                {
                    tempPduSize -= sizeSdu;
                    tempPduSize -= headerSize;
                    LI.push_back(decToBin(sizeSdu, 11));
                    tempPduSize -= extHeaderSize;
                } while (tempPduSize > sizeSdu);
            }
        }
    }
    //std::string test = std::vector[1];
    std::string sizePdu = rlcSdu_p->data[1].substr(0, rlcSdu_p->data[1].find(' '));
    std::cout << "Original " << rlcSdu_p->data[1] << "\nNew " << sizePdu << "\n";
    std::cout << decToBin(5, 5) << "\n";
    return 0;
}