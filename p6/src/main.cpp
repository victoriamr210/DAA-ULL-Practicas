#include <iostream>
#include "../include/calendarPT.hpp"
#include "../include/calendar.hpp"
#include <cmath>

int main(int argc, char *argv[]){
  if(argc == 3){
    int teams = atoi(argv[1]);
    int days = atoi(argv[2]);

    bool powerTwo = false;
    int exp = 0;

    int i=0;
    while(pow(2,i) <= teams){
      if(teams == pow(2,i)){
        powerTwo = true;
        break;
      } else{
        exp=i;
        i++;
      }
    }
    
    if(powerTwo){
      calendarPT c(teams, days);
      c.makeCalendar();
      c.write();
    } else{
      int rows = pow(2,exp+1);
      calendar c(rows, rows-1, teams);
      c.makeCalendar();
      c.write();
    }
  }
}