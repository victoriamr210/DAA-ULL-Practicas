// Ejemplo obtenido en http://c.conclase.net

#include <iostream>
using namespace std;

class ClaseA {
  public:
   void Incrementar() { cout << "Suma 1" << endl; }
   void Incrementar(int n) { cout << "Suma " << n << endl; }
};

class ClaseB : public ClaseA {
  public:
//   void Incrementar() { cout << "Suma 2" << endl; }
};

int main() {
   ClaseB objeto;

   objeto.Incrementar();
//   objeto.Incrementar(10);
   objeto.ClaseA::Incrementar();
   objeto.ClaseA::Incrementar(10);
   
   return 0;
}

