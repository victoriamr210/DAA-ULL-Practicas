#include "../include/calendarPT.hpp"

calendarPT::calendarPT(int n, int m) {
  row_ = n;
  col_ = m;
  board_ = new int*[row_];
  for(int i=0; i<row_; i++){
    board_[i] = new int[col_];
    for(int j=0; j<col_; j++){
      board_[i][j] = 0;
    }
  }
}

void calendarPT::makeCalendar(void){
  buildCalendar(0, col_);
}


void calendarPT::buildCalendar(int inf, int sup){
  int half;
  if(inf == (sup-1)){
    board_[inf][0] = sup+1; 
    board_[sup][0] = inf+1;
  } else {
    half = (inf+sup)/2;
    buildCalendar(inf, half);
    buildCalendar(half+1, sup);
    fillBoard(inf, half, half-inf, sup-inf-1, half+1);
    fillBoard(half+1, sup, half-inf, sup-inf-1, inf);
  }
}

void calendarPT::fillBoard(int inf, int sup, int infd, int supd, int ini){
  for(int j=infd; j<=supd; j++){
    board_[inf][j]=ini+j-infd+1;
  }

  for(int i=inf+1; i<=sup; i++){
    board_[i][infd]=board_[i-1][supd];
    for(int j=infd+1; j<=supd; j++){
      board_[i][j]=board_[i-1][j-1];
    }
  }
}


void calendarPT::write(void){
  std::cout << "   ";
  for(int i=0; i<col_; i++){
    std::cout << i << " ";
  }
  std::cout <<"\n";
  for(int i=0; i<row_; i++){
    std::cout << i << "  ";
    for(int j=0; j<col_; j++){
      std::cout << board_[i][j] << " ";
    }
    std::cout << "\n";
  }
}
