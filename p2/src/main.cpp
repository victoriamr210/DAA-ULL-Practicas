#include <iostream>
#include <iomanip>
#include "../include/cinta.hpp"
#include "../include/memoria.hpp"
#include "../include/programa.hpp"

void estado(memory &m, input_tape &i, output_tape &o, program &p){
	std::cout << "\n" << std::setw(40) << "Estado de la máquina:"<< "\n\n";
	i.print();
	m.print();
	p.print_ins();
	p.print_label();
	o.print();
}

char menu(void){
	char opcion;
	std::cout << "\n\nMenu\n";
	std::cout << "r: ver los registros\n";
	std::cout << "t: traza\n";
	std::cout << "e: ejecutar\n";
	std::cout << "s: desensamblador\n";
	std::cout << "i: ver cinta entrada\n";
	std::cout << "o: ver cinta salida\n";
	std::cout << "h: ayuda\n";
	std::cout << "x: exit\n";
	std::cout << "> ";
	std::cin >> opcion;
	return opcion;
}

int main(int argc, char *argv[]) {
	
	if(argc==5){

		memory m;
		program p(argv[1]);
		input_tape input(argv[2]);
		output_tape output(argv[3]);
		estado(m, input, output, p);
		std::string debug=argv[4];

		if(debug=="1"){
			char op;
			do{
				op=menu();
				switch(op){
					case 'r':
						std::cout << "\n";
						m.print();
						break;
					
					case 't':
						std::cout << "\n";
						std::cout << "Mostrar traza\n";
						break;

					case 'e':
						std::cout << "\n";
						std::cout << "Ejecutar instruccion\n";
						break;
					
					case 's':
						std::cout << "\n";
						std::cout << "Mostrar opcode\n";
						break;
					
					case 'i':
						std::cout << "\n";
						input.print();
						break;
					
					case 'o':
						std::cout << "\n";
						output.print();
						break;
					
					case 'h':
						op=menu();
						break;
					
					case 'x':
						std::cout << "Programa finalizado\n";
						return 0;
					
					default:
						std::cout << "Opción invalida\n";
				}

			}while(op!='x');
		}

	}else{
		std::cout << "Faltan/sobran argumentos\n";
	}

}
