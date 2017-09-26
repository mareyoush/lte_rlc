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
//Author: Dawid Bryłka
std::string binToHex(std::string input)
{
    std::string temp = "", output = "";
    int wordCount = 0;
    
    for(int i=0; i<(int)input.length();i++){
        if(isspace(input[i])) continue;
        temp+=input[i];
        if(temp.length() == 4){
                if(!temp.compare("0000")) output.append("0");
                else if(!temp.compare("0001")) output.append("1");
                else if(!temp.compare("0010")) output.append("2");
                else if(!temp.compare("0011")) output.append("3");
                else if(!temp.compare("0100")) output.append("4");
                else if(!temp.compare("0101")) output.append("5");
                else if(!temp.compare("0110")) output.append("6");
                else if(!temp.compare("0111")) output.append("7");
                else if(!temp.compare("1000")) output.append("8");
                else if(!temp.compare("1001")) output.append("9");
                else if(!temp.compare("1010")) output.append("A");
                else if(!temp.compare("1011")) output.append("B");
                else if(!temp.compare("1100")) output.append("C");
                else if(!temp.compare("1101")) output.append("D");
                else if(!temp.compare("1110")) output.append("E");
                else if(!temp.compare("1111")) output.append("F");
                wordCount++;
                temp = "";
        }
        if(wordCount==2){
            output.append(" ");
            wordCount=0;
        }
    }

   return output;
}
//Author: Jakub Nowak
int loadSduFile(std::string filename, RlcSduS *rlcSdu_p)
{
    log("ENTER Function loadSduFile.");    

    std::string line;
    std::ifstream file(filename.c_str());
    
    log("INFO Read first line from SduFile.");
    getline(file, line);
    
    std::istringstream var(line);
    std::string mode = "", type_or_data = "";
    int pool = 0, sizePdu=0;
    var >> mode >> type_or_data >> pool >> sizePdu;

    log("INFO Check mode.");
    if(mode == "T")
    {
        log("INFO Transparent mode.");
        rlcSdu_p->mode = T;
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
        
    } 
    else if(mode == "A")
    {
        log("INFO Acknowledge mode.");
        rlcSdu_p->mode = A;
    
        log("INFO Check type.");
        if(type_or_data == "D")
        {
            log("INFO Data type.");
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
            log("INFO Control type.");
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
        log("INFO Unacknowledge 5-bit mode.");
        rlcSdu_p->mode = U5;

        rlcSdu_p->sizePdu = stoi(type_or_data);

        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }
    else if(mode == "U10")
    {
        log("INFO Unacknowledge 10-bit mode.");
        rlcSdu_p->mode = U10;
        
        rlcSdu_p->sizePdu = stoi(type_or_data);
        while(getline(file, line))
        {
            rlcSdu_p->data.push_back(line);
        }
    }
    else
    {
        log("ERROR Invalid file format.");
        return 1;   //Blad. Niepoprawny format pliku
    }

    log("INFO Close SduFile.");
    file.close();

    std::cout << std::endl;

    log("EXIT Function loadSduFile.");  
    return 0;
}

//Author: Adam Ziołecki
uint16_t rlcComposer(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    log("ENTER Function rlcComposer.");  

    log("INFO Check mode to choose appropriate composer function.");
    if (rlcSdu_p->mode == T)
    {
        log("INFO Function composerTM.");
        composerTM(rlcSdu_p, rlcPdu_p);
    }
    else if (rlcSdu_p->mode == U5 || rlcSdu_p->mode == U10)
    {
        log("INFO Function composerUM.");
        composerUM(rlcSdu_p, rlcPdu_p);
    }
    else if (rlcSdu_p->mode == A)
    {
        log("INFO Function composerAM.");
        composerAM(rlcSdu_p, rlcPdu_p);
    }

    log("EXIT Function rlcComposer.");
    return 0;
}

//Author: Jakub Nowak
uint16_t composerTM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    log("ENTER Function composerTM.");
    
    rlcPdu_p->mode = rlcSdu_p->mode;
    rlcPdu_p->sizePdu = rlcSdu_p->sizePdu;
    rlcPdu_p->data.push_back("");
    
    log("INFO Enter loop to write data to structure.");
    for (int i=0; i < (int)rlcSdu_p->data.size(); i++)
    {
        rlcPdu_p->data[0] += rlcSdu_p->data[i] + " ";
    }
    log("INFO Exit loop.");

    log("EXIT Function composerTM.");
    return 0;
}

