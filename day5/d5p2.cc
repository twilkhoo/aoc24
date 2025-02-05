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

    cout << line << endl;

    stringstream ss(line);
    string token;
    vector<int> nums;
    unordered_set<int> numsSet;

    // Parse a single line into a vector.
    while(getline(ss, token, ',')) {
      nums.push_back(stoi(token));
      numsSet.insert(stoi(token));
    }


    // This is the check to see whether or not a line is good.
    unordered_set<int> seen; // All the numbers in the current line that we've already seen.
    bool good = true;

    unordered_map<int, vector<int>> miniGraph; // An adjlist only consisting of nodes in the current line, for TopoSort.
    unordered_map<int, vector<int>> miniGraphBack; // Going from neighbor to num (backwards).

    for (int num : numsSet) miniGraph[num]; // Create an empty vector at every node.
    for (int num : numsSet) miniGraphBack[num];


    for (int num : nums) {
      for (int neighbor : graph[num]) {
        // num => neighbor means that num must come before neighbor.
        // So, if seen contains the neighbor, that means neighbor came before num, bad!
        if (seen.contains(neighbor)) good = false;

        // At the same time, start building a graph (adjlist) for only the nodes present in the current line.
        if (numsSet.contains(neighbor)) {
          miniGraph[num].push_back(neighbor);
          miniGraphBack[neighbor].push_back(num);
        }
      }

      seen.insert(num);
    }

    if (good) {
      cout << "This is good" << endl;
      continue;
    }


    // Print the miniGraph.
    cout << "MINIGRAPH:\n";
    for (auto& [num, neighbors] : miniGraph) {
      cout << num << " : { ";
      for (int val : neighbors) cout << val << " ";
      cout << "}\n";
    }

    cout << "MINIGRAPHBACK:\n";
    for (auto& [num, neighbors] : miniGraphBack) {
      cout << num << " : { ";
      for (int val : neighbors) cout << val << " ";
      cout << "}\n";
    }

    // Otherwise, we must order it properly.
    // To order it properly, we need to extract only the edges that are relevant to the current line.
    // That is, only have edges that have nodes in the current numsSet set.
    // We've done the extraction above in miniGraph.
    // Now, we need to run Kahn's algo to toposort.
    
    deque<int> q;

    // Create an indegree count, and init the queue with all indegree 0 nodes.
    // miniGraphBack goes from neighbor => num, so this will identify all indegree 0 nodes.
    unordered_map<int, int> indegreeCounts;
    for (const auto& [num, neighbors] : miniGraphBack) {
      indegreeCounts[num] = neighbors.size();
      if (neighbors.size() == 0) q.push_back(num);
    }

    // Iteratively pop from the queue and push on the next values.
    vector<int> solved;
    while (q.size()) {
      int nextNum = q.front();
      solved.push_back(nextNum);
      q.pop_front();

      // Decrement the values of indegree counts from the neighbors of what we just popped.
      for (int neighbor : miniGraph[nextNum]) {
        indegreeCounts[neighbor]--;
        if (indegreeCounts[neighbor] == 0) q.push_back(neighbor);
      }
    }

    cout << solved.size() << endl;

    // Add the middle element of the solved vector to the sum.
    sum += solved[solved.size() / 2];
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



Part 2:

For part 2, we need to take the incorrectly ordered elements and order them properly.










*/

