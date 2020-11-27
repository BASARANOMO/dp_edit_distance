#include "editDistance.h"
#include <time.h>

int main() {
	string A = "horse";
	string B = "ros";
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
	printPathLevDist(distLevs, A, B, false);

	printf("\n");
	printPathLevDist(distLevs, A, B, true);
	return 0;
}