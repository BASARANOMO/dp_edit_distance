#include "editDistance.h"
#include <iostream>
#include <time.h>

int main() {
	string A = "ecoles";
	string B = "eclose";

	cout << "Recursive solution: ";
	clock_t t1 = clock();
	int distLev = LevenshteinDistanceRecursive(A, B);
	clock_t t2 = clock();
	cout << distLev << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;

	cout << "Recursive solution with memorization: ";
	t1 = clock();
	distLev = LevenshteinDistanceRecursiveMemory(A, B);
	t2 = clock();
	cout << distLev << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;

	cout << "Iterative solution: ";
	t1 = clock();
	distLev = LevenshteinDistanceIterative(A, B);
	t2 = clock();
	cout << distLev << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;
	return 0;
};