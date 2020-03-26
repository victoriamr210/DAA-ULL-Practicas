#include <iostream>
#include "../include/table.hpp"

int main() {
  std::string a= "hola";
  std::string b= "la";
  table t(a, b);
  t.write();
}