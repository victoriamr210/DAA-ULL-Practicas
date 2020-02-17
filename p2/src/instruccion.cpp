#include "../include/instruccion.hpp"

instruction::instruction(std::string i){
  reset();
  set(i);
}

void instruction::set(std::string i){
  reset();
  int pos=i.find(" ");
  instruc_=i.substr(0,(i.size()-(i.size()-pos)));
  op_=i.substr(pos+1, i.size()-pos);

  set_op();
}

bool instruction::is_halt(void){
  std::string halt="halt";
  std::string HALT="HALT";
  if(instruc_==halt || instruc_==HALT)
    return true;
  return false;
}

void instruction::set_op(void){
  if(op_[0]=='='){
    std::cout << "entra\n";
    symbol=op_[0];
    std::stringstream x(op_.substr(1,op_.size()-1));
    x >> number;
  }

  if(op_[0]=='*'){
    symbol=op_[0];
    std::stringstream x(op_.substr(1,op_.size()-1));
    x >> dir;
  }

  if(std::isdigit(op_[0])){
    std::stringstream x(op_);
    x >> number;
  }
  
  if(instruc_=="jump" || instruc_=="JUMP" || 
    instruc_=="jzero" || instruc_=="JZERO"){
      jump=true;
    }
}

void instruction::reset(void){
  symbol='n';
  jump=false;
  number=-1;
  dir=-1;
  instruc_="";
  op_="";
}

void instruction::print(void){
  std::cout << instruc_ << " " << op_ << "\n";
}
