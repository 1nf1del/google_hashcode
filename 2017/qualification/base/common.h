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
#include <set>
#include <map>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define X first
#define Y second
#define PT pair<int, int>
#define mk make_pair
#define ll long long

using namespace std;

string class_name_;
bool enable_logging = true;

struct Endpoint {
  int L, K;
  vector<PT> connections;
};

struct Request {
  int V, E, N;
};

struct Input {
  int V, E, R, C, X;
  vector<int> videos;
  vector<Endpoint> endpoints;
  vector<Request> requests;
  unordered_map<int, vector<Request>> requests_by_video;
};

struct Output {
  vector<vector<int>> servers;
};

inline Input read_input(const std::string& fname) {
  ifstream in_f(fname);
  Input in;
  in_f >> in.V >> in.E >> in.R >> in.C >> in.X;
  for (int i = 0; i < in.V; ++i) {
    int x;
    in_f >> x;
    in.videos.push_back(x);
  }
  LOG("read videos count: " << in.videos.size())
  for (int i = 0; i < in.E; ++i) {
    Endpoint endp;
    in_f >> endp.L >> endp.K;
    for (int j = 0; j < endp.K; ++j) {
      int c, L;
      in_f >> c >> L;
      endp.connections.emplace_back(L, c);
    }
    sort(endp.connections.begin(), endp.connections.end());
    for (auto& qwe : endp.connections) {
      swap(qwe.X, qwe.Y);
    }
    in.endpoints.push_back(move(endp));
  }
  LOG("read endpoints count: " << in.endpoints.size())
  for (int i = 0; i < in.R; ++i) {
    Request req;
    in_f >> req.V >> req.E >> req.N;
    in.requests.push_back(req);
    in.requests_by_video[req.V].push_back(req);
  }
  LOG("read requests count: " << in.requests.size())
  return in;
}

inline Output read_output(const std::string& fname) {
  ifstream in_f(fname);
  int n = 0;
  in_f >> n;
  Output result;
  result.servers.resize(n);
  string s;
  getline(in_f, s);
  for (auto& server : result.servers) {
    getline(in_f, s);
    std::stringstream str(s);
    while (!str.eof()) {
      int x;
      str >> x;
      server.push_back(x);
    }
    LOG("server size: " << server.size());
  }
  return result;
}

inline void print_output(const Output& output, size_t score, const std::string& fpath = "./") {
  auto fname = fpath + to_string(score) + ".ans";
  fstream out_f(fname, fstream::out);

  out_f << output.servers.size() << '\n';
  for (const auto& server : output.servers) {
    for (auto qwe : server) {
      out_f << qwe << ' ';
    }
    out_f << '\n';
  }

  LOG("output has been printed to file: " << fname)
}
