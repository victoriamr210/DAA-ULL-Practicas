#include "../include/ram.hpp"

RAM::RAM(memory &m, program &p, input_tape &i, output_tape &o){
  mem_ = m;
  pr_ = p;
  input_ = i;
  output_ = o;
}

void RAM::set_i(instruction &i){
  ins_ = i;
}

void RAM::print_mem(void){
  mem_.print();
}

void RAM::print_output(void){
  output_.print();
}

int RAM::next_inst(void){
  return jump_to_;
}

void RAM::print_labels(void){
  pr_.print_label();
}

void RAM::print_program(void){
  pr_.print_ins();
}

void RAM::print_input(void){
  input_.print();
}

void RAM::write_file(void){
  output_.write_file();
}

void RAM::execute(void){


  if(ins_.instruc_=="read" || ins_.instruc_=="READ"){
    mem_.store(ins_.number,input_.read());
  
  }else if(ins_.instruc_=="load" || ins_.instruc_=="LOAD"){
    
    if(ins_.symbol == '='){
      mem_.store(0,ins_.number);
    }else{
      if(ins_.symbol == '*'){
        mem_.store(0,mem_.load(mem_.load(ins_.number)));
      }
      mem_.store(0,mem_.load(ins_.number));
    }

  }else if(ins_.instruc_=="store" || ins_.instruc_=="STORE"){
    if(ins_.symbol == '='){
      std::string e = "Instruccion ilegal";
      throw e;
    }else{
      if(ins_.symbol=='*'){
        mem_.store(mem_.load(mem_.load(ins_.number)),mem_.load(0));
      }
      mem_.store(ins_.number,mem_.load(0));
    }

  }else if(ins_.instruc_=="write" || ins_.instruc_=="WRITE"){
    if(ins_.symbol == '='){
      output_.write(ins_.number);
    }else{
      if(ins_.number == 0){
        std::string e = "Instruccion ilegal";
        throw e;
      } else{
        if(ins_.symbol == '*'){
          output_.write(mem_.load(mem_.load(ins_.number)));
        }else{
          output_.write(mem_.load(ins_.number));
        }
      }
    }

  } else if(ins_.instruc_=="add" || ins_.instruc_=="ADD"){
    if(ins_.symbol == '='){
      mem_.store(0, mem_.load(0) + ins_.number);
    }else{
      if(ins_.symbol == '*'){
        mem_.store(0, mem_.load(0) + mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) + mem_.load(ins_.number));
      }
    }

  }else if(ins_.instruc_=="sub" || ins_.instruc_=="SUB"){
    if(ins_.symbol == '='){
      mem_.store(0, mem_.load(0) - ins_.number);
    } else{
        if(ins_.symbol == '*'){
        mem_.store(0, mem_.load(0) - mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) - mem_.load(ins_.number));
      }
    }

  }else if(ins_.instruc_=="mul" || ins_.instruc_=="MUL"){
    if(ins_.symbol == '='){
      mem_.store(0, mem_.load(0) * ins_.number);
    }else{
      if(ins_.symbol == '*'){
        mem_.store(0, mem_.load(0) * mem_.load(mem_.load(ins_.number)));
      }else{
        mem_.store(0, mem_.load(0) * mem_.load(ins_.number));
      }
    }

  }else if(ins_.instruc_=="div" || ins_.instruc_=="DIV"){
    if(ins_.symbol == '='){
      if(ins_.number == 0){
        std::string e = "Division entre 0, ilegal";
        throw e;
      }else{
       mem_.store(0, mem_.load(0) / ins_.number);
      }
    }else{
      if(ins_.symbol == '*'){
        if(mem_.load(mem_.load(ins_.number))==0){
          std::string e = "Division entre 0, ilegal";
          throw e;
        }else{
          mem_.store(0, mem_.load(0) / mem_.load(mem_.load(ins_.number)));
        }
      }else{
        if(mem_.load(ins_.number) == 0){
          std::string e = "Division entre 0, ilegal";
          throw e;
        }else{
          mem_.store(0, mem_.load(0) * mem_.load(ins_.number));
        }
      }
    }

  }else if(ins_.instruc_=="jump" || ins_.instruc_=="JUMP"){
    jump_to_=pr_.get_next_jump(ins_.op_);

  }else if(ins_.instruc_=="jzero" || ins_.instruc_=="JZERO"){
    if(mem_.load(0) == 0){
      jump_to_ = pr_.get_next_jump(ins_.op_);
    }else{
      jump_to_ = -1;
    }
  
  }else if(ins_.instruc_=="jgtz" || ins_.instruc_=="JGTZ"){
    if(mem_.load(0) > 0){
      jump_to_ = pr_.get_next_jump(ins_.op_);
    }else{
      jump_to_ = -1;
    }
  }else{
    std::string e ="Instruccion no existe" + ins_.instruc_;
    throw e;
  }


}


