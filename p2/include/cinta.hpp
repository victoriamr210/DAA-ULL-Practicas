#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class tape{

  protected:
    std::vector<int> t_;
    int head_=0;
    char* file_;
  
  public:
    tape(){}
    ~tape(){}
    std::vector<int> get_tape(void);
    int get_head(void);

};

class input_tape : public tape{

  public:
    input_tape(char* f);
    int read(void);
    void readFile(void);
    void print(void);

};

class output_tape : public tape{

  public:
    output_tape(char* f);
    void write(int a);
    void write_file(void);
    void print(void);
};