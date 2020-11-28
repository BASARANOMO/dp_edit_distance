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

vector<vector<int> > editDistanceIterative(string A, string B, bool DamerauLevenshteinDist) {
	if (DamerauLevenshteinDist) return DamerauLevenshteinDistanceIterative(A, B);
	else return LevenshteinDistanceIterative(A, B);
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
	
	int cost;
	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			cost = A[i - 1] == B[j - 1] ? 0 : 1;
			distLevs[i][j] = Min(distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost);
		}
	}

	return distLevs;
}

// This is not the true DL distance
vector<vector<int> > optimalStringAlignmentDistanceIterative(string A, string B) {
	int m = A.length();
	int n = B.length();

	vector<vector<int> > distLevs(m + 1);
	for (int i = 0; i < m + 1; i++) {
		distLevs[i].resize(n + 1);
		distLevs[i][0] = i;
	}

	for (int i = 0; i < n + 1; i++) distLevs[0][i] = i;

	int cost;
	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			cost = A[i - 1] == B[j - 1] ? 0 : 1;
			distLevs[i][j] = Min(distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost);

			if ((i > 2) && (j > 2) && (A[i - 1] == B[j - 2]) && (A[i - 2] == B[i - 1])) {
				distLevs[i][j] = min(distLevs[i][j], distLevs[i - 2][j - 2] + 1);
			}
		}
	}

	return distLevs;
}

/*
inspired by the solution of:
Boytsov L. 
Indexing methods for approximate dictionary searching: Comparative analysis[J]. 
Journal of Experimental Algorithmics (JEA), 2011, 16: 1.1-1.91.
doi:10.1145/1963190.1963191
*/
vector<vector<int> > DamerauLevenshteinDistanceIterative(string A, string B) {
	int m = A.length();
	int n = B.length();
	int maxDist = m + n;
	int vecASCII[256];
	memset(vecASCII, 0, sizeof(vecASCII));

	vector<vector<int> > distLevs(m + 2);
	for (int i = 0; i < m + 2; i++) distLevs[i].resize(n + 2);

	distLevs[0][0] = maxDist;
	for (int i = 0; i < m + 1; i++) {
		distLevs[i + 1][0] = maxDist;
		distLevs[i + 1][1] = i;
	}
	for (int i = 0; i < n + 1; i++) {
		distLevs[0][i + 1] = maxDist;
		distLevs[1][i + 1] = i;
	}

	int temp, k, l, cost;
	for (int i = 1; i < m + 1; i++) {
		temp = 0;
		for (int j = 1; j < n + 1; j++) {
			k = vecASCII[B[j - 1]];
			l = temp;
			cost = A[i - 1] == B[j - 1] ? 0 : 1;
			if (cost == 0) temp = j;

			distLevs[i + 1][j + 1] = Min(distLevs[i][j + 1] + 1, distLevs[i + 1][j] + 1, distLevs[i][j] + cost);
			distLevs[i + 1][j + 1] = min(distLevs[i + 1][j + 1], distLevs[k][l] + (i - k - 1) + 1 + (j - l - 1));
		}
		vecASCII[A[i - 1]] = i;
	}

	return distLevs;
}

void printPathLevDist(vector<vector<int> > distLevs, string A, string B, bool fromFrontToBack) {
	if (fromFrontToBack) printPathLevDistFrontToBack(distLevs, A, B);
	else printPathLevDistBackToFront(distLevs, A, B);
}

void printPathLevDistBackToFront(vector<vector<int> > distLevs, string A, string B) {
	int i = distLevs.size() - 1;
	int j = distLevs[0].size() - 1;
	string temp = A;
	printf("Operations required to convert '%s' to '%s' (from back to front): \n", A.c_str(), B.c_str());
	while ((i > 0) || (j > 0)) {
		if (i == 0) {
			temp.insert(0, 1, B[j - 1]);
			--j;
		}
		else if (j == 0) {
			temp.erase(i - 1, 1);
			--i;
		}
		else {
			int cost = A[i - 1] == B[j - 1] ? 0 : 1;
			array<int, 3> val{ distLevs[i - 1][j] + 1, distLevs[i][j - 1] + 1, distLevs[i - 1][j - 1] + cost };
			int idx = argmin(val.begin(), val.end());
			if (idx == 0) {
				temp.erase(i - 1, 1);
				//printf("Delete the %dth char '%c' of the first string\n", i, A[i - 1]);
				--i;
			}
			if (idx == 1) {
				temp.insert(i, 1, B[j - 1]);
				//printf("Add char '%c' at the position %d of the first string\n", B[j - 1], i + 1);
				--j;
			}
			if (idx == 2) {
				--i;
				--j;
				if (cost == 0) continue;
				else temp.replace(i, 1, 1, B[j]);
			}
		}
		printf("'%s' -> '%s'\n", A.c_str(), temp.c_str());
		A = temp;
	}
	cout << "End." << endl;
}

void printPathLevDistFrontToBack(vector<vector<int> > distLevs, string A, string B) {
	int i = distLevs.size() - 1;
	int j = distLevs[0].size() - 1;
	stack<tuple<int, int, int> > stk;

	while ((i > 0) || (j > 0)) {
		if (i == 0) {
			stk.push(make_tuple(1, i, j));
			--j;
		}
		else if (j == 0) {
			stk.push(make_tuple(0, i, j));
			--i;
		}
		else {
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
