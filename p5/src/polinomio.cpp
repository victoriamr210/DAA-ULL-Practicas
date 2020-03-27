#include "../include/polinomio.hpp"

polinomio::polinomio(){}

polinomio::polinomio(int coef[], const int tam){

}

polinomio::polinomio(std::vector<monomio> &v){
  p = v;
  terminos = p.size();
  grado = p.back().get_exp();
  // write();
}

int polinomio::get_size(void){
  return p.size();
}

int polinomio::get_grado(void){
  return grado;
}

monomio polinomio::get_element(int i){
  return p[i];
}

void polinomio::set_element(monomio m, int i){
  p[i]=m;
}

void polinomio::write(void){
  for(int i=0; i<get_size(); i++){
    if(get_element(i).get_coef() != 0){
    std::cout << get_element(i) << " ";
    }
  }
}

std::ostream &operator<<(std::ostream &sout, polinomio &p){
  for(int i=0; i<p.get_size(); i++){
    if(p.get_element(i).get_coef() != 0){
    sout << p.get_element(i) << " ";
    }
  }
  sout << "\n";
}


polinomio operator+(polinomio &p, polinomio &q){
  int size;
  // std::cout << "\nsuma:\n";
  // std::cout << "p:" << p;
  // std::cout << "q:" << q;
  if(p.get_size() <= q.get_size()){
    size = q.get_size();
  } else {
    size = p.get_size();
  }
  std::vector<monomio> v;
  bool flag = false;
  int last_element=0;

  for(int i=0; i<p.get_size(); i++){
    for(int j=0; j<q.get_size(); j++){
      if (p.get_element(i).get_exp() == q.get_element(j).get_exp()) {
        v.push_back(p.get_element(i) + q.get_element(j));
        flag = true;
        last_element = j+1;
        break;
      }
    }
    if(!flag){
      v.push_back(p.get_element(i));
    }
    flag = false;
  }
  if(last_element < q.get_size()){
    for(int i=last_element; i<q.get_size(); i++){
      v.push_back(q.get_element(i));
    }
  }
  polinomio aux(v);
  return aux;
}


polinomio operator-(polinomio &p, polinomio &q){
  // std::cout << "\nresta\n";
  int size;

  // std::cout << "p:" << p;
  // std::cout << "q:" << q;
  if(p.get_size() <= q.get_size()){
    size = q.get_size();
  } else {
    size = p.get_size();
  }
  std::vector<monomio> v;
  for(int i = 0; i<size; i++){
    if(p.get_element(i).get_exp() == q.get_element(i).get_exp()){
      // std::cout << "for: " << p.get_element(i) << " " << q.get_element(i) << "\n";
      v.push_back(p.get_element(i) - q.get_element(i));
      // std::cout << "resultado: " << v.back() << "\n"; 
    } else {
      if(p.get_element(i).get_exp() < q.get_element(i).get_exp()){
        // std::cout << "if: " << p.get_element(i) << " " << q.get_element(i) << "\n";
        // v.push_back(p.get_element(i));
        v.push_back(q.get_element(i));
      } else {
        // std::cout << "else: " << q.get_element(i) << " " << p.get_element(i) << "\n";
        v.push_back(q.get_element(i));
        // v.push_back(p.get_element(i));
      }
    }
  }
  // std::cout << "vector: ";
  // for(int i=0; i<v.size(); i++){
  //   std::cout << v[i] << " ";
  // }
  // std::cout << "\n";

  polinomio aux(v);
  return aux;
}


polinomio operator*(polinomio &p, int cte){
  // std::cout << "\ncte: " << cte << "\n";
  monomio aux;
  for(int i = 0; i<p.get_size(); i++){
    // std::cout << p.get_element(i);
    int e = p.get_element(i).get_exp();
    // std::cout << "\ne: " << e << "\n";

    int exp = p.get_element(i).get_exp() + cte;
    // p.get_element(i).set_exp(exp);
    // std::cout << "exp: " << exp << "\n";
    aux.set_coef(p.get_element(i).get_coef());
    aux.set_exp(exp);  
    p.set_element(aux, i);
  }
  return p;
}