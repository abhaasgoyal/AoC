#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool check_str(int i, int j, vector<string> &lines, char dir, char c) {

  // Check bounds
  if (i < 0 || j < 0 || i >= lines.size() || j >= lines[0].size()) {
    return false;
  }

  // Check character match
  if (lines[i][j] != c) {
    return false;
  }

  // Which char to check next (N represents everything has been checked)
  char next_c = c == 'X' ? 'M' : c == 'M' ? 'A' : c == 'A' ? 'S' : 'N';

  // Success XMAS - N
  if (next_c == 'N') {
    return true;
  }

  // Continue check for M/A/S
  // Update index based on direction
  if (dir == '6' || dir == '7' || dir == '8') {
    j -= 1;
  }
  if (dir == '2' || dir == '3' || dir == '4') {
    j += 1;
  }
  if (dir == '8' || dir == '1' || dir == '2') {
    i -= 1;
  }
  if (dir == '4' || dir == '5' || dir == '6') {
    i += 1;
  }

  return check_str(i, j, lines, dir, next_c);
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

  // Iterate through every character in the maze
  for (int i = 0; i < lines.size(); i++) {
    int j_size = lines[i].size();
    for (int j = 0; j < j_size; j++) {
      /* 1-8 represent from North to North West clockwise */
      string dirs = "12345678";
      for (char &d : dirs) {
        // Start checking from X in all directions
        // If match, add to res
        res += check_str(i, j, lines, d, 'X');
      }
    }
  }
  cout << res << endl;

  return 0;
}
