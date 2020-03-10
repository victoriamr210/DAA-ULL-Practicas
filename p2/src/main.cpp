#include <iostream>
#include <iomanip>
#include "../include/cinta.hpp"
#include "../include/memoria.hpp"
#include "../include/programa.hpp"
#include "../include/instruccion.hpp"
#include "../include/ram.hpp"

void estado(RAM &sim){
	std::cout << "\n" << std::setw(40) << "Estado de la máquina:"<< "\n\n";
	sim.print_input();
	sim.print_input();
	sim.print_program();
	sim.print_labels();
	sim.print_output();
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

void ex_step(RAM &sim, int &pc, instruction &ins, program &p){
	try{
		ins.set(p.get_i(pc));
		sim.execute();
		if(ins.jump){
			if(sim.next_inst() !=-1){
				pc=sim.next_inst();
			}else{
				pc++;
			}
		}else{
			pc++;
		}	
	}catch(std::string &e){
		std::cout << e << "\n";
	}
}

int ex(RAM &sim, int &pc, instruction &ins, program &p, int &count, memory &m){
	sim.print_labels();
	try{
		sim.print_input();
		ins.set(p.get_i(pc));
		while(!ins.is_halt()){
			// ins.print();
			sim.set_i(ins);
			sim.execute();
			if(ins.jump){
				if(sim.next_inst() !=-1){
					pc=sim.next_inst();
				}else{
					pc++;
				}
			}else{
				pc++;
			}	
			// sim.print_mem();
			
			ins.set(p.get_i(pc));
			count++;
		}
		sim.print_output();
		std::cout << "Se han ejecutado " << count+1 << " instrucciones\n";
		sim.write_file();
	}catch(std::string &e){
		std::cout << e << "\n";
	}
}

int main(int argc, char *argv[]) {
	
	if(argc==5){

		memory m;
		program p(argv[1]);
		input_tape input(argv[2]);
		output_tape output(argv[3]);
		instruction ins;
		RAM sim(m,p,input,output);
		int pc = 0;
		int count = 0;
		std::string debug=argv[4];
		p.print_ins();

		if(debug=="1"){
			char op;
			do{
				ins.set(p.get_i(pc));
				sim.set_i(ins);
				op=menu();
				switch(op){
					case 'r':
						std::cout << "\n";
						sim.print_mem();
						break;
					
					case 't':
						std::cout << "\n";
						std::cout << "Mostrar traza\n";
						if(!ins.is_halt()){
							ins.desc();
							count++;
							ex_step(sim,pc,ins,p);
						}else{
							std::cout << "Programa finalizado\n";
							sim.print_output();
							op='x';
						}
						break;

					case 'e':
						// std::cout << "\n";
						// std::cout << "Ejecutar instruccion\n";
						ex(sim,pc,ins,p,count,m);		
						op='x';
						break;
					
					case 's':
						// std::cout << "\n";
						// std::cout << "Mostrar opcode\n";
						// ins.get_opcode();
						p.print();
						break;
					
					case 'i':
						std::cout << "\n";
						input.print();
						break;
					
					case 'o':
						std::cout << "\n";
						sim.print_output();
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

			ex(sim,pc,ins,p,count,m);
		}

	}else{
		std::cout << "Faltan/sobran argumentos\n";
	}

}
