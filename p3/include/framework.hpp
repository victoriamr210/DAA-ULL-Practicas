
#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include "problem.hpp"
#include "solution.hpp"

class framework{
  public:
    framework() {}
    virtual ~framework();
    void divideyVenceras(problem *p, solution *s);
};
