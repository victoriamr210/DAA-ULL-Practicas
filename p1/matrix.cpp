#include <iostream>



int main (void){

  int a[3][2] = {{2,3}, {3,8},{6,2}};
  int b[2][2] = {{5,8}, {7,2}};
  int c[3][2];
  for(int i=0; i<3; i++){
    for(int j=0; j<2; j++){
      c[i][j] =0;
    }
  }

  int val;
  for(int i=0; i<3; i++){
    for(int j=0; j<2; j++){
      for(int k=0; k<2; k++){
        c[i][j]+=a[i][k] * b[k][j];
      }
    }
  }

  for(int i=0; i<3; i++){
    for(int j=0; j<2; j++){
      std::cout << c[i][j] << " ";
    }
    std::cout << "\n";
  }

  
}