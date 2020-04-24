#include "../include/graph.hpp"
#include <iomanip>
#include <cmath>
#include <cstdlib>

graph::graph(char file[]){
  read(file);
}

graph::graph(graph &g){

}

void graph::read(char file[]){
  std::cout << "before\n";
  // write();
  std::fstream f;
  f.open(file);
  if(f.is_open()) {
    f >> nodes_;
    std::cout << nodes_ << "\n";
    d_.resize(nodes_ * nodes_, INFINITY);
    set_d();
    int i = 0;
    int j = 1;
    // int rows = (rows * (row))
    float r;

    while((!f.eof()) && (i<nodes_) && (j<nodes_)) {
      // std::cout << "i:" << i << "j:" << j << "\n";
      f >> r;
      set_item(r, i, j);
      // std::cout << "set\n";
      j++;

      if (j == nodes_){

        i++;
        j=i+1;
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

std::vector<float> graph::get_graph(void){
  return d_;
}

int graph::get_nodes(void) {
  return nodes_;
}

float graph::get_item(int i, int j){
  return d_[pos(i,j)];
}

void graph::set_item(float r, int i, int j) {
  if(i!=j){
    // std::cout << "if\n";
    d_[pos(i, j)] = r;
    d_[pos(j, i)] = r;

  }
}

void graph::set_sol(solution s) {
  sol_ = s;
}

int graph::pos(int i, int j) {
  return ((i)*nodes_)+j;
}


std::pair<int,int> graph::maximum(void) {
  srand(time(NULL)); 
  std::vector<std::pair<int,int>> v;
  // int i = rand() % nodes_;
  // int j = rand() % nodes_;
  
  int max = -99999999;
  std::pair<int, int> par;
  par.first = 0;
  for (int i = 0; i < nodes_; i++) {
    for (int j = 0; j < nodes_; j++){
      if (d_[pos(i,j)] > max && i!=j) {
        max = d_[pos(i,j)];
        par.second = j;
      }
    }
  }
  v.push_back(par);
  for (int i = 0; i < nodes_; i++) {
    for (int j = 0; j < nodes_; j++){
      if ((d_[pos(i,j)] == max) && i!=j) {
        v.push_back(std::make_pair(i,j));
        // max = d_[pos(i,j)];
        // par.second = j;
      }
    }
  }
  // std::cout << "max:" << max << "\n";
  // std::cout << "f:" << par.first;
  // std::cout << " s:" << par.second << "\n";
  if (v.size() == 1) {
    return par;
  } else {
    int index = rand() % v.size();
    return v[index];
  }
  
   
    // return par;
}

void graph::write(void){
  for(int i=0; i<nodes_; i++){
    for(int j=0; j<nodes_; j++){
      std::cout << std::setw(3) << d_[pos(i,j)] << std::setw(3) << " ";
    }
    std::cout << "\n";
  }
}

void graph::write_sol(void){
  // for(auto i : sol_){
  //   std::cout << i << " ";
  // }
  // std::cout <<"\n";
  // std::cout << "mean: " << mean_ << "\n";
  sol_.write();
}