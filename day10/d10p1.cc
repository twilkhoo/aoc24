#include <bits/stdc++.h>
using namespace std;




string pairToString(pair<size_t, size_t> p) {
  string res = to_string(p.first) + "," + to_string(p.second);
  return res;
}

pair<size_t, size_t> stringToPair(string s) {
  stringstream ss(s);

  string token;
  bool first = true;
  pair<size_t, size_t> res;
  while (getline(ss, token, ',')) {
    if (first) {
      res.first = stoul(token);
      first = false;
    } else {
      res.second = stoul(token);
    }
  }

  return res;
}


ostream& operator<<(ostream& out, pair<size_t, size_t> p) {
  out << "pair { " << p.first << " , " << p.second << " }";
  return out;
}


vector<pair<int, int>> steps {
  {-1, 0},
  {0, -1},
  {0, 1},
  {1, 0},
};


void dfs(vector<vector<size_t>>& grid, unordered_set<string>& ends, size_t curNum, size_t curRow, size_t curCol) {
  if (curNum == 9) {
    ends.insert(pairToString({curRow, curCol}));
    return;
  }


  for (auto [rowStep, colStep] : steps) {
    int nextRow = rowStep + curRow;
    int nextCol = colStep + curCol;
    size_t nextNum = curNum + 1;

    // Check bounds.
    if (nextRow < 0 || nextRow >= grid.size() || nextCol < 0 || nextCol >= grid[0].size()) continue;

    // Check num.
    if (grid[nextRow][nextCol] != nextNum) continue;

    dfs(grid, ends, nextNum, nextRow, nextCol);
  }

}






int main () {

  // First, read the input as a vector<vector<size_t>>.
  vector<vector<size_t>> grid;

  string lineStr;
  while (getline(cin, lineStr)) {
    vector<size_t> curLine;
    
    for (char c : lineStr) {
      curLine.push_back(c - '0');
    }

    grid.emplace_back(curLine);
  }

  // Print the grid just to be sure.
  for (auto line : grid) {
    for (auto num : line) {
      cout << num << " ";
    }
    cout << endl;
  }




  // Find the locations of all 0s, and add it to a hashmap.
  map<string, unordered_set<string>> zeros;

  for (size_t row = 0 ; row < grid.size(); row++) {
    for (size_t col = 0 ; col < grid[0].size(); col++) {
      if (grid[row][col] == 0) zeros[pairToString({row, col})];
    }
  }






  // Now, for every zero, we want to perform a dfs starting at that location.
  for (auto& [start, ends] : zeros) {
    auto [curRow, curCol] = stringToPair(start);
    dfs(grid, ends, 0, curRow, curCol);
  }



  // Print sizes of zeros.
  unsigned long long sum = 0;
  for (const auto& [start, ends] : zeros) {
    sum += ends.size();
    cout << "start location " << start << " has " << ends.size() << " ends." << endl;
  }

  cout << sum << endl;




}






/*

First, find every 0.

Then, for every 0, do dfs to find the next number (1, 2, ..., 9).
Every time we find a 9, record its position associated with this 0.

So, I want a hashmap { <location of a 0> => hashset{<locations of reachable 9s>} }

We'll represent each location as a string so that it's hashable.









*/







