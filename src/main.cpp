#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include "rlc_structures.h"
#include "parser.h"
#include "composer.h"

//Author: Dawid Bryłka
int main(int argc, char** argv)
{
    uint16_t ret = 0 ;
    int opts = 0;
    int verbose_flag = 0,
         composer_flag = 0,
         parser_flag = 0,
         test_flag = 0;
    while(true){
        static struct option long_opts[] = {
            {"verbose", no_argument, &verbose_flag, 1},
            {"composer", no_argument, &composer_flag, 1},
            {"parser", no_argument, &parser_flag, 1},
            {"test", no_argument, &test_flag, 1},
            {0,0,0,0}
        };

        opts = getopt_long(argc,argv,"",long_opts,0);
        if(opts == -1) break;
    }
    if((parser_flag + composer_flag + test_flag)> 1){
        std::cout << "Too many aruments"<<std::endl;
        return 1;
    }else if((parser_flag + composer_flag + test_flag)==0){
        std::cout<<"rlcLab --composer | --parser | --test [--verbose] SDU_filename PDU_filename" <<std::endl;
        std::cout<<"--composer - compose RLC frame" <<std::endl;
        std::cout<<"--parser - parse RLC frame" <<std::endl;
        std::cout<<"--test - validate composing/parsing RLC frames"<<std::endl;
        std::cout<<"(optional) --verbose - give whole logs to predefined file"<<std::endl;
        return 1;
    }
    RlcSduS *rlcSdu_p = new RlcSduS();
    RlcPduS *rlcPdu_p = new RlcPduS();
    if(composer_flag){
        loadSduFile(argv[1], rlcSdu_p);
        rlcComposer(rlcSdu_p, rlcPdu_p);
        savePduFile(argv[2], rlcPdu_p);
        return 0;
    }else if(parser_flag){
        FILE *file = fopen(argv[1], "r");
        if (file == NULL){
            perror("fopen");
            return EBAD_FILE;
        }
        ret = check_pdu_file(file, rlcPdu_p);
        if (ret != 0){
            printf("Error returned, exiting with code %d", ret);
            return ret;
        }
        ret = rlcParser(rlcPdu_p, rlcSdu_p);
        if (ret != 0){
            printf("Error in parser, exiting.\n");
            return ret;
        }
        ret = fclose(file);
        if (ret != 0){
            perror("fclose");
        }
    }else if(test_flag){
        //ret = rlcTest(rlcPdu_p, rlcSdu_p);
        if(ret){
            std::cout<<"Test finished correctly" <<std::endl;
        }else{
            std::cout<<"Test has failed" <<std::endl;
        }
    }
    return 0;
}

