#define MAX_SOLVING_THREAD_COUNT 18
#pragma once

#include "log.h"
#include <algorithm>
#include <atomic>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#define X first
#define Y second
#define PT pair<int, int>

using namespace std;

string class_name_;
bool enable_logging = true;

struct Input {
  int V, E, R, C, X;
  vector<int> videos;

};

struct Output {
  /* output structure here */
};

inline Input read_input(const std::string& fname) {
  ifstream in_f(fname);
  Input in;
  /* read input here */
  return in;
}

inline void print_output(const Output& output, size_t score, const std::string& fpath = "./") {
  auto fname = fpath + to_string(score) + ".ans";
  fstream out_f(fname, fstream::out);
  /* print output here */
  LOG("output has been printed to file: " << fname)
}
