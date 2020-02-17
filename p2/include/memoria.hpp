#pragma once
#include <iostream>
#include<vector>

class memory{

  private:
    std::vector<int> m_;
  
  public:
    memory(void);

    void store(int pos, int val);
    int load(int pos);

    void print(void);
    int get_acc(void);

};