#pragma once

class ExampleSplitAndMerge {
public:
  static vector<Input> split_input(const Input& input) {
    const string class_name_ = "ExampleSpliteAndMerge";
    vector<Input> result{input};
    /* split input here */
    LOG("finished splitting into " << result.size() << " inputs")
    return result;
  }

  static Output merge_output(const Input& input, const vector<Output>& splitted_output) {
    const string class_name_ = "ExampleSpliteAndMerge";
    Output result = splitted_output.front();
    /* merge output here */
    LOG("finished merging " << splitted_output.size() << " outputs")
    return result;
  }
};