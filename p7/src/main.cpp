#include <iostream>
#include "../include/table.hpp"

int main(int argc, char* argv[]) {
  if(argc == 3){

    std::string a= "juanes";
    std::string b= "ane";
    table t(a, b);
    // t.fill_table();
    t.write();
    t.solution();
  } else {
    std::cout << "Numero de parámetros incorrecto\n";
  }
}