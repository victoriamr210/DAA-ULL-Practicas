#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"
#include <algorithm>

/*Clase que implementa el algoritmo constructivo voraz mejorado*/
class new_voraz : public algoritmo{
  std::vector<solution> solutions_;
  void solve(graph &g) {
    // for (int i = 0; i < 20; i++) {
    //   solutions_.push_back(execute(g));
    // }
    solution a = execute(g);
    a.write();

  }
  /*Funcion que crea un vector con todos los nodos existentes*/
  void build_list(std::vector<int> &s, int size){
    s.resize(size);
    for(int i = 0; i < size; i++){
      s[i] = i;
    }
  }
  /*Funcion que elimina un elemento del vector*/
  void delete_item(std::vector<int> &s, int num){
    s.erase(std::find(s.begin(), s.end(), num));
  }
  /* Funcion principal que implementa el algortimo voraz*/
  solution execute(graph &g){

    std::vector<int> s;
    build_list(s, g.get_nodes()); //creamos un conjunto S con todos los nodos existentes
    // std::pair<int,int> p = g.maximum();
    float mean = getMd(s, g); //generamos la media del conjunto S
    std::vector<int> s_prima; //conjunto S* que nos servira para comparar
    while(s_prima.size() != s.size()) {
      s_prima = s;
      int node = find_k(s, g, mean); //buscamos un nodo k que maximize la media que se debe eliminar
      if (node == -1) {
        break;
      } else {
        delete_item(s, node); //eliminamos el nodo de la solucion
        mean = getMd(s, g); //calculamos su media.
      }
      
    }
    // std::cout << "final:" << mean << "\n";
    return solution(s, mean);
    // g.set_sol(s, mean);

  }

  /* Funcion que encuentra un vertica k que maximize la media de dispersión
  para quitarlo del conjunto*/
  int find_k(std::vector<int> &s, graph &g, float &mean) {
    int node = -1;
    float aux_mean = mean; //media auxliar para comparar
    float aux_mean2; //media auxliar donde se guardaran los calculos
    std::vector<int> v;
      for (int j = 0;  j < s.size(); j++){
          std::vector<int> aux = build_check(s,s[j]); //generamos un conjnto auxliar con el nodo condidato a ser eliminado
          aux_mean2 = getMd(aux, g);
          if (aux_mean2 > aux_mean) { //actualizamos la media si resulta ser mayor
            node = s[j];
            v.clear();
            v.push_back(s[j]);
            aux_mean = aux_mean2;
          } else if(aux_mean2 == aux_mean){ //si se encuentra un nodo que maximiza la media en la misma medida se guarda
              v.push_back(s[j]);
          }
      }
      // std::cout << "\nnode:" << node << " final:" << aux_mean << "\n\n";

      //retornar el nodo que maximiza la media
      if(v.size() > 1){ 
        int index = rand() % v.size();
        return v[index];
      }
      return node;
  }

  /* Funcion que calcula la media de dispersión de un conjunto de nodos*/
  float getMd(std::vector<int> s, graph &g) {
    float sum;
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        sum += g.get_item(s[i],s[j]);

      }
    }
    return sum / s.size();
  }

  /*Funcion que crea un vector sin el elemento que se le manda*/
  std::vector<int> build_check(std::vector<int> s, int num){
    std::vector<int> aux;
    for(int i = 0; i < s.size(); i++){
      if(s[i] != num){
        aux.push_back(s[i]);
      }
    }
    return aux;
  }

  /*Funcion que comprueba si el nodo candidato existe en la solución o no*/
  bool valid(std::vector<int> &s, int j) {
    for(int k = 0; k < s.size(); k++){
      if(s[k] == j){
        return true;
      }
    }
    return false;
  }
  /*Funcion que escribe un vector*/
  void write(std::vector<int> s){
    for(int i = 0; i < s.size(); i++){
      std::cout << s[i] << " ";
    }
    std::cout << "\n";
  }
};