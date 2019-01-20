#pragma once

#include "../../base/async_solution.h"

class MeAtZooSolution : public AsyncSolution {
public:
  template <typename... T>
  MeAtZooSolution(T&&... args):
      AsyncSolution(std::forward<T>(args)...) {
    clog = ofstream("logs/" + to_string(number()) + ".log");
  }

  void solve_internal() override {
    LOG("started")
    /* solve problem here */
    LOG("finished")
  }

private:
  const string class_name_ = "MeAtZooSolution";
  ofstream clog;
};
