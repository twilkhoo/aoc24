#include <bits/stdc++.h>

using namespace std;


bool findRest(const vector<vector<char>> grid, int startRow, int startCol, size_t maxRow, size_t maxCol, int rowDir, int colDir, string remaining) {
  cout << "Calling findRest with row=" << startRow << ", col=" << startCol << "\n";
  
  if (remaining.empty()) return true;

  if (startRow < 0 || startRow > maxRow || startCol < 0 || startCol > maxCol) return false;

  // See if we don't have a match for the current char.
  if (*remaining.rbegin() != grid[startRow][startCol]) return false;

  // Otherwise, this char matched, and go in the direction.
  remaining.pop_back();
  return findRest(grid, startRow + rowDir, startCol + colDir, maxRow, maxCol, rowDir, colDir, remaining);

}


int main() {

  // Consume the input as a vector<vector<char>>.

  vector<vector<char>> grid;

  string line;
  while (getline(cin, line)) {
    vector<char> lineVec(line.begin(), line.end());
    grid.emplace_back(lineVec);
  }

  const size_t maxRow = grid.size() - 1;
  const size_t maxCol = grid[0].size() - 1;

  const vector<pair<int, int>> directions {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

  long ans = 0;

  for (size_t row = 0; row <= maxRow; row++) {
    for (size_t col = 0; col <= maxCol; col++) {

      // Check if we have a match in any direction here.
      for (auto [rowDir, colDir] : directions) {
        ans += findRest(grid, row, col, maxRow, maxCol, rowDir, colDir, "SAMX"); // Input the match string backwards to conveniently pop off.
      }


    }
  }

  cout << ans << "\n";

}



/*

Notes:

We must first scan the grid for an X. When we see an X, then check every direction (8 directions) to see if we have MAS.



*/
