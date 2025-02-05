#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

bool isIncreasing(int first, int second) {
  return second - first > 0;
}

bool isSafe(const std::vector<int>& line) {

  const bool increasing = isIncreasing(line[0], line[1]);

  for (size_t i = 0; i < line.size() - 1; i++) {
    
    // Ensure in range.
    if (std::abs(line[i] - line[i+1]) > 3 || std::abs(line[i] - line[i+1]) < 1) return false;
    
    // Ensure they're still increasing/not increasing as before.
    bool curIncreasing = isIncreasing(line[i], line[i+1]);
    if (curIncreasing != increasing) return false;

  }

  return true;


}



int main() {
  // First, consume the input into a vector<vector<int>>.
  std::ifstream input("./input.txt");


  std::string line;
  std::vector<std::vector<int>> inputVec;
  while (getline(input, line)) {
    std::stringstream ss(line);

    std::string num;
    std::vector<int> lineVec;
    while (getline(ss, num, ' ')) {
      lineVec.push_back(std::stoi(num));
    }

    inputVec.emplace_back(lineVec);
  }

  // std::cout << inputVec.size() << " " << inputVec[0].size() << std::endl;
 

  // Iterate through the lines.
  int safeCount = 0;

  for (const auto& line : inputVec) {

    // Make a copy of the current line, skipping one value (at i).
    for (size_t i = 0; i < line.size(); i++) {
      std::vector<int> curLine;

      for (size_t j = 0; j < line.size(); j++) {
        if (j == i) continue;
        curLine.push_back(line[j]);
      }

      // std::cout << "CurLine: ";
      // for (auto num : curLine) std::cout << num << " ";
      // std::cout << std::endl;

      // See if this version of the line is safe.
      if (isSafe(curLine)) {
        // std::cout << "good!" << std::endl;
        safeCount++;
        break;
      }
    }
  }

  std::cout << safeCount << std::endl;


}

