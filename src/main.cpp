#include "combiner.h"
#include <iostream>

int main(int argc, char** argv) {
	int err_code(0);
	
	try{
		Combiner cb(argc, argv);
	} catch(const std::string &s) {
		std::cout << "Error : " << s << std::endl;
		err_code = 1;
	}
	
	return err_code;
}
