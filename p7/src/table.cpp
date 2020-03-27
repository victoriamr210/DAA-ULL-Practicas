#include "../include/table.hpp"
#include <iomanip>
#include <algorithm>

table::table(std::string top, std::string sub){
  topString_ = top;
  subString_ = sub;
  row = subString_.size() + 1;
  col = topString_.size() + 1;
  std::cout << "Primera cadena: " << topString_ << "\n";
  std::cout << "Segunda cadena: " << subString_ << "\n\n";
  v_.resize(row*col);
  build_empty();
  fill_table();
  // std::cout << pos(0,3);


}

int table::pos(int i, int j){
  return((i)*col+j);
}

void table::build_empty(void){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      v_[pos(i,j)] = 0;
    }
  }
}

void table::fill_table(void){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      v_[pos(i,j)] = LCS(i,j);
    }
  }
}

int table::LCS(int i, int j){
  // std::cout << i <<" "<<j << "\n";
  if((i==0) || (j==0)){
    return 0;
  } else {
    // std::cout << subString_[i-1] << " " << topString_[j-1] << "\n";
    if(subString_[i-1] == topString_[j-1]){
  // std::cout << "hola\n";
      return 1 + LCS(i-1, j-1);
    } else {
      return std::max(LCS(i-1,j), LCS(i,j-1));
    }
  }
}

std::string table::solution(void){
  std::string sol = "";
  int i = row-1;
  int j = col-1;
  int aux=-1;
  while((i>=0) && (j>=0)){
    aux=v_[pos(i,j)];
    if(aux == 0){
      break;
    }
    if((v_[pos(i-1,j)]) == aux-1 && (v_[pos(i,j-1)] == aux-1)){
      sol = subString_[i-1] + sol;
      i--;
      j--;
    } else{
    // std::cout << "i-1:" << v_[pos(i-1,j)] << " j-1:" << v_[pos(i,j-1)] << "\n";
      if ((v_[pos(i,j-1)]) == aux-1 && (v_[pos(i-1,j)] == aux-1)){
        i--;
      } else {
        if ((v_[pos(i,j-1)]) == aux && (v_[pos(i-1,j)] < aux)){
          j--;
        }
      }
    } 
  }
  return sol;
  // std::cout << sol << " " << sol.size() << "\n";
}

void table::write(void){
  std::cout  << std::setw(7);
  for(int i = 0; i < topString_.size(); i++){
    std::cout << topString_[i] << std::setw(2);
  }
  std::cout << "\n";
  std::cout << std::setw(5);
  for(int i = 0; i < col; i++){
    std::cout << i << " ";
  }
  std::cout << "\n";


  for (int i = 0; i < row; i++){
    if(i > 0){
    std::cout << subString_[i-1] << std::setw(2) << i << std::setw(2);
    } else {
      std::cout << std::setw(3) << i << std::setw(2);
    }
    for(int j = 0; j < col; j++){
      std::cout <<  v_[pos(i,j)] << std::setw(2);
    }
    std::cout << "\n";
  }
}
