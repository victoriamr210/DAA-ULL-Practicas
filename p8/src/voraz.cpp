#include <iostream>
#include "../include/voraz.hpp"
#include <vector>
#include <set>


void voraz::solve(graph& g) {
  std::set<int> s;
  s.insert(g.maximum().first);
  s.insert(g.maximum().second);

}