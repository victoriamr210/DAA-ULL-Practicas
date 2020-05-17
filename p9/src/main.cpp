#include <iostream>
#include "../include/problem.hpp"
#include "../include/solution.hpp"
#include "../include/voraz.hpp"
#include "../include/newVoraz.hpp"
#include "../include/strategy.hpp"
#include "../include/localSearch.hpp"
#include "../include/GRASP.hpp"
#include "../include/RyP.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
      std::cout << "Un parametro, nombre de fichero\n";
    } else {
      Problem p(argv[1]);
      // p.write();
      int m = 3;
      std::cout << "-------Voraz------\n";
      resolve *v = new resolve(new voraz(m));
      Solution voraz = v->get_solution(p);
      std::cout << "\n-------New Voraz------\n";
      v->set_a(new newVoraz(m));
      Solution nv = v->get_solution(p);
      std::cout << "\n-------Busqueda Local (inicial voraz) ------\n";
      v->set_a(new localSearch(m, voraz));
      Solution lsv = v->get_solution(p);
      std::cout << "\n-------Busqueda Local (inicial nuevo voraz) ------\n";
      v->set_a(new localSearch(m, nv));
      Solution lsnv = v->get_solution(p);
      std::cout << "\n-------GRASP------\n";
      v->set_a(new GRASP(m));
      Solution grasp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior voraz / cota superior pequeña)------\n";
      v->set_a(new RyP(m, voraz, true));
      Solution ryp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior nuevo voraz / cota superior pequeña)------\n";
      v->set_a(new RyP(m, nv, true));
      ryp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior GRASP / cota superior pequeña)------\n";
      v->set_a(new RyP(m, grasp, true));
      ryp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior voraz / nodo mas profundo)------\n";
      v->set_a(new RyP(m, voraz, false));
      ryp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior nuevo voraz / nodo mas profundo)------\n";
      v->set_a(new RyP(m, nv, false));
      ryp = v->get_solution(p);
      std::cout << "\n-------Ramificacion y poda (inferior GRASP / nodo mas profundo)------\n";
      v->set_a(new RyP(m, grasp, false));
      ryp = v->get_solution(p);
    }

}