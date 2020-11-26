#include "levenshtein.h";
map<pair<int, int>, int> distLevs;

int LevenshteinDistanceRecursive(string A, string B) {
	int m = A.length();
	int n = B.length();
	// if there is empty string
	if (m == 0) return n;
	if (n == 0) return m;

	// else
	int cost = A[m - 1] == B[n - 1] ? 0 : 1; // 0 if the last char of A == the last char of B, 1 otherwise
	return Min((LevenshteinDistanceRecursive(A.substr(0, m - 1), B) + 1), 
		(LevenshteinDistanceRecursive(A, B.substr(0, n - 1)) + 1), 
		(LevenshteinDistanceRecursive(A.substr(0, m - 1), B.substr(0, n - 1)) + cost));
};

int LevenshteinDistanceRecursiveMemory(string A, string B) {
	int m = A.length();
	int n = B.length();
	// if there is empty string
	if (m == 0) return n;
	if (n == 0) return m;

	// else
	int cost = A[m - 1] == B[n - 1] ? 0 : 1; // 0 if the last char of A == the last char of B, 1 otherwise

	pair<int, int> p1(m - 1, n);
	if (!distLevs.count(p1)) distLevs.insert(make_pair(p1, LevenshteinDistanceRecursive(A.substr(0, m - 1), B) + 1));
	pair<int, int> p2(m, n - 1);
	if (!distLevs.count(p2)) distLevs.insert(make_pair(p2, LevenshteinDistanceRecursive(A, B.substr(0, n - 1)) + 1));
	pair<int, int> p3(m - 1, n - 1);
	if (!distLevs.count(p3)) distLevs.insert(make_pair(p3, LevenshteinDistanceRecursive(A.substr(0, m - 1), B.substr(0, n - 1)) + cost));

	return Min(distLevs[p1], distLevs[p2], distLevs[p3]);
};