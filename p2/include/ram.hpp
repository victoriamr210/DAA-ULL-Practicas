#pragma once
#include <iostream>
#include "memoria.hpp"
#include "instruccion.hpp"
#include "programa.hpp"
#include "cinta.hpp"

class RAM{

  private:
    memory mem_;
    instruction ins_;
    program pr_;
    input_tape input_;
    output_tape output_;
    int jump_to_=-1;
    
  
  public:

    RAM(memory &m, program &p, input_tape &i, output_tape &o);
    void set_i(instruction &i);
    void execute(void);
    int next_inst(void);
    void print_mem(void);
    void print_output(void);
    void print_input(void);
    void print_labels(void);
    void print_program(void);
    void write_file(void);

};