#pragma once
#include <iostream>
#include "memoria.hpp"
#include "instruccion.hpp"
#include "programa.hpp"
#include "cinta.hpp"

class simulator{

  public:
    memory mem_;
    instruction ins_;
    program pr_;
    input_tape input_;
    output_tape output_;
    int jump_to_=-1;
    
  
  public:

    simulator(memory &m, program &p, input_tape &i, output_tape &o);
    void set_i(instruction &i);
    void execute(void);
    int next_inst(void);

};