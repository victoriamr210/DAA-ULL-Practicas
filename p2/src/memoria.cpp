#include "../include/memoria.hpp"

memory::memory(void){
  m_.resize(10);
}

void memory::store(int pos, int val){
  m_[pos]=val;
}

int memory::load(int pos){
  m_[0]=m_[pos];
}

void memory::print(void){
  std::cout << "Memoria:\n";
  std::cout << "acc: " << m_[0] << " | ";
  for(int i=1; i<m_.size(); i++){
    std::cout <<"R[" << i << "]" << ":" << m_[i] << " | ";
  }
  std::cout << "\n\n";
}