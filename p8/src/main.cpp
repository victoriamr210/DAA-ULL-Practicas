#include <iostream>
#include "../include/graph.hpp"
#include "../include/strategy.hpp"
#include "../include/voraz.hpp"
#include "../include/solution.hpp"

int main(int argc, char* argv[]) {

  if(argc != 2) {
    std::cout << "Nombre de fichero\n";
  } else {
    graph g(argv[1]);
    g.write();

    resolve *v = new resolve(new voraz());
    v->get_solution(g);
    // g.write_sol();

  }
}