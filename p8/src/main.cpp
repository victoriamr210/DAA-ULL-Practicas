#include <iostream>
#include "../include/graph.hpp"
#include "../include/strategy.hpp"
#include "../include/voraz.hpp"
#include "../include/newVoraz.hpp"
#include "../include/solution.hpp"
#include "../include/grasp.hpp"

int main(int argc, char* argv[]) {

  if(argc != 2) {
    std::cout << "Error de entrada\n";
  } else {
    graph g(argv[1]);
    // g.write();

    resolve *v = new resolve(new new_voraz());
    // v->get_solution(g);
    // v = new resolve(new GRASP());
    v->get_solution(g);

    // g.write_sol();

  }
}