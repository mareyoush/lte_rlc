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
	
	rlcComposer(rlcSdu_p,rlcPdu_p);
	uint8_t ret = rlcParser(rlcPdu_p, rlcSdu_p);

	printf("Checking correctness of PDU \n");
	if(rlcPdu_p1->sizePdu == rlcPdu_p->sizePdu){
		std::cout<<"Size is correct" <<std::endl;

	}else{
		std::cout<<"Size is not correct";
		return false;
	}

	if(rlcPdu_p1->mode == rlcPdu_p->mode){
		std::cout<<"Mode is correct" <<std::endl;

	}else{
		std::cout<<"Mode is not correct";
		return false;
	}

	printf("Checking SDU file ");
	if(ret!=0)
	{
		printf("Error\n");
		return false;
	}


	/*
	rlcSdu_p1->mode = rlcSdu_p->mode;
	rlcSdu_p1->type = rlcSdu_p->type;
	rlcSdu_p1->pool = rlcSdu_p->pool;
	rlcSdu_p1->sizePdu = rlcSdu_p->sizePdu;
	rlcSdu_p1->sizeSduS = rlcSdu_p->sizeSduS;
	*/

	if(rlcSdu_p1->mode == rlcSdu_p->mode){
		std::cout<<"Mode is correct\n";
	}else{
		std::cout<<"Mode is not correct \n";
		return false;
	}

	if(rlcSdu_p1->type == rlcSdu_p->type){
		std::cout<<"Type is correct\n";
	}else{
		std::cout<<"Type is not correct \n";
		return false;
	}

	if(rlcSdu_p1->sizePdu == rlcSdu_p->sizePdu){
		std::cout<<"Pdu size is correct\n";
	}else{
		std::cout<<"PDU size is not correct \n";
		return false;
	}

	if(rlcSdu_p1->sizeSduS == rlcSdu_p->sizeSduS){
		std::cout<<"SDU size is correct\n";
	}else{
		std::cout<<"SDU size is not correct \n";
		return false;
	}

	if(rlcSdu_p1->pool == rlcSdu_p->pool){
		std::cout<<"Pool is correct\n";
	}else{
		std::cout<<"Mode is not correct \n";
		return false;
	}
	return true;
}
