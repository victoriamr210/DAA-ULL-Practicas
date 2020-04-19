#include <iostream>
#include "../include/graph.hpp"

int main(int argc, char* argv[]) {

  if(argc != 2) {
    std::cout << "Nombre de fichero\n";
  } else {
    graph g(argv[1]);
    g.write();
  }
}