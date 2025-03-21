#include <bits/stdc++.h>
using namespace std;


// This function evaluates the result of an integer, after blinking.
// It may return either 1 or 2 numbers.
vector<size_t> evaluate(size_t num) {

  // Case 1.
  if (num == 0) return {1};


  // Case 2.
  string numStr = to_string(num);
  if (numStr.size() % 2 == 0) {
    string firstHalf = numStr.substr(0, numStr.size() / 2);
    string secondHalf = numStr.substr(numStr.size() / 2, numStr.size() / 2);

    return {stoul(firstHalf), stoul(secondHalf)};
  }

  // Case 3.
  return {num * 2024};
}


int main() {

  // Read the input.
  string numStr;
  vector<size_t> nums;
  while (getline(cin, numStr, ' ')) {
    nums.push_back(stoul(numStr));
  }

  // cout << nums.size() << endl;


  size_t n = 75;

  for (int i = 0 ; i < n ; i++) {
    cout << "starting blink " << i << endl;

    vector<size_t> newNums;

    for (size_t num : nums) {
      vector<size_t> res = evaluate(num);
      for (size_t resNum : res) {
        newNums.push_back(resNum);
      }
    }

    nums = newNums;
  }

  // for (auto num : nums) {
  //   cout << num << endl;
  // }

  cout << nums.size() << endl;
}






/*
Notes:

Proceed with a simulation.

Have an array of size_t.

On every blink (iteration), we'll make a new array and transform each previous element into the new element, inserting left to right.



*/
