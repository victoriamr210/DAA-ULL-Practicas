// Strategy pattern -- Structural example

#include <iostream>
using namespace std;

enum TYPESTRATEGY{A, B, C};

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
         Context() {
            _strategy = NULL;
         }
         // Constructor
         Context(Strategy *strategy) {
            _strategy = strategy;
         }
 
         void setstrategy(TYPESTRATEGY type ) {
	    delete _strategy;
	    if (type == A)
            	_strategy = new ConcreteStrategyA();
	    else if (type == B)
            	_strategy = new ConcreteStrategyB();
	    else if (type == C)
            	_strategy = new ConcreteStrategyC();
	    else 
		cout << "ERROR: Stratey not known" << endl; 
         }

         void setstrategy(Strategy *strategy ) {
	    delete _strategy;
	    _strategy = strategy;
         }
         void ContextInterface() {
            _strategy -> AlgorithmInterface();
         }

};

int main() {
      Context *pcontext;
      Context context;

      pcontext = new Context(new ConcreteStrategyA());
      context.setstrategy(A);

      pcontext->ContextInterface();
      context.ContextInterface();

      pcontext -> setstrategy(new ConcreteStrategyB());
      context.setstrategy(B); 

      pcontext->ContextInterface();
      context.ContextInterface();

}

 
