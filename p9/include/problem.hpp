#pragma once
#include <iostream>
#include <vector>
class Problem {
  private:
    int n_;
    int k_;
    std::vector<float> v_;
  
  public:
    Problem(char file[]);
    Problem(){}
    void read(char file[]);
    int pos(int i, int j);
    float get_item(int i, int j);
    void set_item(float r, int i, int j);
    int get_elements(void);
    int get_dimension(void);
    void write(void);
    std::vector<float> center(std::vector<int> s);
    float get_distance(int first, int second);


};