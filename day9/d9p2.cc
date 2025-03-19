#include <bits/stdc++.h>
using namespace std;



ostream& operator<<(ostream& out, const vector<int>& vec) {

  out << "{ ";

  for (const auto& num : vec) {
    if (num == -1) {
      out << "." << " ";
    } else {
      out << num << " ";
    }
  }

  out << "}";

  return out;  
}




int main() {


  string inputStr;
  getline(cin, inputStr);

  cout << inputStr << endl;


  // Now, create an Explicit Vector Representation of our string, based on the problem requirements.

  vector<int> vecRep;
  bool isFreeSpace = false;
  size_t curId = 0;

  for (char c : inputStr) {

    size_t digit = c - '0';
    
    // Adding free space.
    if (isFreeSpace) {
      for (size_t i = 0 ; i < digit ; i++) {
        vecRep.push_back(-1);
      }
    }

    // Adding the doc id.
    else {
      for (size_t i = 0 ; i < digit ; i++) {
        vecRep.push_back(curId);
      }
      curId++;
    }

    isFreeSpace = !isFreeSpace;
  }

  cout << "Initial vecRep: \n";
  cout << vecRep << endl;


  // file representation: tuple{ id, startPos, length }
  vector<tuple<size_t, size_t, size_t>> files;


  int curDigit = vecRep[vecRep.size() - 1];
  size_t len = 1;


  for (int i = vecRep.size() - 2; i >= 0; i--) {
    
    // We have a new digit.
    if (curDigit != vecRep[i]) {
      files.emplace_back(curDigit, i + 1, len);

      // Keep iterating backwards until i isn't a -1;
      while (vecRep[i] == -1) {
        i--;
      }

      curDigit = vecRep[i];
      len = 1;
    }

    // Continuing on with the current digit.
    else {
      len++;
    }

  }

  // Don't forget to add the last element!
  files.emplace_back(curDigit, 0, len);


  cout << "Files: \n";
  // Print out the files just to make sure.
  for (auto [digit, startPos, len] : files) {

    cout << "{ " << digit << " " << startPos << " " << len << "}\n";

  }







  // Now, create a similar list only for free spaces.

  // space representation: pair{ startPos, length }
  vector<pair<size_t, size_t>> spaces;


  len = 0;
  size_t startPos = 0;
  for (size_t i = 0; i < vecRep.size(); i++) {
    
    if (vecRep[i] != -1) {
      if (len == 0) continue; // We didn't have a free space anyway.

      // Otherwise, this new digit marks the end of a free space!
      spaces.emplace_back(startPos, len);
      len = 0;
      startPos = 0;
    }

    // Otherwise, we're building a free space.
    else {

      if (len == 0) {
        startPos = i;
      }

      len++;
    }

  }

  // No need to add the last space, since this would be beyond the files (never used).

  cout << "spaces: \n";
  // Print out the spaces just to make sure.
  for (auto [startPos, len] : spaces) {

    cout << "{ " << startPos << " " << len << "}\n";

  }




  cout << endl << endl << endl;





  // Finally, iterate through the files and see if we can put it in a free space.
  for (auto [fileDigit, fileStartPos, fileLen] : files) {

    for (auto& [spaceStartPos, spaceLen] : spaces) {

      // If the spaceStartPos > fileStartPos, just break, since we don't want to move the file further than where it currently is.
      if (spaceStartPos > fileStartPos) break;

      // We can put it in this space!
      if (spaceLen >= fileLen) {
        // Write this file in the new location in the vecRep.
        for (size_t i = spaceStartPos; i < spaceStartPos + fileLen; i++) {
          vecRep[i] = fileDigit;
        }

        // Erase this file's previous position.
        for (size_t i = fileStartPos; i < fileStartPos + fileLen; i++) {
          vecRep[i] = -1;
        }

        // Adjust the space details.
        spaceLen = spaceLen - fileLen;
        spaceStartPos += fileLen;

        // Don't check any others if we found a match.
        break;
      }

    }


    // cout << "vecRep is now: " << vecRep << endl;

    // cout << "Files now: \n";
    // for (auto [digit, startPos, len] : files) {
    //   cout << "{ " << digit << " " << startPos << " " << len << "}\n";
    // }

    // cout << "Spaces now: \n";
    // for (auto [startPos, len] : spaces) {
    //   cout << "{ " << startPos << " " << len << "}\n";
    // }
  }

  cout << "Final vecRep: \n";
  cout << vecRep << endl;






  // Finally, compute the checksum.
  unsigned long long sum = 0;
  for (size_t i = 0 ; i < vecRep.size(); i++) {
    if (vecRep[i] == -1) continue;

    sum += i * vecRep[i];
  }

  cout << sum << endl;

}





/*

Notes:


After we have our explicit vector representation, let's get extract a list of files including {id, length, startPos}.

Let's make this list backwards, e.g. starting with the higher id numbers and higher start positions.

Then, for every file (starting from the bigger ones), iterate over the explicit vector representation. 
If we have something that fits in a free space, place it in the first one.



*/