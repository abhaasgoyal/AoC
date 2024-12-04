#include <iostream>
#include <regex>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() { return 0; }

/*
 * Philosophy - Treat Problems like CTF, one can use existing tools
 *
 * (a) Steps
 * 1. In regex101.com, I used the following command
 * (mul\([0-9]{1, 3},[0-9]{1,3}\))
 * 2. Substitute with $1+
 * 3. Remove the final +
 * 4. Open python interpreter and create a mul function a*b
 * 5. Paste the result and get the answer
 *
 * (b) Steps
 * 1. Use the following regex to lazily remove muls between don't() and do() and
 * remove line breaks
 * (?s)(don't\()\).*?(do\(\))
 * 2. Use steps in (a)
 *
 */
