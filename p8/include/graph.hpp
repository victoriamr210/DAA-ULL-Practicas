#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <utility>
#include "solution.hpp"

class graph {

  private:
    /*Numero de nodos*/
    int nodes_;
    /*matriz de disancias implementada como vector*/
    std::vector<float> d_;
    // std::vector<int> sol_;
    solution sol_;
    float mean_;
  
  public:
    graph(char file[]); //constructor dado un nombre de fichero
    graph(graph &g); //constructor de copia
    graph(){} //constructor por defecto
    void read(char file[]); //lee le fichero y guarda los valores
    int pos(int i, int j); //devuelve la posicion relativa al vector
    void set_item(float num, int i, int j);  //guarda elemento en posicion indicada
    void set_d(void); //diagonal de la matriz a cero
    void write(void); //imprimir matriz de distancias
    std::pair<int, int> maximum(void); //devuelve arista de mayor afinidad
    std::vector<float> get_graph(void); // getter de la matriz de distancias
    int get_nodes(void); //getter del numero de nodos
    float get_item(int i, int j); //deveulve elemento en la posicion indicada
    void set_sol(solution s);
    void write_sol(void);
}; 