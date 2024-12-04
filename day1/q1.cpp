#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {

  string line;
  ifstream input("input1.txt");
  vector<int> a1, a2;
  long res = 0;

  while (getline(input, line)) {
    long i1, i2;
    istringstream os(line);
    os >> i1 >> i2;
    a1.push_back(i1);
    a2.push_back(i2);
  }

  sort(a1.begin(), a1.end());
  sort(a2.begin(), a2.end());

  for (int i = 0; i < a1.size(); i++) {
    res += abs(a1[i] - a2[i]);
  }

  cout << res;

  return 0;
}
