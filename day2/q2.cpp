#include <iostream>
#include <algorithm>
#include <fstream>
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

  // Get input
  while (getline(input, line)) {
    long i;
    vector<long> a;
    istringstream os(line);
    while (os >> i) {
      a.push_back(i);
    }

    res += algo(a);

  }

  cout << res;

  return 0;
}
