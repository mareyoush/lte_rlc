#include <stdio.h>
#include <errno.h>
#include "rlc_structures.h"
#include "parser.h"
int main(int argc, char **argv)
{
    uint16_t ret;
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        perror("fopen");
        return 1;
    }

    RlcPduS *pdu = new RlcPduS;

    ret = check_pdu_file(file, pdu);
    if (ret != 0){
        printf("exiting");
        return ret;
    }

    RlcSduS *sdu = new RlcSduS;
    ret = rlcParser(pdu, sdu);
    if (ret != 0){
        printf("Error in parser, exiting.\n");
        return ret;
    }


    
    ret = fclose(file);
    if (ret != 0){
        perror("fclose");
    }
    return 0;
}