//Author: Adam Ziołecki
//Pachoł: Dawid Bryłka
uint16_t composerUM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    log("ENTER Function composerUM.");

    rlcPdu_p->mode = rlcSdu_p->mode;
    rlcPdu_p->sizePdu = rlcSdu_p->sizePdu;

    std::vector<int> sizeSduS;

    for (unsigned int i = 0; i < rlcSdu_p->data.size(); i++)
    {
        sizeSduS.push_back(std::stoi(rlcSdu_p->data[i].substr(0, rlcSdu_p->data[i].find(' '))));
    }

    int headerSize = 1;
    int tempPduSize = 0;
    int i = 0;
    int j = 0;
    std::string FI = "";
    std::string prevFI = "";
    std::string E = "";
    std::string extHeader = "";
    std::string padding = "";
    int usableSpacePdu = 0;
    int leftSizeSdu = 0;
    int SN = 0;
    std::string output = "";

    while (i < int(rlcSdu_p->data.size()))
    {
        FI = "";
        E = "0";
        extHeader = "";
        tempPduSize = rlcSdu_p->sizePdu;
        j = 0;
        
        if (prevFI != "")
            FI += prevFI[1];    //std::cout << "prevFI: " << prevFI[1] << "\n"; 

        if (leftSizeSdu != 0)   //Część poprzedniego SDU
        {
            j++;
            //tempPduSize -= 2;
        }

        while (tempPduSize > 0)
        {
            if ((i+j) > int(rlcSdu_p->data.size()))
                break;
            tempPduSize -= headerSize;
            tempPduSize -= leftSizeSdu;
            if (leftSizeSdu == 0) {
                tempPduSize -= sizeSduS[i+j];
                ++i;
            }
            else {
                tempPduSize -= sizeSduS[i+j-1];
                ++i;
            }
            if (j > 1)
            {
                if (j % 2 != 0)
                    tempPduSize -= 2;
                else
                    tempPduSize -= 1;
            }
            ++j;
        }

        if (i-j == 0) //First SDU
        {
            FI = "0";
        }

        int k = 1;
        while (j > k)  // Wiecej niz jeden Sdu miesci sie w Pdu
        {
            E = "1";
            if (k == (j-1))
            {
                 extHeader += "0";
            }
            else
            {
                extHeader += "1";
            }
            
            if (leftSizeSdu != 0)
            {
                extHeader += decToBin(leftSizeSdu, 11);
            }
            else
            {
                extHeader += decToBin(sizeSduS[i-j+k-1], 11); 
            }
            ++k;
        }

        if (extHeader.size() % 8 != 0)
        {
            extHeader += "0000";    // Padding
        }

        usableSpacePdu = 0;
        usableSpacePdu += leftSizeSdu;
        if (leftSizeSdu != 0)
            --j;
        for (int m = i-j; m < i; m++)
        {
            usableSpacePdu += sizeSduS[m];
        }

        usableSpacePdu += headerSize; // Header size (in bytes)
        if (leftSizeSdu != 0)
            ++j;
        if ((j*12) % 8 != 0)
            usableSpacePdu += ((j-1)*12)/8;
        else
            usableSpacePdu += ((j-1)*12)/8 + 1;
        
        if (usableSpacePdu == rlcSdu_p->sizePdu)
        {
            FI += "0";
            leftSizeSdu = 0;
        }
        else if (usableSpacePdu > rlcSdu_p->sizePdu)
        {
            FI += "1";
            leftSizeSdu = usableSpacePdu - rlcSdu_p->sizePdu;
        }
        else if (usableSpacePdu < rlcSdu_p->sizePdu)
        {
            FI += "0";
        }

        output += binToHex(FI + E + decToBin(SN, 5));
        output += binToHex(extHeader);
        /*for (int m = i-j; m < j; ++m)
        {
            output += rlcSdu_p->data[m]  + " ";
        }*/
        prevFI = FI;
        std::cout << "FI: " << FI << "\n";
        std::cout << "E: " << E << "\n";
        std::cout << "SN: " << decToBin(SN, 5) << "\n";
        std::cout << "EXTENSION HEADER: ";
        std::cout << extHeader << "\n"; 

        ++SN;
    }
      
    rlcPdu_p->data.push_back(output);

    log("EXIT Function composerUM.");
    return 0;
}

uint16_t composerAM(RlcSduS *rlcSdu_p, RlcPduS *rlcPdu_p)
{
    log("ENTER Function composerAM.");
   
    log("EXIT Function composerAM.");
    return 0;
}

//Author: Jakub Nowak
int savePduFile(std::string filename, RlcPduS *rlcPdu_p)
{
    log("ENTER Function savePduFile.");

    std::string mode;
    if(rlcPdu_p->mode == 1)
        mode = "T";
    else if (rlcPdu_p->mode == 2)
        mode = "U5";
    else if (rlcPdu_p->mode == 3)
        mode = "U10";
    else if (rlcPdu_p->mode == 4)
        mode = "A";
    else
    {
        log("ERROR Wrong mode.");
        return 1;
    }
    
    std::ofstream outfile;

    log("INFO Open PduFile to write.");
    outfile.open(filename);    
    if (rlcPdu_p->sizePdu == 0)
        outfile << mode << "\n" << rlcPdu_p->data[0];
    else
        outfile << mode << " " << rlcPdu_p->sizePdu << "\n" << rlcPdu_p->data[0];
    log("INFO Close PduFile to write.");
    outfile.close();
    
    log("EXIT Function savePduFile.");
    return 0;
}

void log(std::string prompt)
{
    std::ofstream logfile;
    logfile.open("log.txt", std::ios::app);
    
        logfile << prompt << "\n";
    
    logfile.close();
}
