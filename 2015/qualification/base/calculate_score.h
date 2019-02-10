#pragma once

#include "common.h"

std::string print_coordinates(int r, int s, bool square = false) {
  return (square ? "[" : "(") + std::to_string(r) + ", " + std::to_string(s) + (square ? "]" : ")");
}

void validate(const Input& input, const Output& output, bool enable_logging) {
  assert(("Invalid output, expecting description of " + std::to_string(input.M) + " servers",
    output.servs.size() == input.M));
  for (size_t i = 0; i < output.servs.size(); ++i) {
    const auto& server = output.servs[i];
    if (!server.ok)
      continue;

    assert(("server " + std::to_string(i) + " has wrong coordinates: " + print_coordinates(server.ar, server.as) +
      ", it must be in " + print_coordinates(0, input.R, true) + " x " + print_coordinates(0, input.S),
      0 <= server.ar && server.ar < input.R && 0 <= server.as && server.as < input.S));

    assert(("server " + std::to_string(i) + " extends beyond the slots on the row ",
      server.as + input.servs[i].first > server.as));

    assert(("server " + std::to_string(i) + " has invalid pool number: " + std::to_string(server.ap),
      0 <= server.ap && server.ap < input.P));

    for (size_t j = 0; j < input.us.size(); ++j) {
      if (input.us[j].first == server.ar) {
        assert(("server " + std::to_string(i) + " occupies unavailable slot " + print_coordinates(input.us[j].first, input.us[j].second),
          server.as + input.servs[i].first <= input.us[j].second || server.as > input.us[j].second));
      }
    }
  }
}

int calculate_score(const Input& input, const Output& output, bool enable_logging = true) {
  validate(input, output, enable_logging);
  int score = -1;
  for (int un = 0; un < input.R; ++un) {
    vector<int> cap(input.P);
    for (size_t j = 0; j < output.servs.size(); ++j) {
      const auto& server = output.servs[j];
      if (!server.ok)
        continue;

      if (server.ar != un) {
        cap[server.ap] += input.servs[j].second;
      }
    }
    int current_score = *std::min_element(cap.begin(), cap.end());
    if (enable_logging) {
      LOG("Shutdown " + std::to_string(un) + " row, score = " << current_score);
    }
    if (score == -1 || score > current_score) {
      score = current_score;
    }
  }
  return std::max(0, score);
}
