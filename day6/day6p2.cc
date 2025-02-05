#include <bits/stdc++.h>
using namespace std;


enum class Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};


ostream& operator<<(ostream& os, vector<vector<char>> vec) {
  for (const auto& line : vec) {
    for (char c : line) {
      os << c;
    }
    os << "\n";
  }

  return os;
}

ostream& operator<<(ostream& os, vector<vector<Direction>> vec) {
  for (const auto& line : vec) {
    for (Direction c : line) {
      os << static_cast<int>(c);
    }
    os << "\n";
  }

  return os;
}


int main() {
  string line;
  
  // Row and col refer to where the guard currently is in our simulation.
  int startRow;
  int startCol;

  vector<vector<char>> gridOG;
  size_t curRow = 0;
  while (getline(cin, line)) {
    vector<char> lineVec;
    for (size_t i = 0 ; i < line.size() ; i ++) {
      if (line[i] == '^') {
        startRow = curRow;
        startCol = i;
        lineVec.push_back('.');
      }

      else {
        lineVec.push_back(line[i]);
      }
    }
    curRow++;
    gridOG.emplace_back(lineVec);
  }


  cout << "Guard is at row=" << startRow << ", col=" << startCol << "\n";
  cout << gridOG;

  // Make a copy of the grid for bookkeeping.








  // Now, we need functionality to detect a cycle.
  // To detect a cycle, see if we're currently on a node that we've previously visited (X).
  // Keep track of the previous direction. If the direction we were going last time we were here matches our current direction, that means we will be in a cycle!
  // Otherwise, keep going.
  // So, keep a direction grid too.

  vector<vector<unordered_set<Direction>>> gridDirsOG(gridOG.size(), vector<unordered_set<Direction>>(gridOG[0].size(), unordered_set<Direction>()));



  size_t cycleCount = 0;
  // A nested for loop to try putting an obstacle at every position.
  for (int i = 0; i < gridOG.size(); i++) {
    for (int j = 0; j < gridOG[0].size(); j++) {

      if (gridOG[i][j] == '#') continue; // Can't put an obstacle where an obstacle currently is.
      if (i == startRow && j == startCol) continue; // Can't put an obstacle where the guard currently is.


      // cout << "Trying to put obstacle at row=" << i <<", col=" << j << endl;

      // The current state.
      int row = startRow;
      int col = startCol;
      Direction dir = Direction::UP;

      // Copy the original grids to reset.
      auto grid = gridOG;
      auto gridDirs = gridDirsOG;

      grid[i][j] = '#'; // Add an obstacle and try.

      while (true) {

        // Check if we're out of bounds.
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
          // cout << "Doesn't create a cycle.\n";
          break;
        }

        // Check if we're at an obstacle.
        if (grid[row][col] == '#') {
          if (dir == Direction::UP) {
            row++;
            dir = Direction::RIGHT;
          }

          else if (dir == Direction::RIGHT) {
            col--;
            dir = Direction::DOWN;
          }

          else if (dir == Direction::DOWN) {
            row--;
            dir = Direction::LEFT;
          }

          else if (dir == Direction::LEFT) {
            col++;
            dir = Direction::UP;
          }

          continue;
        }

        // Check if we're in a cycle.
        if (grid[row][col] == 'X' && gridDirs[row][col].contains(dir)) {
          // cout << "Found a cycle!\n";
          cycleCount++;
          break;
        }

        // Otherwise, all is well and we can mark the current spot as visited.
        grid[row][col] = 'X';
        gridDirs[row][col].insert(dir);

        // Finally, let's move in the direction.
        if (dir == Direction::UP) {
          row--;
        }

        else if (dir == Direction::RIGHT) {
          col++;
        }

        else if (dir == Direction::DOWN) {
          row++;
        }

        else if (dir == Direction::LEFT) {
          col--;
        }
      }


      // cout << "grid\n";
      // cout << grid;


      // return 0;

    }
  }



  cout << cycleCount << endl;






}







/*

Problem:

Imagine if we end up going back and forth in a line. That is, we somehow get in this position:
 #
  #







#^
 #


In this case with our current implementation, we'd be overwriting our gridDirs!

So, at every gridDir cell, I want to instead keep a hashset<direction>, to store all the directions
we've ever seen so far. If we're on a cell we've seen before and ANY direction before is the same, cycle!


*/







