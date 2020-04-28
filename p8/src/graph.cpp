#include "../include/graph.hpp"
#include <iomanip>
#include <cmath>
#include <cstdlib>
/**
 * @brief Constructor dado un nombre de fichero
 * 
 * @param file fihchero
 */
graph::graph(char file[]){
  read(file);
}

/**
 * @brief Constructor de copia
 * 
 * @param g 
 */
graph::graph(graph &g){

}

/**
 * @brief Lee le fichero y guarda los valores
 * 
 * @param file fichero
 */
void graph::read(char file[]){
  // write();
  std::fstream f;
  f.open(file);
  if(f.is_open()) {
    f >> nodes_;
    std::cout << nodes_ << " nodos\n";
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

/**
 * @brief Dagonal de la matriz a cero
 * 
 */
void graph::set_d(void){
  for(int i=0; i < nodes_; i++) {
    d_[pos(i,i)] = 0;
  }
}

/**
 * @brief Getter de la matriz de distancias
 * 
 * @return std::vector<float> 
 */
std::vector<float> graph::get_graph(void){
  return d_;
}

/**
 * @brief Getter del numero de nodos
 * 
 * @return int 
 */
int graph::get_nodes(void) {
  return nodes_;
}

/**
 * @brief Deveulve elemento en la posicion indicada
 * 
 * @param i fila
 * @param j columna
 * @return float 
 */
float graph::get_item(int i, int j){
  return d_[pos(i,j)];
}

/**
 * @brief Guarda elemento en posicion indicada
 * 
 * @param num elemento a guardar
 * @param i fila
 * @param j columna
 */
void graph::set_item(float num, int i, int j) {
  if(i!=j){
    d_[pos(i, j)] = num;
    d_[pos(j, i)] = num;

  }
}


void graph::set_sol(solution s) {
  sol_ = s;
}

/**
 * @brief Devuelve la posicion relativa al vector
 * 
 * @param i fila
 * @param j columna
 * @return int 
 */
int graph::pos(int i, int j) {
  return ((i)*nodes_)+j;
}

/**
 * @brief Devuelve arista de mayor afinidad
 * 
 * @return std::pair<int,int> 
 */
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

/**
 * @brief Imprimir matriz de distancias
 * 
 */
void graph::write(void){
  for(int i=0; i<nodes_; i++){
    for(int j=0; j<nodes_; j++){
      std::cout << std::setw(3) << d_[pos(i,j)] << std::setw(3) << " ";
    }
    std::cout << "\n";
  }
}

void graph::write_sol(void){
  sol_.write();
}