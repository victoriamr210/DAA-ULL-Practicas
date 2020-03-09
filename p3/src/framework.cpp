
#include "../include/framework.hpp"

framework::~framework() {}

void framework::divideyVenceras(problem* p, solution* s){
	if (p->isMin()){
		p->solve(s);
	}
	else{
		std::pair<problem*,problem*> subProblems;
		std::pair<solution*,solution*> subSolutions;
		subProblems = p->decompose();
		subSolutions.first = s->getInstance();
		subSolutions.second = s->getInstance();
		divideyVenceras(subProblems.first, subSolutions.first);  //.1
		divideyVenceras(subProblems.second, subSolutions.second);  //.2
		s->combine(subSolutions);
		// std::cout << "Hola\n";
	}
}

