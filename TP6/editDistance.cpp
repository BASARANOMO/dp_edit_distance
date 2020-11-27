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
}

map<pair<int, int>, int> distLevs;
int LevenshteinDistanceRecursiveMemory(string A, string B) {
	int m = A.length();
	int n = B.length();
	// if there is empty string
	if (m == 0) return n;
	if (n == 0) return m;

	// else
	int cost = A[m - 1] == B[n - 1] ? 0 : 1; // 0 if the last char of A == the last char of B, 1 otherwise

	pair<int, int> p0(m - 1, n);
	if (!distLevs.count(p0)) distLevs.insert(make_pair(p0, LevenshteinDistanceRecursiveMemory(A.substr(0, m - 1), B)));
	pair<int, int> p1(m, n - 1);
	if (!distLevs.count(p1)) distLevs.insert(make_pair(p1, LevenshteinDistanceRecursiveMemory(A, B.substr(0, n - 1))));
	pair<int, int> p2(m - 1, n - 1);
	if (!distLevs.count(p2)) distLevs.insert(make_pair(p2, LevenshteinDistanceRecursiveMemory(A.substr(0, m - 1), B.substr(0, n - 1))));

	return Min(distLevs[p0] + 1, distLevs[p1] + 1, distLevs[p2] + cost);
}

vector<vector<int> > LevenshteinDistanceIterative(string A, string B) {
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

	return distLevs;
}

void printPathLevDist(vector<vector<int> > distLevs, string A, string B, bool fromFrontToBack = true) {
	if (fromFrontToBack) printPathLevDistFrontToBack(distLevs, A, B);
	else printPathLevDistBackToFront(distLevs, A, B);
}

void printPathLevDistBackToFront(vector<vector<int> > distLevs, string A, string B) {
	int i = distLevs.size() - 1;
	int j = distLevs[0].size() - 1;
	printf("Operations required to convert '%s' to '%s' (from back to front): \n", A.c_str(), B.c_str());
	while ((i > 0) && (j > 0)) {
		int cost = A[i - 1] == B[j - 1] ? 0 : 1;
		array<int, 3> val{ distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost };
		int idx = argmin(val.begin(), val.end());
		if (idx == 0) {
			printf("Delete the %dth char '%c' of the first string\n", i, A[i - 1]);
			--i;
		}
		if (idx == 1) {
			printf("Add char '%c' at the position %d of the first string\n", B[j - 1], i + 1);
			--j;
		}
		if (idx == 2) {
			if (cost == 1) {
				printf("Replace the %dth char '%c' of the first string by the char '%c'\n", i, A[i - 1], B[j - 1]);
			}  // else: do nothing
			--i;
			--j;
		}
	}
	cout << "End." << endl;
}

void printPathLevDistFrontToBack(vector<vector<int> > distLevs, string A, string B) {
	int i = distLevs.size() - 1;
	int j = distLevs[0].size() - 1;
	stack<tuple<int, int, int> > stk;

	while ((i > 0) && (j > 0)) {
		int cost = A[i - 1] == B[j - 1] ? 0 : 1;
		array<int, 3> val{ distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost };
		int idx = argmin(val.begin(), val.end());
		// note down idx, i and j as a tuple in a stack
		if ((idx != 2) or (cost != 0)) stk.push(make_tuple(idx, i, j));
		if (idx == 0) --i;
		if (idx == 1) --j;
		if (idx == 2) {
			--i;
			--j;
		}
	}

	tuple<int, int, int> tup;  // idx, cost, i, j
	string temp = A;
	int posModif = 0;
	printf("Operations required to convert '%s' to '%s' (from front to back): \n", A.c_str(), B.c_str());
	while (!stk.empty()) {
		tup = stk.top();
		stk.pop();
		if (get<0>(tup) == 0) {
			temp.erase(get<1>(tup) - 1 + posModif, 1);
			posModif--;
		}
		if (get<0>(tup) == 1) {
			temp.insert(get<1>(tup) + posModif, 1, B[get<2>(tup) - 1]);
			posModif++;
		}
		if (get<0>(tup) == 2) {
			temp.replace(get<1>(tup) - 1 + posModif, 1, 1, B[get<2>(tup) - 1]);
		}
		printf("'%s' -> '%s'\n", A.c_str(), temp.c_str());
		A = temp;
	}
	cout << "End." << endl;
}
