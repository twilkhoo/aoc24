#include <bits/stdc++.h>
using namespace std;


int main() {

  string line;
  unordered_map<int, vector<int>> graph;

  // First, keep inputting the dependencies until the blank row.
  while (getline(cin, line)) {

    if (line.empty()) break;
    
    stringstream ss(line);
    string token;
    vector<int> tokens;
    while (getline(ss, token, '|')) {
      tokens.push_back(stoi(token));
    }

    graph[tokens[0]].push_back(tokens[1]);
  }


  // Now, we'll analyze the comma lines.
  long sum = 0;
  while (getline(cin, line)) {

    stringstream ss(line);
    string token;
    unordered_set<int> seen; // All the numbers in the current line that we've already seen.
    vector<int> seenVec; // Just to maintain order.
    bool good = true;

    cout << "line: " << line << endl;

    // Parse a single line.
    while(getline(ss, token, ',')) {
      
      int curNum = stoi(token);
      cout << "curNum: " << curNum << endl;

      for (int num : graph[curNum]) {
        if (seen.contains(num)) {
          good = false;
          break;
        }
      }

      if (!good) break;
      seen.insert(curNum);
      seenVec.push_back(curNum);
    }

    if (good) {
      int midVal = seenVec[(seenVec.size()) / 2];
      cout << midVal << endl;
      sum += midVal;
    }


  }

  cout << sum << endl;

}


/*

Notes:

To validate if a sequence of numbers is valid, we first tabulate all dependencies as a hashmap { value => vector{nextElems} }

Ex consider we have dependencies
a|b, b|c, a|z.

Map would be: hashmap {
  a => vector{b, z} // If we have both a and b, then a needs to be printed before b.
  b => vector{c}
}

Then, for a particular input line, say we have a,b,c.
Iterate through the line.
Keep a seen set. So, when we get to element c, our seen set will have {a, b}.
For the current element c, iterate through it's outgoing elements, which indicate that if that c and that outgoing element are present, 
that outgoing element cannot come earlier. So, check if it exists in the earlier set and we're done!



*/

