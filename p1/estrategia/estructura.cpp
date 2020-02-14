// Strategy pattern -- Structural example

#include <iostream>
using namespace std;



// The 'Strategy' abstract class
class Strategy {
    public: 
	virtual void AlgorithmInterface() = 0;
 };


// A 'ConcreteStrategy' class
class ConcreteStrategyA : public Strategy  {
    void AlgorithmInterface() {
     cout <<  "Called ConcreteStrategyA.AlgorithmInterface()" << endl;
    }
};

 
// A 'ConcreteStrategy' class
class ConcreteStrategyB : public Strategy  {
    void AlgorithmInterface() {
     cout <<  "Called ConcreteStrategyB.AlgorithmInterface()" << endl;
    }
};

// A 'ConcreteStrategy' class
class ConcreteStrategyC : public Strategy  {
    void AlgorithmInterface() {
     cout <<  "Called ConcreteStrategyC.AlgorithmInterface()" << endl;
    }
};
 


// The 'Context' class
class Context {
    private:
	 Strategy *_strategy;
    public:
         // Constructor
         Context(Strategy *strategy) {
            _strategy = strategy;
         }
 
         void ContextInterface() {
            _strategy -> AlgorithmInterface();
         }

};

int main() {
      Context *context_a, *context_b, *context_c;

      // Three contexts following different strategies

      context_a = new Context(new ConcreteStrategyA());
      context_a->ContextInterface();

      context_b = new Context(new ConcreteStrategyB());
      context_b->ContextInterface();


      context_c = new Context(new ConcreteStrategyC());
      context_c->ContextInterface();

}

 
