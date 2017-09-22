//Autor: Marta Szukalska, Dawid Bryłka 

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "rlc_structures.h"
#include "rlcTest.h"
#include "parser.h"
#include "composer.h"

bool rlcTest(RlcPduS *rlcPdu_p, RlcSduS *rlcSdu_p){

	 //- Parser output. 
	RlcPduS *rlcPdu_p1 = new RlcPduS;
	rlcPdu_p1->sizePdu = rlcPdu_p->sizePdu;
	rlcPdu_p1->mode = rlcPdu_p->mode;
	rlcPdu_p1->data = rlcPdu_p->data;	

	RlcSduS *rlcSdu_p1 = new RlcSduS;
	rlcSdu_p1->mode = rlcSdu_p->mode;
	rlcSdu_p1->type = rlcSdu_p->type;
	rlcSdu_p1->pool = rlcSdu_p->pool;
	rlcSdu_p1->sizePdu = rlcSdu_p->sizePdu;
	rlcSdu_p1->sizeSduS = rlcSdu_p->sizeSduS;
	rlcSdu_p1->data = rlcSdu_p->data;
	
	rlcComposer(rlcSdu_p,rlcPdu_p1);
	//printf("%c %c", rlcPdu_p->data[0], rlcPdu_p1->data[0] );
	return false;
}
