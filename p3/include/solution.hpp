#pragma once
#include <vector>
#include <utility>
#include <iostream>

class solution{

  public:
    solution(){}
    virtual ~solution();

    virtual void solve_s(void);
    virtual void combine(std::pair<solution*,solution*> subsolutions);
    virtual solution* getInstance(void);
};