#pragma once
#include <iostream>
#include <string>
#include <sstream>


class instruction{

  public:
    std::string instruc_;
    std::string op_;
    char symbol;
    bool jump=false;
    int number;
    int dir;

  public:

    instruction(std::string i);
    instruction(){}

    void set(std::string i);

    bool is_halt(void);
    void set_op(void);
    void reset(void);
    void print(void);
};