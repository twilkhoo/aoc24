#include <bits/stdc++.h>
using namespace std;


int main() {

  // Consume the input.
  string lineStr;
  vector<string> input;
  while (getline(cin, lineStr)) {
    input.emplace_back(lineStr);
  }


  // Categorize the antennas based on type.
  unordered_map<char, vector<pair<size_t, size_t>>> antennas;

  for (size_t row = 0 ; row < input.size() ; row++) {
    for (size_t col = 0 ; col < input[0].size() ; col++) {
      if (input[row][col] == '.') continue;
      antennas[input[row][col]].emplace_back(row, col);
    }
  }

  // For every pair of antennas of the same type, compute their antinodes.
  // If they're in bounds, mark them on the antinode map.



  // A helper function to see if we're in bounds.

  auto isInBounds = [&](const pair<int, int>& point) -> bool {
    bool good = !(point.first < 0 || point.first >= input.size() || point.second < 0 || point.second >= input[0].size());

    cout << "point: { " << point.first << " , " << point.second << " } is " << good << endl;

    return !(point.first < 0 || point.first >= input.size() || point.second < 0 || point.second >= input[0].size());
  };


  vector<vector<bool>> antinodes(input.size(), vector<bool>(input[0].size(), false));

  for (const auto& [c, antennaLocations] : antennas) {

    cout << "analyzing char " << c << endl << endl;

    for (size_t i = 0 ; i < antennaLocations.size() ; i++) {
      for (size_t j = i + 1 ; j < antennaLocations.size() ; j++) {

        // cout << "location with i = " << i << ", j = " << j << endl;
        
        const pair<size_t, size_t>& first = antennaLocations[i];
        const pair<size_t, size_t>& second = antennaLocations[j];

        cout << "First: { " << first.first << " , " << first.second << " }" << endl;
        cout << "Second: { " << second.first << " , " << second.second << " }" << endl;

        int rowDiff = second.first - first.first;
        int colDiff = second.second - first.second;

        pair<int, int> newPoint1(first.first - rowDiff, first.second - colDiff);
        pair<int, int> newPoint2(second.first + rowDiff, second.second + colDiff);

        cout << "newPoint1: { " << newPoint1.first << " , " << newPoint1.second << " }" << endl;
        cout << "newPoint2: { " << newPoint2.first << " , " << newPoint2.second << " }" << endl;

        if (isInBounds(newPoint1)) antinodes[newPoint1.first][newPoint1.second] = true;
        cout << "added first" << endl;
        if (isInBounds(newPoint2)) antinodes[newPoint2.first][newPoint2.second] = true;
        cout << "added second" << endl;

        cout << "good" << endl;
      }
    }
  }



  // Read off where we have antinodes.
  unsigned int count = 0;
  for (const auto& line : antinodes) {
    for (const auto& bad : line) {
      if (bad) count++;
    }
  }

  cout << count << endl;

}


/*

Notes:

To do this, first keep track of all antennas based on type, in a hashmap { type => list { locations } }

Then, for every two nodes of the same type, it will create 2 antinodes. Mark off the in-bound antinodes they create, on a 2d grid.

Finally, simply read off the antinodes found on the answer grid.


*/



