#include "../include/programa.hpp"

program::program(char* file){
  build(file);
}

void program::build(char* file){
  
  std::fstream f;
  f.open(file);
  std::string aux;
  std::string aux2;
  if(f.is_open()){
    while(!f.eof()){

      f >> aux;

      if(aux == "#"){
        while(f.peek() != '\n'){
          f >> aux;
        }
      }else{
        if(aux.back() == ':'){
          aux.pop_back();
          std::pair <std::string,int> t(aux,ins_.size());
          label_.push_back(t);
        }else{
          if(aux == "HALT" || aux == "halt"){
            ins_.push_back(aux);
          }else{
            aux2=aux;
            aux2+=" ";
            f >> aux;
            aux2+=aux;
            ins_.push_back(aux2);
          }  
        }
      }
    }
  }else{
    std::cout << "Error de apertura\n";

  }

}


void program::print_ins(void){

  std::cout << "Instrucciones: \n";
  for(int i=0; i<ins_.size(); i++){
    std::cout << i << ":" << ins_[i] << " | ";
  }
  std::cout << "\n\n";
}


void program::print_label(void){

  std::cout << "Etiquetas: \n";
  for(int i=0; i<label_.size(); i++){
    std::cout << label_[i].first << ":" << label_[i].second << " | ";
  }
  std::cout << "\n\n";
}