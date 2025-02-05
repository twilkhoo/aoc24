#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;



// Operator to print a pair<ull, vector<ull>>
std::ostream& operator<<(std::ostream& os, const std::pair<ull, std::vector<ull>>& p) {
    os << "{" << p.first << ", {";
    for (size_t i = 0; i < p.second.size(); ++i) {
        os << p.second[i];
        if (i + 1 < p.second.size()) {
            os << ", ";
        }
    }
    os << "}}";
    return os;
}

// Operator to print a vector<pair<ull, vector<ull>>>
std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<ull, std::vector<ull>>>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i]; 
        if (i + 1 < v.size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}


enum class Operator {
  ADD,
  MULT,
  CONCAT
};


// A recursive backtracking implementation to see if we can achieve the target using the numbers in nums, with only * and +.
bool isPossible(ull target, vector<ull> nums, size_t curIdx, ull curVal, Operator type) {


  if (curIdx == nums.size()) return target == curVal;

  // Assign the newVal.
  ull newVal;

  switch (type) {

    case (Operator::ADD) : {
      newVal = curVal + nums[curIdx];
      break;
    }

    case (Operator::MULT) : {
      newVal = curVal * nums[curIdx];
      break;
    }

    default : { // Operator::CONCAT
      string curValStr  = to_string(curVal);
      string nextNumStr = to_string(nums[curIdx]);
      curValStr += nextNumStr;

      newVal = stoull(curValStr); 
      break;
    }
  }


  return isPossible(target, nums, curIdx + 1, newVal, Operator::ADD) 
  | isPossible(target, nums, curIdx + 1, newVal, Operator::MULT)
  | isPossible(target, nums, curIdx + 1, newVal, Operator::CONCAT);
}






int main() {

  // Consume the input as a vector<pair<ull, vector<ull>>>, where the first num in the pair is the target, the next vector is the list of chars.
  vector<pair<ull, vector<ull>>> inputs;

  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string token;

    pair<ull, vector<ull>> curLineData{0, vector<ull>()};
    bool firstNum = true;
    while (getline(ss, token, ' ')) {

      // Adjust for the first character.
      if (firstNum) {
        token.pop_back(); // Get rid of the ':'
        curLineData.first = stoull(token);
        firstNum = false;
        continue;
      }

      // For every other character, just push back.
      curLineData.second.push_back(stoull(token));
    }

    inputs.emplace_back(curLineData);
  }











  // cout << inputs << endl;

  // Parse the inputs.
  size_t ans = 0;
  for (const auto& input : inputs) {
    if (isPossible(input.first, input.second, 0, 0, Operator::ADD)) ans += input.first;
  }

  cout << ans << endl;

}


/*

Notes:

Backtracking- start with the leftmost number as the state.
On every iteration, either multiply or add, in that order.
Do this as recursive dfs.





*/

