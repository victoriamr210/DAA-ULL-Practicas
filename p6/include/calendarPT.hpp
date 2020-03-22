#include <iostream>
#include <vector>

class calendarPT{

  private:
    int **board_;
    int row_;
    int col_;

  public:
    calendarPT(int n, int m);
    void emptyBoard(void);
    void makeCalendar(void);
    void buildCalendar(int inf, int sup);
    void fillBoard(int inf, int sup, int infd, int supd, int ini);
    void write(void);
    
};