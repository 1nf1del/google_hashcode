#pragma once

#include "common.h"

int calculate_score(const Input& input, const Output& output, bool enable_logging = true) {
  int score = 0;
  vector<vector<bool>> qwe(input.R, vector<bool>(input.C, false));
  for (int q = 0; q < output.sls.size(); ++q) {
    auto& sl = output.sls[q];
    int tcnt = 0;
    int mcnt = 0;
    int ax = sl.st.X, ay = sl.st.Y, bx = sl.fin.X, by = sl.fin.Y;
    if (ax > bx)
      swap(ax, bx);
    if (ay > by)
      swap(ay, by);
    for (int i = ax; i < bx + 1; ++i) {
      for (int j = ay; j < by + 1; ++j) {
        if (ax < 0 || ay < 0 || bx >= input.R || by >= input.C) {
          LOG("out of border: " << i << ' ' << j)
          LOG("slice number: " << q)
          LOG("slice corners: " << ax << ' ' << ay << ' ' << bx << ' ' << by)
          return 0;
        }
        if (qwe[i][j]) {
          LOG("already used cell: " << i << ' ' << j)
          LOG("slice number: " << q)
          LOG("slice corners: " << ax << ' ' << ay << ' ' << bx << ' ' << by)
          return 0;
        }
        qwe[i][j] = 1;
        if (input.pizza[i][j] == 'T')
          ++tcnt;
        else if (input.pizza[i][j] == 'M')
          ++mcnt;
      }
    }
    if (tcnt < input.L) {
      LOG("too small number of T: " << tcnt)
      LOG("slice number: " << q)
      LOG("slice corners: " << ax << ' ' << ay << ' ' << bx << ' ' << by)
      return 0;
    }
    if (mcnt < input.L) {
      LOG("too small number of M: " << mcnt)
      LOG("slice number: " << q)
      LOG("slice corners: " << ax << ' ' << ay << ' ' << bx << ' ' << by)
      return 0;
    }
    if (tcnt + mcnt > input.H) {
      LOG("exceeds the maximum number of cells in a slice: " << mcnt + tcnt)
      LOG("slice number: " << q)
      LOG("slice corners: " << ax << ' ' << ay << ' ' << bx << ' ' << by)
      return 0;
    }
  }
  for (const auto& row : qwe)
    for (const auto& cell : row)
      score += cell;
  return score;
}
