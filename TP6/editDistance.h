#ifndef _EDITDISTANCE_H_
#define _EDITDISTANCE_H_

#include <string>
#include <vector>
#include <array>
#include <map>
#include <stack>
#include <algorithm>
#include <iostream>
//#include <stdio.h>
using namespace std;

#define Min(a, b, c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int LevenshteinDistanceRecursive(string, string);  // Time comlexity: Omega(2^(max(n, m))), expon.

extern map<pair<int, int>, int> distLevs;

int LevenshteinDistanceRecursiveMemory(string, string);

vector<vector<int> > LevenshteinDistanceIterative(string, string);

void printPathLevDist(vector<vector<int> >, string, string, bool);
void printPathLevDistBackToFront(vector<vector<int> >, string, string);
void printPathLevDistFrontToBack(vector<vector<int> >, string, string);

template<class ForwardIterator>
inline int argmin(ForwardIterator first, ForwardIterator last)
{
    return distance(first, min_element(first, last));
}
#endif