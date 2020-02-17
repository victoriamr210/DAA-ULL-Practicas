#include <iostream>
#include <iomanip>
#include "../include/cinta.hpp"
#include "../include/memoria.hpp"
#include "../include/programa.hpp"
#include "../include/instruccion.hpp"
#include "../include/simulador.hpp"

void estado(simulator &sim){
	std::cout << "\n" << std::setw(40) << "Estado de la máquina:"<< "\n\n";
	sim.input_.print();
	sim.mem_.print();
	sim.pr_.print_ins();
	sim.pr_.print_label();
	sim.output_.print();
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
		instruction ins;
		simulator sim(m,p,input,output);
		int pc=0;
		std::string debug=argv[4];
		// p.print_ins();

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
		}else{
			pc=0;
			try{

				ins.set(p.get_i(pc));
				p.print_ins();
			// for(int i=0; i<30; i++){
				while(!ins.is_halt()){
					sim.set_i(ins);
					sim.execute();
					if(ins.jump){
						std::cout << "if\n";
						if(sim.next_inst() !=-1){
							std::cout << "next\n";
							pc=sim.next_inst();
						}else{
							pc++;
						}
					}else{
						std::cout << "else\n";
						pc++;
					}	
					std::cout << "pc:" << pc << "\n";
					ins.print();
					ins.set(p.get_i(pc));
					sim.mem_.print();
					sim.output_.print();
				}

			}catch(std::string &e){
				std::cout << e << "\n";
			}
					
					// pc++;
				
			
			
			
		}

	}else{
		std::cout << "Faltan/sobran argumentos\n";
	}

}
