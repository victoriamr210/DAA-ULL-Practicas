#include <iostream>
#include "../include/calendarPT.hpp"

int main(int argc, char *argv[]) {
  if(argc == 3){
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);

    calendarPT c(row, col);
    c.makeCalendar();
    c.write();
  }
}