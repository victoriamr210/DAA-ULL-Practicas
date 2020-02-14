#include <iostream>
#include "../include/cinta.hpp"

int main(int argc, char *argv[]) {
	
	// if(argc==2){
		char* a=argv[1];
		char* b=argv[2];
		input_tape input(a);
		// input.print();

		output_tape output(b);

		for(int i=0; i<3; i++){
			output.write(input.read());
		}

		output.print();

	// }else{
	// 	std::cout << "Faltan/sobran argumentos\n";
	// }





}