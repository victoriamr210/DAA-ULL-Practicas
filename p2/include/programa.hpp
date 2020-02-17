#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "cinta.hpp"
#include "memoria.hpp"

class program{

  private:
    std::vector<std::string> ins_;
    std::vector<std::pair<std::string,int>> label_;
    int pc_;
    
  public:
    program(char* file);
    program(){}
    ~program(){}

    void build(char* file);
    void print_ins(void);
    void print_label(void);
    std::string get_i(int pos);
    int get_next_jump(std::string aux);

};