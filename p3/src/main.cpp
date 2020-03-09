#include <iostream>
#include <stdlib.h>
#include "../include/mergesortP.hpp"
#include "../include/mergesortS.hpp"
#include "../include/framework.hpp"

void fill(std::vector<int> &v, int size){
	srand(37);
	for(int i=0; i<size; i++){
		// std::cout << rand() % 100 << " ";
		v.push_back(rand() % 100);
	}
}



int main(int argc, char *argv[]) {

	std::vector<int> v;
	fill(v,10);

	for(int i=0; i< v.size(); i++){
		std::cout << v[i] << " ";
	}
	std::cout << "\n";


	problem* p = new mergesortP(v);
	solution* s = new mergesortS();
	framework* f = new framework();

	f->divideyVenceras(p,s);
	std::cout << "\nResultado\n";
	s->solve_s();

}