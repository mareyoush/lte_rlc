//Autor: Marta Szukalska, Dawid Bryłka 

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

bool rlcTest(RlcSduS *rlcSdu_p, U8 *rlcPdu_p){

	 //- Parser output. 
	RlcSduS *rlcPdu_p1 = rlcPdu_p;
	rlcComposer(rlcSdu_p, rlcPdu_p);

	RlcSduS *rlcSdu_p1 = rlcSdu_p; //- Output from parser.
	rlcParser(rlcPdu_p, rlcSdu_p);

	//Check correctness of PDU.
	std::cout<< "Checking PDU\n";

	if(rlcPdu_p.mode == rlcPdu_p1.mode){
		std::cout << "correct mode \n";

	}else{
		std::cout << "mode not correct\n";
		return false;
	}

	if(rlcPdu_p.sizePdu == rlcPdu_p1.sizePdu){
		std::cout << "size is correct\n";
	}else{
		std::cout << "size is not correct\n";
		return false;
	}

	std::cout << "Checking SDU\n";

	if(rlcSdu_p.mode == rlcSdu_p1.mode){
		std::cout << "mode is correct\n";
	}else{
		std::cout << "mode not correct\n";
		return false;
	}

	if(rlcSdu_p.type == rlcSdu_p1.type){
		std::cout << "type is correct\n";
	}else{
		std::cout << "type is not correct\n";
		return false;
	}

	if(rlcSdu_p.pool == rlcSdu_p1.pool){
		std::cout << "pool is correct\n";
	}else{
		std::cout << "pool is not correct\n";
		return false;
	}

	if(rlcSdu_p.sizePdu == rlcSdu_p1.sizePdu){
		std::cout << "size is correct\n";
	}else{
		std::cout << "size is not correct\n";
		return false;
	}

	for(int i(0); i < rlcSdu_p.size(); ++i){

		if(rlcSdu_p.sizeSduS[i] == rlcSdu_p1.sizeSduS[i]){
			std::cout << "The Sdu size number " << i << "is correct.\n ";
		}else{
			std::cout << "The Sdu's size number " << i << "is not correct.\n";
			return false;
		}
	}
	return true; 

}


	/*//Checks if the data have been parsed and composed correctly. 
	
	if(cSDUpPDU.size() != pSDUcPDU.size()){
		
		std::cout << "The data have not been copmposed or parsed correctly."<< '\n';
		return 0;

	}else{
		int count = 0;
		int success = 0;

		for(int i(0); i != cSDUpPDU.size(); ++i){
			count = count + 1;
			if(cSDUpPDU[i] == pSDUcPDU[i]){
				success = success +1;
				std::cout << "The line number " << count << " is correct. " << '\n';

			}else{

				std::cout << "The line number " << count << " is not correct. " << '\n';
				std::cout << "The output is: " << pSDUcPDU[i] << '\n';
				std::cout << "The expected output is: " << cSDUpPDU[i] << '\n';
			}
		}

		if(count == success){

			std::cout << "The file was composed and parsed sucessfully. " << '\n';
			return 1;

		}else{
			std::cout << "The file was not composed and parsed correctly" << '\n';
			return 0;
		}
	}

}*/