#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool algo(vector<long> a) {
  if (a.size() < 2) {
    return true;
  }
  // Whether a sequence is supposed to be increasing or decreasing
  bool inc = a[0] < a[1];
  for (int i = 0; i < a.size() - 1; i++) {
    // Check for inc/dec and abs difference
    if ((inc && a[i] >= a[i + 1]) || (!inc && a[i] <= a[i + 1]) ||
        (abs(a[i] - a[i + 1]) < 1) || (abs(a[i] - a[i + 1]) > 3)) {
      return false;
    }
  }
  return true;
}

int main() {

  string line;
  ifstream input("input2.txt");
  long res = 0;

  while (getline(input, line)) {
    long i;
    vector<long> a;
    istringstream os(line);
    while (os >> i) {
      a.push_back(i);
    }
    bool any_pos = false;
    for (int i = 0; i < a.size(); i++) {
      // By removing any 1 integer, create a new string
      // Use original algorithm on that
      // I mean it's not efficient but sample input is small enough for O(n^2)
      vector<long> a_copy(a);
      a_copy.erase(a_copy.begin() + i);
      any_pos |= algo(a_copy);
    }
    res += any_pos;
  }

  cout << res;

  return 0;
}
