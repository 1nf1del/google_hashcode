#include "solution.h"
#include "../../base/statistics.h"
#include "../../improver/improver.h"

int main() {
  auto input = read_input("../../input/<<test_name>>.in");
  <<TestName>>Solution solution(input);
  solution.solve();

  auto score = calculate_score(solution.input(), solution.output());
  LOG("<<test_name>> score: " << score)
  print_output(solution.output(), score, "../../output/<<test_name>>/");

  auto improving_result = Improver::improve(solution.input(), solution.output());
  while (improving_result.Y) {
    improving_result = Improver::improve(solution.input(), move(improving_result.X));
  }
  auto improved_score = calculate_score(solution.input(), improving_result.X);
  print_output(improving_result.X, improved_score, "../../output/<<test_name>>/");
  LOG("<<test_name>> improved score: " << improved_score)
}
