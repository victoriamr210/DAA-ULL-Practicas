#include "../include/calendarPT.hpp"

calendarPT::calendarPT(int n, int m) {
  row_ = n;
  col_ = m;
  board_ = new int*[row_+1];
  for(int i=1; i<=row_; i++){
    board_[i] = new int[col_+1];
    for(int j=1; j<=col_; j++){
      board_[i][j] = 0;
    }
  }
}

void calendarPT::makeCalendar(void){
  buildCalendar(1, row_);
}


void calendarPT::buildCalendar(int inf, int sup){
  int half;
  // sup=sup-1;
  if(inf == (sup-1)){
    board_[inf][1] = sup; 
    board_[sup][1] = inf;
  } else {
    half = (inf+sup)/2;
    buildCalendar(inf, half);
    buildCalendar(half+1, sup);
  std::cout << "BC(" << inf << " " << sup <<")\n";
    std::cout << "primera llamada\n";
    // fillBoard(inf, half, half, sup-1, half+1) ;
    fillBoard(inf, half, half-inf+1, sup-inf, half+1);
    // fillBoard(inf, half, sup-half, sup-inf, half+1);
    std::cout << "segunda llamada\n";
    // fillBoard(half+1, sup, half, sup-1, inf);
    fillBoard(half+1, sup, half-inf+1, sup-inf, inf);
  }
}

void calendarPT::fillBoard(int inf, int sup, int infd, int supd, int ini){
  std::cout << "inf:" << inf << " sup:" << sup << " infd:" << infd;
  std::cout << " supd:" << supd << " ini:" << ini << "\n";
  std::cout << "antes\n";
  write();
  std::cout << "\n";
  std::cout << "primer for\n";
  for(int j=infd; j<=supd; j++){
    board_[inf][j]=ini+j-infd;
    std::cout << "board:" << inf << " " << j;
    std::cout << " = " << ini+j-infd+1 << " ("<<ini<<"+"<<j<<"-"<<infd<<"+1)\n";
  }
  write();
  std::cout << "\n";
  std::cout << "segundo for\n";
  for(int i=inf+1; i<=sup; i++){
    std::cout << "board:" << i << " " << infd;
    std::cout << " = " << board_[i-1][supd] << " (board_[" << i
      <<"-1]["<<supd<<"])\n";
    board_[i][infd]=board_[i-1][supd];
    
    for(int j=infd+1; j<=supd; j++){
       std::cout << "board:" << i << " " << j;
    std::cout << " = " << board_[i-1][j-1] << " (board_["<<i<<"-1]["<<j<<"-1])\n";
      board_[i][j]=board_[i-1][j-1];

    }
  }

  write();
  std::cout << "\n";
}


void calendarPT::write(void){
  std::cout << "   ";
  for(int i=0; i<col_; i++){
    std::cout << i << " ";
  }
  std::cout <<"\n";
  for(int i=1; i<=row_; i++){
    std::cout << i << "  ";
    for(int j=1; j<=col_; j++){
      std::cout << board_[i][j] << " ";
    }
    std::cout << "\n";
  }
}
