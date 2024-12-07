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

static bool is_part_two = false;

void reverseStack(stack<long> &s) {
  stack<long> reversed_stack;
  while (!s.empty()) {
    reversed_stack.push(s.top());
    s.pop();
  }
  s = reversed_stack;
}

bool algo(long tot_sum, stack<long> &factors) {
  // If sum has been crossed by the current stack
  if (tot_sum < 0)
    return false;

  long a = factors.top();
  factors.pop();

  if (factors.empty()) {
    return tot_sum == a;
  }

  long b = factors.top();
  factors.pop();

  stack<long> mul_factors(factors), add_factors(factors),
      concat_factors(factors);

  // 3 possibilities which could lead to the answer
  long add_temp = a + b;
  long mul_temp = a * b;
  long concat_temp = stol(to_string(a) + to_string(b));

  mul_factors.push(add_temp);
  add_factors.push(mul_temp);
  concat_factors.push(concat_temp);

  return algo(tot_sum, mul_factors) || algo(tot_sum, add_factors) ||
         (is_part_two ? algo(tot_sum, concat_factors) : false);
}

int main() {

  cout << "Enter 0 for Part(a) and 1 for Part(b)";
  cin >> is_part_two;

  string line;
  ifstream input("input7.txt");
  long res = 0;

  vector<pair<long, stack<long>>> sum_fact;

  // Process input
  while (getline(input, line)) {
    long a;
    string factor_str = line.substr(line.find(':') + 2);
    long total = stol(line.substr(0, line.find(':')));
    stringstream ss(factor_str);
    stack<long> factor;
    string substr;
    while (getline(ss, substr, ' ')) {
      factor.push(stol(substr));
    }
    sum_fact.push_back({total, factor});
  }

  for (auto &[sum, fact] : sum_fact) {
    reverseStack(fact);
    res += algo(sum, fact) ? sum : 0;
  }

  cout << res << endl;

  return 0;
}
