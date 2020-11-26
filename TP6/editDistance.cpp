#include "editDistance.h"

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

map<pair<int, int>, int> distLevs;
int LevenshteinDistanceRecursiveMemory(string A, string B) {
	int m = A.length();
	int n = B.length();
	// if there is empty string
	if (m == 0) return n;
	if (n == 0) return m;

	// else
	int cost = A[m - 1] == B[n - 1] ? 0 : 1; // 0 if the last char of A == the last char of B, 1 otherwise

	pair<int, int> p1(m - 1, n);
	if (!distLevs.count(p1)) distLevs.insert(make_pair(p1, LevenshteinDistanceRecursiveMemory(A.substr(0, m - 1), B)));
	pair<int, int> p2(m, n - 1);
	if (!distLevs.count(p2)) distLevs.insert(make_pair(p2, LevenshteinDistanceRecursiveMemory(A, B.substr(0, n - 1))));
	pair<int, int> p3(m - 1, n - 1);
	if (!distLevs.count(p3)) distLevs.insert(make_pair(p3, LevenshteinDistanceRecursiveMemory(A.substr(0, m - 1), B.substr(0, n - 1))));

	return Min(distLevs[p1] + 1, distLevs[p2] + 1, distLevs[p3] + cost);
};

int LevenshteinDistanceIterative(string A, string B) {
	int m = A.length();
	int n = B.length();

	vector<vector<int> > distLevs(m + 1);
	for (int i = 0; i < m + 1; i++) {
		distLevs[i].resize(n + 1);
		distLevs[i][0] = i;
	}

	for (int i = 0; i < n + 1; i++) distLevs[0][i] = i;
	
	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			int cost = A[i - 1] == B[j - 1] ? 0 : 1;
			distLevs[i][j] = Min(distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost);
		}
	}

	return distLevs[m][n];
};