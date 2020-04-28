#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"
#include <algorithm>

/**
 * @brief Clase que implementa el algoritmo constructivo voraz mejorado
 * 
 */
class new_voraz : public algoritmo{
  /**
   * @brief Funcion principal, inicia la ejecucion
   * 
   * @param g matriz de distancias
   */
  void solve(graph &g, bool greedy) {
    auto t1 = std::chrono::high_resolution_clock::now();
    solution a = execute(g);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    a.set_time(duration);
    a.write();

  }

  /**
   * @brief Funcion que crea un vector con todos los nodos existentes
   * 
   * @param s vector
   * @param size tamaño del vector
   */
  void build_list(std::vector<int> &s, int size){
    s.resize(size);
    for(int i = 0; i < size; i++){
      s[i] = i;
    }
  }

  /**
   * @brief Funcion que elimina un elemento del vector
   * 
   * @param s vector
   * @param num elemento a eliminar
   */
  void delete_item(std::vector<int> &s, int num){
    s.erase(std::find(s.begin(), s.end(), num));
  }

  /**
   * @brief Funcion principal que implementa el algortimo voraz
   * 
   * @param g matriz de distancias
   * @return solution 
   */
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

  /* Funcion que encuentra un vertice k que maximize la media de dispersión
  para quitarlo del conjunto*/
  /**
   * @brief Funcion que encuentra un vertice k que maximize la media de dispersión
   * para quitarlo del conjunto
   * 
   * @param s vector de nodos
   * @param g matriz de distancias
   * @param mean media global
   * @return int 
   */
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

      if(v.size() > 1){ 
        int index = rand() % v.size();
        return v[index];
      }
      return node;
  }

  /**
   * @brief Funcion que calcula la media de dispersión de un conjunto de nodos
   * 
   * @param s vector de nodos
   * @param g matriz de distancias
   * @return float 
   */
  float getMd(std::vector<int> s, graph &g) {
    float sum;
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        sum += g.get_item(s[i],s[j]);

      }
    }
    return sum / s.size();
  }

  /**
   * @brief Funcion que crea un vector sin el elemento que se le manda
   * 
   * @param s vector de nodos
   * @param num numero a ignorar
   * @return std::vector<int> 
   */
  std::vector<int> build_check(std::vector<int> s, int num){
    std::vector<int> aux;
    for(int i = 0; i < s.size(); i++){
      if(s[i] != num){
        aux.push_back(s[i]);
      }
    }
    return aux;
  }

  /**/
  /**
   * @brief Funcion que comprueba si el nodo candidato existe en la solución o no
   * 
   * @param s vector de nodos
   * @param num numero a comprobar
   * @return true 
   * @return false 
   */
  bool valid(std::vector<int> &s, int num) {
    for(int k = 0; k < s.size(); k++){
      if(s[k] == num){
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Funcion que escirbe un vector
   * 
   * @param s vector
   */
  void write(std::vector<int> s){
    for(int i = 0; i < s.size(); i++){
      std::cout << s[i] << " ";
    }
    std::cout << "\n";
  }
};