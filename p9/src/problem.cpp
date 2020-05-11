#include <iostream>
#include "../include/problem.hpp"
#include <fstream>
#include <iomanip>
#include <math.h>

Problem::Problem(char file []){
  read(file);
}



void Problem::read(char file[]){
  std::fstream f;
  f.open(file);

  if(f.is_open()) {
    f >> n_;
    f >> k_;
    v_.resize(n_ * k_);
    // std::cout << "size:" << v_.size() << "\n";
    int i = 0;
    int j = 0;
    float number;
    for(int i = 0; i < n_; i++){
     for(int j = 0; j < k_; j++){
      // std::cout << i << " " << j << "\n";
      // std::cout << "n:" << number << "\n";
      f >> number;
      set_item(number, i, j);
      
      }
   }
    f.close();
  } else {
    std::cerr << "Error de apertura\n";
  }
}

int Problem::pos(int i, int j){
  return ((i) * k_)+j;
}

void Problem::set_item(float r, int i, int j){
  v_[pos(i,j)] = r;
}

float Problem::get_item(int i, int j){
  return v_[pos(i,j)];
}

int Problem::get_elements(void){
  return n_;
}

int Problem::get_dimension(void){
  return k_;
}

void Problem::write(void ){
  for(int i = 0; i < n_; i++){
    for(int j = 0; j < k_; j++){
      std::cout << std::setw(3) << v_[pos(i, j)] << std::setw(3) << " ";
    } 
    std::cout << "\n";
  }
}

std::vector<float> Problem::center(std::vector<int> s){
  std::vector<float> aux(k_);
  for(int j = 0; j < k_; j++){
    for(int i = 0; i < s.size(); i++){
      aux[j] += get_item(s[i], j);
    }
  }

  for(int i = 0; i < k_; i++){
    aux[i] = aux[i] / s.size();
  }
  return aux;
}


float Problem::get_distance(int first, int second){
  float aux = 0;
  for(int i = 0; i < k_; i++){
    aux += pow(get_item(first, i) - get_item(second, i), 2);
  }
  aux = sqrt(aux);
  return aux;
}