#include "solution.h"
#include "../../base/calculate_score.h"

int main(int argc, char** argv) {
  DBG("debug mode")
  LOG("srand: " << atoi(argv[1]))
  srand(atoi(argv[1]));

  auto input = read_input("../../input/kittens.in");
  Solution solution(input);
  solution.solve();

  auto score = calculate_score(solution.input(), solution.output());
  LOG("final score: " << score)
  print_output(solution.output(), score, "../../output/kittens/");
}
