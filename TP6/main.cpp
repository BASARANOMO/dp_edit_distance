#include "levenshtein.h"
#include <iostream>

int main() {
	string A = "ecoles";
	string B = "eclose";

	int distLev = LevenshteinDistanceRecursive(A, B);
	cout << distLev << endl;

	distLev = LevenshteinDistanceRecursiveMemory(A, B);
	cout << distLev << endl;

	return 0;
};