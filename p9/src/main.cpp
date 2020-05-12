#include <iostream>
#include "../include/problem.hpp"
#include "../include/solution.hpp"
#include "../include/voraz.hpp"
#include "../include/newVoraz.hpp"
#include "../include/strategy.hpp"
#include "../include/localSearch.hpp"
#include "../include/GRASP.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
      std::cout << "Un parametro, nombre de fichero\n";
    } else {
      Problem p(argv[1]);
      // p.write();
      std::cout << "-------Voraz------\n";
      resolve *v = new resolve(new voraz());
      v->get_solution(p);
      std::cout << "\n-------New Voraz------\n";
      v->set_a(new newVoraz());
      v->get_solution(p);
      std::cout << "\n-------Busqueda Local------\n";
      v->set_a(new localSearch());
      v->get_solution(p);
      std::cout << "\n-------GRASP------\n";
      v->set_a(new GRASP());
      v->get_solution(p);
    }

}