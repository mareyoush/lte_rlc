#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#define OUTPUT 8

enum rlcMode {T, U5, U10, A};
enum typeSdu {D, C};

struct RlcSduS
{
    rlcMode mode;
    typeSdu type;
    int pool;
    int sizePdu;
    int seqNum;
    std::vector<int> sizeSduS;
    std::vector<string> data;
};

struct RlcPduS
{
    rlcMode mode;
    int sizePdu;
    std::vector<string> data;
};

void decToBin(int hex){
    ofstream file;
    file.open("output.txt", ios::app);
    string output = "";
    while(hex!=0){
        if(hex%2){
            output+="1";
            hex--;
        }
        else
            output+="0";
        hex/=2;
    }
    if (output.length()!=OUTPUT)
        {
            int temp = OUTPUT - output.length();
            for(int i=0;i<temp;i++){
                output+="0";
            }
        }
    for(int i=output.length(); i>=0;i--){
        
        file <<output[i];

    }
    file <<" ";
    file.close();
}
int main()
{
int hex = 0;
string x;
std::ofstream ofs;
ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);
ofs.close();

ifstream file;
file.open("input");
while(!file.eof()){
    //file >> std::hex >> hex;
    file >> std::hex >> hex;
    
    decToBin(hex);

}
file.close();

std::cout << std::endl;
return 0;
}
