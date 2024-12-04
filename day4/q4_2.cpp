#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool check_str(int i, int j, vector<string> &lines) {
  int res = 0;
  // Check bounds
  if (i < 1 || j < 1 || i >= (lines.size() - 1) || j >= (lines[0].size() - 1)) {
    return false;
  }

  string d1 = "", d2 = "";

  d1 = d1 + lines[i - 1][j - 1] + lines[i + 1][j + 1];
  d2 = d2 + lines[i + 1][j - 1] + lines[i - 1][j + 1];

  return ((d1 == "MS" || d1 == "SM") && (d2 == "MS" || d2 == "SM"));
}

int main() {

  string line;
  ifstream input("input4.txt");
  vector<string> lines;
  long res = 0;

  // Process input
  while (getline(input, line)) {
    lines.push_back(line);
  }

  for (int i = 0; i < lines.size(); i++) {
    int j_size = lines[i].size();
    for (int j = 0; j < j_size; j++) {
      // Check for middle A and whether cross MS is formed
      if (lines[i][j] == 'A') {
        res += check_str(i, j, lines);
      }
    }
  }
  cout << res << endl;

  return 0;
}
