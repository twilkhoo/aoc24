#include <bits/stdc++.h>

using namespace std;

enum class Direction { TOPLEFT = 1, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

bool findRest(const vector<vector<char>> grid, int startRow, int startCol,
              size_t maxRow, size_t maxCol, Direction dir, string remaining) {
  // cout << "Calling findRest with row=" << startRow << ", col=" << startCol
      //  << "\n";

  if (remaining.empty()) return true;

  if (startRow < 0 || startRow > maxRow || startCol < 0 || startCol > maxCol)
    return false;

  // See if we don't have a match for the current char.

  if (*remaining.rbegin() != grid[startRow][startCol]) return false;

  // Otherwise, this char matched, and go in the direction.

  int rowDir, colDir;

  switch (dir) {
    case (Direction::TOPLEFT) : {
      rowDir = -1;
      colDir = -1;
      break;
    }

    case (Direction::TOPRIGHT) : {
      rowDir = -1;
      colDir = 1;
      break;
    }

    case (Direction::BOTTOMLEFT) : {
      rowDir = 1;
      colDir = -1;
      break;
    }

    default : { // Direction::BOTTOMRIGHT
      rowDir = 1;
      colDir = 1;
      break;
    }
  }

  remaining.pop_back();
  return findRest(grid, startRow + rowDir, startCol + colDir, maxRow, maxCol,
                  dir, remaining);
}


// Function to print a 2D vector of chars
void print2DVector(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char c : row) {
            std::cout << c << ' ';  // Print each character followed by a space
        }
        std::cout << '\n';         // Move to the next line after each row
    }
}

struct Occurence {
  size_t row;
  size_t col;
  Direction dir;
};

struct OccurenceHash {
  std::size_t operator()(const Occurence& key) const {
    std::size_t h1 = std::hash<size_t>()(key.row);
    std::size_t h2 = std::hash<size_t>()(key.col);
    std::size_t h3 = std::hash<Direction>()(key.dir);
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};

struct OccurenceEqual {
  bool operator()(const Occurence& lhs, const Occurence& rhs) const {
    return lhs.row == rhs.row && lhs.col == rhs.col && lhs.dir == rhs.dir;
  }
};

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

  print2DVector(grid);

  cout << maxRow << endl;
  cout << maxCol << endl;


  unordered_set<Occurence, OccurenceHash, OccurenceEqual> answers;

  for (size_t row = 0; row <= maxRow; row++) {
    for (size_t col = 0; col <= maxCol; col++) {
      // Check if we have a match in any direction here.
      for (size_t dir = 1; dir <= 4; dir++) {

        // cout << "Trying row=" << row << ", col=" << col << ", dir=" << dir << "\n";

        if (findRest(grid, row, col, maxRow, maxCol, static_cast<Direction>(dir), "SAM")) {
          cout << "Found an occurence! With row=" << row << ", col=" << col << ", dir=" << dir << "\n";
          
          Occurence occ{row, col, static_cast<Direction>(dir)};
          answers.insert(occ);
        }
      }
    }
  }


  // Now, iterate through each answer and see if we can make an x.
  long xCount = 0;
  for (const auto [row, col, dir] : answers) {
    cout << row << " " << col << " " << static_cast<size_t>(dir) << "\n";

    switch (dir) {
      case (Direction::TOPLEFT) : {

        Occurence opt1{row-2, col, Direction::BOTTOMLEFT};
        Occurence opt2{row, col-2, Direction::TOPRIGHT};
        if (answers.contains(opt1) || answers.contains(opt2)) xCount++;

        break;
      }

      case (Direction::TOPRIGHT) : {

        Occurence opt1{row-2, col, Direction::BOTTOMRIGHT};
        Occurence opt2{row, col+2, Direction::TOPLEFT};
        if (answers.contains(opt1) || answers.contains(opt2)) xCount++;

        break;
      }

      case (Direction::BOTTOMLEFT) : {

        Occurence opt1{row+2, col, Direction::TOPLEFT};
        Occurence opt2{row, col-2, Direction::BOTTOMRIGHT};

        if (answers.contains(opt1) || answers.contains(opt2)) xCount++;

        break;
      }

      default : {

        Occurence opt1{row+2, col, Direction::TOPRIGHT};
        Occurence opt2{row, col+2, Direction::BOTTOMLEFT};
        if (answers.contains(opt1) || answers.contains(opt2)) xCount++;


        break;
      }
    }

  }

  cout << answers.size() << "\n";
  cout << xCount / 2 << "\n"; // Divided by 2 to avoid doubule counting.
}

/*

Notes:

First, let's find every occurence of MAS, in a diagonal way.

Then, say we have a MAS with M starting from [0,1], going bottom right. And,
let's say we have a MAS starting from [2,1] going top right. Is this a pair?
Yes!

In general, if we have a MAS with M starting from [row, col], going:
- bottom right, need [row+2, col] going top right or [row, col+2] going bottom
left
- bottom left, need [row+2, col] going top left or [row, col-2] going bottom
right
- top right, need [row-2, col] going bottom right or [row, col+2] going top left
- top left, need [row-2, col] going bottom left or [row, col-2] going top right.

So, after finding all the (row, col, dir) tuples, put them in a hash map, and
see what pairs we have. Half the final value to account for double counting.

*/
