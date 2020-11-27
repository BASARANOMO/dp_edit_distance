#include "editDistance.h"
#include <time.h>

int main() {
	string A = "¨¦coles";
	string B = "eclose";
	clock_t t1;
	clock_t t2;
	int distLev;

	/*
	cout << "Recursive solution: ";
	t1 = clock();
	distLev = LevenshteinDistanceRecursive(A, B);
	t2 = clock();
	cout << distLev << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;
	*/

	printf("\n");
	cout << "Recursive solution with memorization: ";
	t1 = clock();
	distLev = LevenshteinDistanceRecursiveMemory(A, B);
	t2 = clock();
	cout << distLev << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;

	printf("\n");
	cout << "Iterative solution: ";
	t1 = clock();
	vector<vector<int> > distLevs = LevenshteinDistanceIterative(A, B);
	t2 = clock();
	cout << distLevs[A.length()][B.length()] << endl;
	cout << "Execution time: " << (t2 - t1) / float(CLOCKS_PER_SEC) << endl;

	printf("\n");
	printPath(distLevs, A, B, false);

	printf("\n");
	printPath(distLevs, A, B, true);
	return 0;
}