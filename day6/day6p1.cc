#include <bits/stdc++.h>
using namespace std;


ostream& operator<<(ostream& os, vector<vector<char>> vec) {
  for (const auto& line : vec) {
    for (char c : line) {
      os << c;
    }
    os << "\n";
  }

  return os;
}


enum class Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

int main() {

  string line;
  
  // Row and col refer to where the guard currently is in our simulation.
  int row;
  int col;

  vector<vector<char>> grid;
  size_t curRow = 0;
  while (getline(cin, line)) {
    vector<char> lineVec;
    for (size_t i = 0 ; i < line.size() ; i ++) {
      if (line[i] == '^') {
        row = curRow;
        col = i;
        lineVec.push_back('X');
      }

      else {
        lineVec.push_back(line[i]);
      }
    }
    curRow++;
    grid.emplace_back(lineVec);
  }


  cout << "Guard is at row=" << row << ", col=" << col << "\n";
  cout << grid << "\n";






  // Now, we'll start the actual simulation.
  Direction dir = Direction::UP;
  pair<int, int> movement{-1, 0}; // How to move up.

  while (true) { // The loop.

    // cout << "starting, row: " << row << ", col: " << col << endl;

    // Moving up.
    if (dir == Direction::UP) {
      // Mark the current position as an X.
      grid[row][col] = 'X';

      // Move in the direction required.
      row += -1;
      col += 0;
    }
    else if (dir == Direction::RIGHT) {
      grid[row][col] = 'X';
      row += 0;
      col += 1;
    }
    else if (dir == Direction::DOWN) {
      grid[row][col] = 'X';
      row += 1;
      col += 0;
    }
    else if (dir == Direction::LEFT) {
      grid[row][col] = 'X';
      row += 0;
      col += -1;
    }



    cout << "row: " << row << ", col: " << col << endl;

    // After moving, see if we are done, or have hit an obstacle.
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
      break; // You're done.
    }

    // cout << "cell after moving: " << grid[row][col] << "\n";


    if (grid[row][col] == '#') {
      // cout << "in here\n";
      if (dir == Direction::UP) {
        // cout << "test\n";
        // First, go downwards (away from the obstacle).
        row += 1;
        col += 0;

        // Then, turn right.
        dir = Direction::RIGHT;
      }

      else if (dir == Direction::RIGHT) {
        // First, go leftwards (away from the obstacle).
        row += 0;
        col += -1;

        // Then, turn down.
        dir = Direction::DOWN;
      }

      else if (dir == Direction::DOWN) {
        // First, go upwards (away from the obstacle).
        row += -1;
        col += 0;

        // Then, turn left.
        dir = Direction::LEFT;
      }

      else if (dir == Direction::LEFT) {
        // First, go rightwards (away from the obstacle).
        row += 0;
        col += 1;

        // Then, turn up.
        dir = Direction::UP;
      }
    }
  }


  cout << grid;


  // Now, we count the number of Xs.
  size_t count = 0;
  for (auto& line : grid) {
    for (auto& c : line) {
      if (c == 'X') count++;
    }
  }

  cout << count << endl;





}


/*

Notes:

Simulation

Assume that the guard doesn't go in circles- that is, the guard has to leave the area.

*/

