#include <iostream>
#include "../include/table.hpp"

int main(int argc, char* argv[]) {
  if(argc == 3){
    
    // std::string a= "juanes";
    // std::string b= "ane";

    std::string a(argv[1]);
    std::string b(argv[2]);
    table t(a, b);
    // t.fill_table();
    t.write();
    std::string solucion = t.solution();
    if(solucion.empty()){
      std::cout << "No hay subcadena común\n";
    } else {
      std::cout << "\nLa Subsecuencia Común mas Larga es: " << solucion << 
        " con longitud: " << solucion.size() << "\n";
    }
  } else {
    std::cout << "Numero de parámetros incorrecto\n";
  }
}