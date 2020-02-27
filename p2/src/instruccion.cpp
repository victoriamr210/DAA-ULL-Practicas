#include "../include/instruccion.hpp"

instruction::instruction(std::string i){
  reset();
  set(i);
}

void instruction::set(std::string i){
  reset();
  int pos=i.find(" ");
  instruc_ = i.substr(0,(i.size()-(i.size()-pos)));
  op_ = i.substr(pos+1, i.size()-pos);

  set_op();
}

bool instruction::is_halt(void){
  std::string halt="halt";
  std::string HALT="HALT";
  if(instruc_ == halt || instruc_ == HALT)
    return true;
  return false;
}

void instruction::set_op(void){
  keyword();
  if(op_[0] == '='){
    symbol=op_[0];
    std::stringstream x(op_.substr(1,op_.size()-1));
    x >> number;
    opcode+= "0";
    opcode+= op_.substr(1,op_.size()-1);
  }

  if(op_[0] == '*'){
    symbol = op_[0];
    std::stringstream x(op_.substr(1,op_.size()-1));
    x >> dir;
    opcode+= "1";
    opcode+= op_.substr(1,op_.size()-1);

  }

  if(std::isdigit(op_[0])){
    std::stringstream x(op_);
    x >> number;
    opcode+= "3";
    opcode+= op_;
  }
  
  if(instruc_ ==" jump" || instruc_ == "JUMP" || 
    instruc_ == "jzero" || instruc_ == "JZERO" ||
    instruc_ == "jgtz" || instruc_ == "JGTZ"){
      jump = true;
    }
}

void instruction::reset(void){
  symbol = 'n';
  jump = false;
  number = -1;
  dir = -1;
  instruc_ = "";
  op_ = "";
  opcode = "";
}

void instruction::print(void){
  std::cout << instruc_ << " " << op_ << "\n";
}

void instruction::desc(void){
  std::cout << instruc_ << " " << op_ << " ";
  if(instruc_ == "read" || instruc_ == "READ"){
    std::cout << "Leer cinta y se guarda en " << op_;
  
  }else if(instruc_ == "load" || instruc_ == "LOAD"){
    if(symbol == '='){
      std::cout << "Cargar en acc el numero " << number;
    }else{
      if(symbol == '*'){
        std::cout << "Guardar en acc el numero guardado en el registro " << number;
      }
      std::cout << "Cargar en acc el registro " << number;
    }

  }else if(instruc_ == "store" || instruc_ == "STORE"){
    if(symbol == '='){
      std::string e = "Instruccion ilegal";
      throw e;
    }else{
      if(symbol == '*'){
        std::cout << "Contenido del acc al registro apuntado por " << number;
      }
      std::cout << "Contenido del acc al registro " << number;
    }

  }else if(instruc_ == "write" || instruc_ == "WRITE"){
    if(symbol == '='){
      std::cout << "Escribir en cinta " << number;
    }else{
      if(symbol == '*'){
        std::cout << "Escribir en cinta lo apuntado por el registro " << number;
      }else{
        std::cout << "Escribir en cinta el registro " << number;
      }
    }

  } else if(instruc_ == "add" || instruc_ == "ADD"){
    if(symbol == '='){
      std::cout << "Sumar al acc " << number;
    }else{
      if(symbol == '*'){
        std::cout << "Sumar al acc lo apuntado por " << number;
      }else{
        std::cout << "Sumar al acc el registro " << number;
      }
    }

  }else if(instruc_ == "sub" || instruc_ == "SUB"){
    if(symbol == '='){
      std::cout << "Restar al acc " << number;
    } else{
        if(symbol == '*'){
        std::cout << "Restar al acc lo apuntado por " << number;
      }else{
        std::cout << "Restar al acc el registro " << number;
      }
    }

  }else if(instruc_ == "mult" || instruc_ == "MULT"){
    if(symbol == '='){
      std::cout << "Multiplicar al acc " << number;
    }else{
      if(symbol == '*'){
        std::cout << "Multiplicar al acc lo apuntado por " << number;
      }else{
        std::cout << "Multiplicar al acc el registro " << number;
      }
    }

  }else if(instruc_ == "div" || instruc_ == "DIV"){
    if(symbol == '='){
        std::cout << "Dividir al acc " << number;
    }else{
      if(symbol == '*'){
        std::cout << "Dividir al acc lo apuntado por " << number;
      }else{
        std::cout << "Dividir al acc el registro " << number;
      }
    }

  }else if(instruc_ == "jump" || instruc_ == "JUMP"){
    std::cout << "Salta a etiqueta " << op_;

  }else if(instruc_ == "jzero" || instruc_ == "JZERO"){
    std::cout << "Si acc == 0 saltar a " << op_;
  
  }else if(instruc_ == "jgtz" || instruc_ == "JGTZ"){
    std::cout << "Si acc > 0 saltar a " << op_;
  }else{
    std::string  e= "Instruccion no existe";
    throw e;    
  }
}

void instruction::get_opcode(void){
  std::cout << opcode << "\n";
}

void instruction::keyword(void){
  if(instruc_ == "load" || instruc_ == "LOAD") opcode+="01";
  else if(instruc_ == "store" || instruc_ == "STORE") opcode+="02";
  else if(instruc_ == "add" || instruc_ == "ADD") opcode+="03";
  else if(instruc_ == "sub" || instruc_ == "SUB") opcode+="04";
  else if(instruc_ == "mult" || instruc_ == "MULT") opcode+="05";
  else if(instruc_ == "div" || instruc_ == "DIV") opcode+="06";
  else if(instruc_ == "read" || instruc_ == "READ") opcode+="07";
  else if(instruc_ == "write" || instruc_ == "WRITE") opcode+="08";
  else if(instruc_ == "jump" || instruc_ == "JUMP") opcode+="09";
  else if(instruc_ == "jgtz" || instruc_ == "JGTZ") opcode+="10";
  else if(instruc_ == "jzero" || instruc_ == "JZERO") opcode+="11";
  else if(instruc_ == "halt" || instruc_ == "HALT") opcode+="12";
  else opcode+="xx";
}