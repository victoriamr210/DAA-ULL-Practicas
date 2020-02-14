// Strategy pattern -- Structural example

#include <iostream>
using namespace std;

enum TYPESTRATEGY{A, B, C, D};

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
 

// A new 'ConcreteStrategy' class
class ConcreteStrategyD : public Strategy  {
    void AlgorithmInterface() {
     cout <<  "Called ConcreteStrategyD.AlgorithmInterface()" << endl;
    }
};

// The 'Context' class
class Context {
    protected:
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
	    else { 
		cout << "ERROR: Stratey not known" << endl; 
		_strategy = NULL;
	    }
         }

         void setstrategy(Strategy *strategy ) {
	    delete _strategy;
	    _strategy = strategy;
         }
         void ContextInterface() {
	    if (_strategy)
            	_strategy -> AlgorithmInterface();
	    else
		cout << "ERROR: Strategy not set" << endl;
         }

};

// The 'Context' class
class Newcontext: public Context {
	public:
         void setstrategy(TYPESTRATEGY type ) {
	    delete _strategy;
	    if (type == D)
            	_strategy = new ConcreteStrategyD();
	    else 
		Context::setstrategy(type);
         }
};

int main() {
      Context *pcontext;
      Context context;
      Newcontext newcontext;

      pcontext = new Context(new ConcreteStrategyA());
      context.setstrategy(A);
      newcontext.setstrategy(A);

      pcontext->ContextInterface();
      context.ContextInterface();
      newcontext.ContextInterface();

      pcontext -> setstrategy(new ConcreteStrategyD());
      pcontext->ContextInterface();

      context.setstrategy(D); 
      context.ContextInterface();

      newcontext.setstrategy(D); 
      newcontext.ContextInterface();

}

 
