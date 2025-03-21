#include <bits/stdc++.h>
using namespace std;


int n = 75;

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


size_t recurse(size_t stone, unordered_map<size_t, vector<size_t>>& memo, size_t blinkCount) {

  cout << "determining number of stones made from " << stone << " after " << blinkCount << " blinks." << endl;

  // If we already know how many stones will be produced after blinking <blinkCount> times starting from stone, just return this number.
  if (memo.contains(stone) && memo[stone][blinkCount] != 0) return memo[stone][blinkCount];

  // Otherwise, we must solve this subproblem. First, let's create a vector (if not already created).
  if (!memo.contains(stone)) memo[stone] = vector<size_t>(n + 1);

  // Base case- we've blinked only once, just compute the number of stones made directly.
  if (blinkCount == 1) {
    vector<size_t> stonesMade = evaluate(stone);
    memo[stone][blinkCount] = stonesMade.size();
    return stonesMade.size();
  }

  // General case- we need to compute how many stones were made after blinking <blinkCount> times, so do this recursively.
  size_t sum = 0;
  // For each of the stones we create by blinking with the current one...
  for (size_t nextStone : evaluate(stone)) {
    // Compute how many stones each child stone creates, and add it to this sum.
    sum += recurse(nextStone, memo, blinkCount - 1);
  }

  memo[stone][blinkCount] = sum;
  return sum;


}






int main() {

  // Read the input.
  string numStr;
  vector<size_t> input;
  while (getline(cin, numStr, ' ')) {
    input.push_back(stoul(numStr));
  }


  unordered_map<size_t, vector<size_t>> memo;

  // Have a recursive dp function.
  unsigned long long sum = 0;
  for (size_t num : input) {
    sum += recurse(num, memo, n);
  }

  cout << sum << endl;

}






/*
Notes:

Proceed with a simulation.

Have an array of size_t.

On every blink (iteration), we'll make a new array and transform each previous element into the new element, inserting left to right.



Part 2:

Note that the only important part is to compute the number of stones after each blink.

So, let's keep a hash map of form hashmap{ num => vector<size_t> }, where the num is the first number, and the index into the vector is the number of blinks.

Our answer for a particular num would be in m[num][75].

So, we can build up this strategy using memoization (which is what the hashmap is for).



*/
