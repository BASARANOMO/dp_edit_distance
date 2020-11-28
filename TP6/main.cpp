#include "editDistance.h"
#include <time.h>

int main() {
	string A = "abc";
	string B = "ca";
	clock_t t1;
	clock_t t2;
	int distLev;
	vector<vector<int> > distLevs;

	printf("String 1: '%s'\n", A.c_str());
	printf("String 2: '%s'\n", B.c_str());

	printf("\n***************************** Levenshtein distance *****************************\n");
	/*
	cout << "Recursive solution result: ";
	t1 = clock();
	distLev = LevenshteinDistanceRecursive(A, B);
	t2 = clock();
	cout << distLev << endl;
	printf("Execution time: %f sec.\n", (t2 - t1) / float(CLOCKS_PER_SEC));
	*/

	cout << "\nRecursive solution with memorization result: ";
	t1 = clock();
	distLev = LevenshteinDistanceRecursiveMemory(A, B);
	t2 = clock();
	cout << distLev << endl;
	printf("Execution time: %f sec.\n", (t2 - t1) / float(CLOCKS_PER_SEC));

	cout << "\nIterative solution result: ";
	t1 = clock();
	distLevs = editDistanceIterative(A, B); // Levenshtein Distance
	t2 = clock();
	cout << distLevs[A.length()][B.length()] << endl;
	printf("Execution time: %f sec.\n", (t2 - t1) / float(CLOCKS_PER_SEC));

	printf("\n");
	printPathLevDist(distLevs, A, B, false);

	printf("\n");
	printPathLevDist(distLevs, A, B, true);

	printf("\n************************* Damerau-Levenshtein distance *************************\n");
	cout << "Iterative solution result: ";
	t1 = clock();
	distLevs = editDistanceIterative(A, B, true);  // Damerau-Levenshtein Distance
	t2 = clock();
	cout << distLevs[A.length() + 1][B.length() + 1] << endl;
	printf("Execution time: %f sec.\n", (t2 - t1) / float(CLOCKS_PER_SEC));


	return 0;
}