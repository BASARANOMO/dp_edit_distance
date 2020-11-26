#include <string>;
using namespace std;

#define Min(a, b, c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int LevenshteinDistanceRecursive(string, string);  // Time comlexity: Omega(2^(max(n, m))), expon.

int LevenshteinDistanceRecursiveMemory();

