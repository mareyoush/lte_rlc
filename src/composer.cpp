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
        return 1;   //Blad. Niepoprawny format pliku
    }
    file.close();

    std::cout << std::endl;
    return 0;
}

//Autor: Adam Ziołecki
uint16_t rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    if (rlcSdu_p->mode == T)
    {
        composerTM(rlcSdu_p, rlcPdu_p);
    }
    else if (rlcSdu_p->mode == U5 || rlcSdu_p->mode == U10)
    {
        composerUM(rlcSdu_p, rlcPdu_p);
    }
    else if (rlcSdu_p->mode == A)
    {
        composerAM(rlcSdu_p, rlcPdu_p);
    }

    return 0;
}

//Autor: Jakub Nowak
uint16_t composerTM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    rlcPdu_p->mode = rlcSdu_p->mode;
    rlcPdu_p->sizePdu = rlcSdu_p->sizePdu;
    
    for (int i=0; i < (int)rlcSdu_p->data.size(); i++)
    {
        rlcPdu_p->data += rlcSdu_p->data[i] + " ";
    }
    return 0;
}

//Autor: Adam Ziołecki
uint16_t composerUM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    /*std::string dataPdu = "";
    std::string FI = "";
    std::string E = "";
    std::vector<std::string> LI;
    
    unsigned int SN = 0;

    int i = 0;
    int headerSize = 8;     //size in bits
    int extHeaderSize = 12; //size in bits
    int tempPduSize = rlcSdu_p->sizePdu;
    int sizeSdu = std::stoi(rlcSdu_p->data[i].substr(0, rlcSdu_p->data[i].find(' ')));
    
    for (unsigned int i = 0; i < rlcSdu_p->data.size(); i++)
    {
        if(rlcSdu_p->sizePdu == sizeSdu-1)
        {
            dataPdu += "000";   // FI = 00; E = 0
            dataPdu += decToBin(SN, 5);
            SN++;
            dataPdu += rlcSdu_p->data[i];
        }
        else if(rlcSdu_p->sizePdu > sizeSdu)
        {
            do
            {
                tempPduSize -= sizeSdu;
                tempPduSize -= headerSize/8;
                LI.push_back(decToBin(sizeSdu, 11));
                tempPduSize -= extHeaderSize;
            } while (tempPduSize > sizeSdu);
                
            dataPdu += FI + E + SN;
            for (int i = 0; i < LI.size(); ++i)
            {
                if (LI.last == LI[i])
                    dataPdu += "0";
                else 
                    dataPdu += "1";
                dataPdu += LI[i];
            }

            if (tempPduSize < 0)
            {
                
            }
        }
    }*/

    std::vector<int> sizeSduS;

    for (unsigned int i = 0; i < rlcSdu_p->data.size(); i++)
    {
        sizeSduS.push_back(std::stoi(rlcSdu_p->data[i].substr(0, rlcSdu_p->data[i].find(' '))));
    }

    /*for (unsigned int i = 0; i < rlcSdu_p->data.size();)
    {
        tempPduSize = rlcSdu_p->sizePdu;
        int j = 0;
        while (tempPduSize > 0)
        {
            tempPduSize -= sizeSduS[i];
            ++j;
        }
        if (rlcSdu_p->data[0] == rlcSdu_p->data[i]) //First SDU
        {
            FI = "0";
        }

    }*/

    int tempPduSize = 0;
    int i = 0;
    std::string FI = "";
    std::string E = "";
    std::string extHeader = "";
    while (i < 3)
    {
        FI = "";
        E = "0";
        extHeader = "";
        tempPduSize = rlcSdu_p->sizePdu;
        int j = 0;
        while (tempPduSize > 0)
        {
            tempPduSize -= sizeSduS[i+j];
            ++j;
        }
        if (rlcSdu_p->data[0] == rlcSdu_p->data[i]) //First SDU
        {
            FI = "0";
        }
        int k = 1;
        while (j > k)  // Wiecej wiecej niz jeden Sdu miesci sie w Pdu
        {
            E = "1";
            if (k == (j-1))
                extHeader += "0";
            else
                extHeader += "1";
            extHeader += decToBin(sizeSduS[i], 11); 
            ++k;
        }
        if (extHeader.size() % 8 != 0)
        {
            extHeader += "0000";    // Padding
        }
        int usableSpacePdu = 0;
        for (int m = i; m < i+j; m++)
        {
            usableSpacePdu += sizeSduS[m];

        }
        usableSpacePdu += 1 + (extHeader.size()/8); // Header size + extension header size (in bytes)
        std::cout << usableSpacePdu << "\n";
        i = i+j;
    }
    

    /*std::string test = std::vector[1];
    std::string sizePdu = rlcSdu_p->data[1].substr(0, rlcSdu_p->data[1].find(' '));
    std::cout << "Original " << rlcSdu_p->data[1] << "\nNew " << sizePdu << "\n";
    std::cout << decToBin(5, 5) << "\n";*/

    return 0;
}

uint16_t composerAM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{

    return 0;
}

