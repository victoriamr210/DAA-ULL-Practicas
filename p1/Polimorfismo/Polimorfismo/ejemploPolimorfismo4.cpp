// Ejemplo obtenido en http://c.conclase.net

#include <iostream>
#include <cstring>
using namespace std;
 
class Persona {
  public:
   Persona(const char *n) { strcpy(nombre, n); }
   virtual void VerNombre() { 
      cout << "Persona: " << nombre << endl; 
   }
  protected:
   char nombre[30];
};

class Empleado : public Persona {
  public:
   Empleado(const char *n) : Persona(n) {}
   void VerNombre() { 
      cout << "Empleado: " << nombre << endl; 
   }
};

class Estudiante : public Persona {
  public:
   Estudiante(const char *n) : Persona(n) {}
   void VerNombre() { 
      cout << "Estudiante: " << nombre << endl; 
   }
};

int main() {
   Estudiante Pepito("Jose");
   Empleado Carlos("Carlos");
   Persona &rPepito = Pepito; // Referencia como Persona
   Persona &rCarlos = Carlos; // Referencia como Persona

   rCarlos.VerNombre();
   rPepito.VerNombre();
    
   return 0;
}
