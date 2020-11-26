#ifndef _LEVENSHTEIN_H_
#define _LEVENSHTEIN_H_

#include <string>;
#include <map>;
using namespace std;

#define Min(a, b, c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int LevenshteinDistanceRecursive(string, string);  // Time comlexity: Omega(2^(max(n, m))), expon.

extern map<pair<int, int>, int> distLevs;

int LevenshteinDistanceRecursiveMemory(string, string);

#endif