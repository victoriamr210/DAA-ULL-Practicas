#include "../include/table.hpp"
#include <iomanip>

table::table(std::string top, std::string sub){
  topString_ = top;
  subString_ = sub;
  row = subString_.size();
  col = topString_.size();
  v_.resize(row*col);
  build_empty();
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

void table::write(void){
  std::cout << std::setw(4);
  for(int i = 0; i < topString_.size(); i++){
    std::cout << topString_[i] << std::setw(2);
  }
  std::cout << "\n";

  for (int i = 0; i < row; i++){
    std::cout << subString_[i] << std::setw(3);
    for(int j = 0; j < col; j++){
      std::cout <<  v_[pos(i,j)] << std::setw(2);
    }
    std::cout << "\n";
  }
}
