#include "../include/cinta.hpp"

std::vector<int> tape::get_tape(void){
  return t_;
}

int tape::get_head(void){
  return head_;
}

input_tape::input_tape(char* f){
  file_=f;
  t_.resize(10);
  readFile();
}

int input_tape::read(void){
  head_++;
  return t_[head_-1];
}

void input_tape::readFile(void){
  std::fstream f;

  f.open(file_);
  
  int aux;

  int i=0;
  if(f.is_open()){
    while(!f.eof()){
      f >> aux;
      t_[i]=aux;
      i++;
    }
  }else{
    std::cout << "Error de apertura\n";
  }

}

void input_tape::print(void){
  std::cout << "Cinta entrada\n ";
  for(int i=0; i<t_.size(); i++){
    std::cout << i << ": " << t_[i] << "/";
  }
  std::cout << "\n\n";
}

output_tape::output_tape(char* f){
  file_=f;
  t_.resize(10);
}

void output_tape::write(int a){
  t_[head_]=a;
  head_++;
}

void output_tape::write_file(void){
  std::fstream f;
  f.open(file_);
  int i=0;
  if(f.is_open()){
    while(i<t_.size()){
      f << t_[i];
      f << "\n";
      i++;
    }
  }else{
    std::cout << "Error de apertura\n";
  }

}

void output_tape::print(void){
  std::cout << "Cinta salida\n";
  for(int i=0; i<t_.size(); i++){
    std::cout << i << ": " << t_[i] << " | ";
  }
  std::cout << "\n\n";
}

