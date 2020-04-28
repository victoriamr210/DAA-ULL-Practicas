#include <iostream>
#include "../include/graph.hpp"
#include "../include/strategy.hpp"
#include "../include/voraz.hpp"
#include "../include/newVoraz.hpp"
#include "../include/solution.hpp"
#include "../include/grasp.hpp"
#include "../include/multiarranque.hpp"
#include "../include/vns.hpp"

int main(int argc, char* argv[]) {

  if(argc != 3) {
    std::cout << "./main Nombre-fichero 1/0 (1=greedy, 0=ansioso)\n";
  } else {
    graph g(argv[1]);
    bool greedy = atoi(argv[2]); 
    // g.write();
    // for(int i = 0; i < 5; i++){
    if (greedy) {
      std::cout << "Greedy\n\n";
    } else {
      std::cout << "Ansiosa\n\n";
    }
    std::cout << "-------Voraz------\n";
    resolve *v = new resolve(new voraz(), greedy);
    v->get_solution(g);
    std::cout << "\n-------Nuevo Voraz------\n";
    v->set_a(new new_voraz());
    v->get_solution(g);
    std::cout << "\n-------GRASP------\n";
    v->set_a(new GRASP());
    v->get_solution(g);
    std::cout << "\n-------Multiarranque------\n";
    v->set_a(new multiarranque());
    v->get_solution(g);
    std::cout << "\n-------VNS------\n";
    v->set_a(new VNS());
    v->get_solution(g);
    // }
  }
}