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



  // Put left and right pointers appropriately.
  
  size_t l;
  for (int i = 0 ; i < vecRep.size() ; i++) {
    if (vecRep[i] == -1) {
      l = i;
      break;
    }
  }

  size_t r;
  for (int i = vecRep.size() - 1; i >= 0 ; i--) {
    if (vecRep[i] != -1) {
      r = i;
      break;
    }
  }


  cout << l << " " << r << endl;


  cout << vecRep << endl;



  // Swap the elements when we have a free space.
  
  while (l < r) {

    vecRep[l] = vecRep[r];
    vecRep[r] = -1;

    // Find the next free space for l.
    while (l < r && vecRep[l] != -1) l++;

    // Find the next non-free space for r;
    while (l < r && vecRep[r] == -1) r--;

  }



  cout << vecRep << endl;



  // Finally, compute the checksum.
  unsigned long long sum = 0;
  for (size_t i = 0 ; i < vecRep.size(); i++) {
    if (vecRep[i] == -1) break;

    sum += i * vecRep[i];
  }

  cout << sum << endl;

}





/*

Take the puzzle input as a string.

Create an Explicit Vector representation from the string, e.g. string(12345) => vector<int>(0,.,.,1,1,1,.,.,.,.,2,2,2,2,2) (dots are -1)


Then, start iterating to fill up the free space, by keeping a left pointer and a right pointer coresspond to left meaning free space, right meaning next one to put

=> 

vector<int>(0,2,2,1,1,1,2,2,2,. )
                              lr





*/

