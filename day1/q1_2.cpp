#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {

  string line;
  ifstream input("input1.txt");
  unordered_map<long, long> m;
  vector<long> a;
  long res = 0;

  // Idea: Store instances of the right side in hashmap
  while (getline(input, line)) {
    long i1, i2;
    istringstream os(line);
    os >> i1 >> i2;
    a.push_back(i1);
    if (m.find(i2) != m.end()) {
      m[i2]++;
    } else {
      m[i2] = 1;
    }
  }

  for (int i = 0; i < a.size(); i++) {
    res += a[i] * m[a[i]];
  }

  cout << res;

  return 0;
}
