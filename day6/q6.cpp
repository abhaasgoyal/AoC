//
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define out_of_bounds_pos {-1, -1}

char switch_dir(char old_dir) {
  return old_dir == '^'   ? '>'
         : old_dir == '>' ? 'v'
         : old_dir == 'v' ? '<'
                          : '^';
}

pair<int, int> get_new_loc(vector<string> &maze, pair<int, int> &old_loc) {
  char status = maze[old_loc.first][old_loc.second];
  int new_i = status == '^'   ? old_loc.first - 1
              : status == 'v' ? old_loc.first + 1
                              : old_loc.first;
  int new_j = status == '<'   ? old_loc.second - 1
              : status == '>' ? old_loc.second + 1
                              : old_loc.second;
  if (new_i < 0 || new_j < 0 || new_i >= maze.size() ||
      new_j >= maze[0].size()) {
    return out_of_bounds_pos;
  }
  return {new_i, new_j};
}

bool algo(vector<string> &maze) {

  size_t m = maze.size();
  size_t n = maze[0].size();

  vector<vector<bool>> past_temp(m, vector<bool>(n, false));

  vector<vector<bool>> past_d(past_temp), past_u(past_temp), past_l(past_temp),
      past_r(past_temp);
  // Starting direction is always ^ (assumption)
  char current_dir = '^';

  pair<int, int> curr_loc;

  // Get starting position
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      if (maze[i][j] == '^') {
        curr_loc = {i, j};
      }
    }
  }
  const pair<int, int> check_pair = {-1, -1};

  while (true) {

    // New location
    pair<int, int> new_loc = get_new_loc(maze, curr_loc);
    maze[curr_loc.first][curr_loc.second] = 'X';

    // If new location is out of bounds
    if (new_loc == check_pair)
      return false;

    // Update lookups based on past visits
    if (current_dir == '>') {
      past_r[curr_loc.first][curr_loc.second] = true;
    } else if (current_dir == '<') {
      past_l[curr_loc.first][curr_loc.second] = true;
    } else if (current_dir == '^') {
      past_u[curr_loc.first][curr_loc.second] = true;
    } else if (current_dir == 'v') {
      past_d[curr_loc.first][curr_loc.second] = true;
    }

    if (maze[new_loc.first][new_loc.second] == '#') {
      // If obstacle is hit, switch 90 degrees
      current_dir = switch_dir(current_dir);
      maze[curr_loc.first][curr_loc.second] = current_dir;
    } else {
      // Move forward
      maze[new_loc.first][new_loc.second] = current_dir;
      curr_loc = new_loc;
    }

    // If already visited once in the same direction, a cycle will be formed
    if (past_d[new_loc.first][new_loc.second] && current_dir == 'v' ||
        past_u[new_loc.first][new_loc.second] && current_dir == '^' ||
        past_l[new_loc.first][new_loc.second] && current_dir == '<' ||
        past_r[new_loc.first][new_loc.second] && current_dir == '>') {
      return true;
    }
  }
  return false;
}

int main() {

  string line;
  ifstream input("input6.txt");
  int res;

  vector<string> maze;

  // Process input
  while (getline(input, line)) {
    maze.push_back(line);
  }

  vector<string> part1_maze(maze), temp_maze(maze);

  // Part 1
  res = 0;
  part1_maze = maze;
  algo(part1_maze);

  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      if (part1_maze[i][j] == 'X') {
        res++;
      }
    }
  }

  cout << "Part 1: " << res << endl;

  // Part 2
  res = 0;
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      /*  cout << i << " " << j << endl; */
      // Create copy of maze and amend with obstacle at all positions
      temp_maze = maze;

      // Don't edit the start position and only run the algorithm where hitting is possible
      if (temp_maze[i][j] == '^' || part1_maze[i][j] != 'X')
        continue;
      temp_maze[i][j] = '#';

      // Run Q1 algo
      res += algo(temp_maze);
    }
  }

  cout << "Part 2: " << res << endl;

  return 0;
}
