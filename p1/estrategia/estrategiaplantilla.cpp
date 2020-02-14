#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class SortBubble {
public:
   void sort( int v[], int n ) {
	cout << "SortBubble" << endl;
   }
};

class SortShell {
public:
   void sort( int v[], int n ) {
	cout << "SortShell" << endl;
   }
};

template<class STRATEGY>
class Stat {
public:
   void readVector( int v[], int n ) {
      imp_.sort( v, n );
      min_ = v[0];   max_ = v[n-1];
      med_ = v[n/2]; 
   }
   int getMin() { return min_; }
   int getMax() { return max_; }
   int getMed() { return med_; }
private:
   int       min_, max_, med_;
   STRATEGY  imp_;
};

int main( void ) {
   const int NUM = 9;
   int       array[NUM];
   time_t    t;
   srand((unsigned) time(&t));
   cout << "Vector: ";
   for (int i=0; i < NUM; i++) {
      array[i] = rand() % 9 + 1;
      cout << array[i] << ' '; 
   }
   cout << endl;

   Stat<SortBubble>  obj;
   obj.readVector( array, NUM );
   cout << "min is " << obj.getMin()
      << ", max is " << obj.getMax()
   << ", median is " << obj.getMed()
      << endl;

   Stat<SortShell>  two;
   two.readVector( array, NUM );
   cout << "min is " << two.getMin()
      << ", max is " << two.getMax()
      << ", median is " << two.getMed()
      << endl;
};




