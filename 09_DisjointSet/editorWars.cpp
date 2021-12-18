#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct BipartiteUnionFind {
	vector <int> parent;
	vector <int> rank;
	vector <int> enemy;
	vector <int> size;

	BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for(int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {

	}

};