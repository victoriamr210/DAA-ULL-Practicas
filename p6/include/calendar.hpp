#include <iostream>
#include <vector>

class calendar{

  private:
    int **board_;
    int row_;
    int col_;
    int teams_;

  public:
    calendar(int n, int m, int t);
    void emptyBoard(void);
    void makeCalendar(void);
    void buildCalendar(int inf, int sup);
    void fillBoard(int inf, int sup, int infd, int supd, int ini);
    void write(void);
    
};