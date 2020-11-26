#include "levenshtein.h";

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