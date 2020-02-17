#include "../include/simulador.hpp"

simulator::simulator(memory &m, program &p, input_tape &i, output_tape &o){
  mem_=m;
  pr_=p;
  input_=i;
  output_=o;
}

void simulator::set_i(instruction &i){
  ins_=i;
}


void simulator::execute(void){

  if(ins_.instruc_=="read" || ins_.instruc_=="READ"){
    mem_.store(ins_.number,input_.read());
  }

  if(ins_.instruc_=="load" || ins_.instruc_=="LOAD"){
    if(ins_.symbol=='='){
      mem_.store(0,ins_.number);
    }else{
      if(ins_.symbol=='*'){
        mem_.store(0,mem_.load(mem_.load(ins_.number)));
      }
      mem_.store(0,mem_.load(ins_.number));
    }
  }

  if(ins_.instruc_=="store" || ins_.instruc_=="STORE"){
    if(ins_.symbol=='='){
      // std::cout << "hola\n";
      std::string e="Instruccion ilegal";
      throw e;
    }else{
      if(ins_.symbol=='*'){
        mem_.store(mem_.load(mem_.load(ins_.number)),mem_.load(0));
      }
      mem_.store(ins_.number,mem_.load(0));
    }
  }

  if(ins_.instruc_=="write" || ins_.instruc_=="WRITE"){
    if(ins_.symbol=='='){
      output_.write(ins_.number);
    }else{
      if(ins_.number==0){
        std::string e="Instruccion ilegal";
        throw e;
      } else{
        output_.write(mem_.load(ins_.number));
      }
    }
  }

  if(ins_.instruc_=="add" || ins_.instruc_=="ADD"){
    if(ins_.symbol=='='){
      mem_.store(0, mem_.load(0) + ins_.number);
    }else{
      if(ins_.symbol=='*'){
        mem_.store(0, mem_.load(0) + mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) + mem_.load(ins_.number));
      }
    }
  }

  if(ins_.instruc_=="sub" || ins_.instruc_=="SUB"){
    if(ins_.symbol=='='){
      mem_.store(0, mem_.load(0) - ins_.number);
    } else{
        if(ins_.symbol=='*'){
        mem_.store(0, mem_.load(0) - mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) - mem_.load(ins_.number));
      }
    }
  }

  if(ins_.instruc_=="mul" || ins_.instruc_=="MUL"){
    if(ins_.symbol=='='){
      mem_.store(0, mem_.load(0) * ins_.number);
    }else{
      if(ins_.symbol=='*'){
        mem_.store(0, mem_.load(0) * mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) * mem_.load(ins_.number));
      }
    }
  }

  if(ins_.instruc_=="jump" || ins_.instruc_=="JUMP"){
    jump_to_=pr_.get_next_jump(ins_.op_);
    // std::cout << "jump_to:" << jump_to_ << "\n";
  }

  if(ins_.instruc_=="jzero" || ins_.instruc_=="JZERO"){
    if(mem_.load(0)==0){
      jump_to_=pr_.get_next_jump(ins_.op_);
      // std::cout << "jump_to:" << jump_to_ << "\n";
    }else{
      jump_to_=-1;
    }
  }


}


int simulator::next_inst(void){
  return jump_to_;
}