#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int main() {

  string line;
  ifstream input("input5.txt");

  vector<vector<int>> edges;

  // Process ordering and save as edges
  while (getline(input, line)) {
    int a, b;
    char c;
    if (line.empty())
      break;
    istringstream os(line);
    os >> a >> c >> b;
    edges.push_back({a, b});
  }

  int res = 0;
  while (getline(input, line)) {
    vector<int> check_order;
    stringstream ss(line);
    string substr;
    while (getline(ss, substr, ',')) {
      int x;
      istringstream os(substr);
      os >> x;
      check_order.push_back(x);
    }

    bool isSubSeq = true;

    // Brute force approach for now since question isn't framed well
    // For optimizations to implement ig
    for (int i = 0; i < check_order.size() - 1; i++) {
        for (int j = i + 1; j < check_order.size(); j++) {
            bool temp = false;
            for (auto edge : edges) {
                if (edge[0] == check_order[i] && edge[1] == check_order[j]) {
                    // change 1 (kinda like bublesort)
                    swap(check_order[i], check_order[j]);
                    temp = true;
                }
            }
            isSubSeq &= temp;
        }
    }

    // Change 2 (the ones which were said no)
    if(!isSubSeq) {
      int mid = (check_order.size() / 2);
      res += check_order[mid];
    }
  }

  cout << res;
  return 0;
}
