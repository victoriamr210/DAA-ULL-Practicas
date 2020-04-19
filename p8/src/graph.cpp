#include "../include/graph.hpp"
#include <iomanip>

graph::graph(char file[]){
  read(file);
}

void graph::read(char file[]){
  std::fstream f;
  f.open(file);
  if(f.is_open()) {
    f >> nodes_;
    std::cout << nodes_ << "\n";
    d_.resize(nodes_ * nodes_, -1);
    set_d();
    int i = 0;
    int j = 1;
    // int rows = (rows * (row))
    float r;

    while((!f.eof()) && (i<nodes_)) {
      f >> r;
      set_item(r, i, j);
      j++;

      if (j == nodes_){
        i++;
        j=0;
      }
    }
    f.close();
  }else {
    std::cerr << "Error de apertura\n";
  }
}

void graph::set_d(void){
  for(int i=0; i < nodes_; i++) {
    d_[pos(i,i)] = 0;
  }
}

void graph::set_item(float r, int i, int j) {
  if(i!=j && (d_[pos(i,j)] == -1)){
    d_[pos(i, j)] = r;
    d_[pos(j, i)] = r;

  }else {
    while(d_[pos(i,j)] != 0){
      j++;
    }
    if (i==j) {
      j++;
    }
    d_[pos(i, j)] = r;
    d_[pos(j, i)] = r;
  }
}

int graph::pos(int i, int j) {
  return ((i)*nodes_)+j;
}

void graph::write(void){
  for(int i=0; i<nodes_; i++){
    for(int j=0; j<nodes_; j++){
      std::cout << std::setw(3) << d_[pos(i,j)] << std::setw(3) << " ";
    }
    std::cout << "\n";
  }
}