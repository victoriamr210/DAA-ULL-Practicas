#include <iostream>
#include "../include/graph.hpp"
#include "../include/strategy.hpp"
#include "../include/voraz.hpp"
#include "../include/newVoraz.hpp"
#include "../include/solution.hpp"
#include "../include/grasp.hpp"
#include "../include/multiarranque.hpp"

int main(int argc, char* argv[]) {

  if(argc != 2) {
    std::cout << "Error de entrada\n";
  } else {
    graph g(argv[1]);
    // g.write();
    std::cout << "-------Voraz------\n";
    resolve *v = new resolve(new voraz());
    v->get_solution(g);
    // std::cout << "-------Nuevo Voraz------\n";
    // v->set_a(new new_voraz());
    // v->get_solution(g);
    // std::cout << "-------GRASP------\n";
    // v->set_a(new GRASP());
    // v->get_solution(g);
    // std::cout << "-------Multiarranque------\n";
    // v->set_a(new multiarranque());
    v->get_solution(g);
  }
}