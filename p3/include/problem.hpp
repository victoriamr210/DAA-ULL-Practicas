#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include "solution.hpp"


class problem{

  public:
    problem(){}
    virtual ~problem();
    virtual bool isMin(void);
    virtual std::pair<problem*, problem*> decompose(void);
    virtual void solve(solution* s);

};