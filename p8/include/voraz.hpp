#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"

/*Clase que implementa el algoritmo constructivo voraz*/
class voraz : public algoritmo{
  /*Funcion que inica la ejecucion*/
  std::vector<solution> solutions_;
  void solve(graph &g) {
 
    solution a = execute(g);
    a.write();

  }

  /* Funcion principal que implementa el algortimo voraz*/
  solution execute(graph &g){

    std::vector<int> s; //conjunto de nodos de la solucion
    std::pair<int,int> p = g.maximum(); //hallamos nodos que contiene la arista de mayor afinidad
    s.push_back(p.first);
    s.push_back(p.second);
    float mean = g.get_item(p.first, p.second) / 2;
    std::vector<int> s_prima; //conjunto auxiliar
    while(s_prima.size() != s.size() ) { //mientras el conjunto cambie
      s_prima = s;
      int node = find_k(s, g, mean); //buscamos un vertice k que maximize la media
      if (node == -1) { //si el nodo es -1 sigfinca no se hay encontrado ningun vertice
        break;
      } else {
        s.push_back(node); //guardamos el nodo en la solución
      }
    }
    // std::cout << "final:" << mean << "\n";
    return solution(s, mean); //generamos la solucion

  }

  /* Funcion que encuentra un vertice k que maximize la media de dispersión*/
  int find_k(std::vector<int> &s, graph &g, float &mean) {
    int node = -1;
    float aux_mean = mean; //guardamos la media consiguida hasta ahora
    float aux_mean2;
    std::vector<int> v;
      for (int j = 0;  j < g.get_nodes(); j++){
        
        if (valid(s,j)) { //comprobamos si el nodo j no se encuentra en la solución
          std::vector<int> aux = s;
          aux.push_back(j); //guardamos el nodo en nuestra solucion a evaluar
          aux_mean2 = getMd(aux, g); //calculamos la media de nuestra solucion auxiliar
           if (aux_mean2 > aux_mean) {  //actualizamos la media en caso de se mayor
            node = j;
            v.clear();
            v.push_back(j);
            aux_mean = aux_mean2;
          } else if(aux_mean2 == aux_mean){ //si encontramos un nodo que genere una media igual a 
              v.push_back(j);               //la guardamos en un vector
          }
        }
      }
    if(aux_mean >= mean) {  //actualizamos la media global
      mean = aux_mean;
      if(v.size() > 1){
        return v[rand() % v.size()]; //en caso de que hayan varios nodos que den la misma media, elegimos uno al azar
      }
      return node; //retornamos el nodo que maximiza la media
    } else {
      return -1;
    }
  }

  /* Funcion que calcula la media de dispersión de un conjunto de nodos*/
  float getMd(std::vector<int> s, graph &g) {
    float sum;
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        sum += g.get_item(s[i],s[j]);

      }
    // std::cout << "\n";
    }
    return sum / s.size();
  }

  /*Funcion que comprueba si el nodo candidato existe en la solución o no*/
  bool valid(std::vector<int> &s, int j) {
    for(int k = 0; k < s.size(); k++){
      if(s[k] == j){
        return false;
      }
    }
    return true;
  }
};