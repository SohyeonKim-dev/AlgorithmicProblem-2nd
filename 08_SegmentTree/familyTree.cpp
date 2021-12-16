#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int MAX_N = 100000;
int n;
vector <int> child[MAX_N];

int no2serial[MAX_N];
int serialno2[MAX_N];

int locInTrip[MAX_N];
int depth[MAX_N];

int nextSerial;

void traverse(int here, int d, vector<int>& trip) {
	no2serial[here] = nextSerial;
	serialno2[nextSerial] = here;
	++nextSerial;
	depth[here] = d;
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	for (int i = 0; i < child[here].size(); ++i) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(no2serial[here]);
	}
}

// 오류 발생 
RMQ* prepareRMQ() {
	nextSerial = 0;
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v) {
	int lu = locInTrip[u];
	int lv = locInTrip[v];

	if (lu > lv) {
		swap(lu, lv);
	}

	int lca = serialno2[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}




// segment tree 활용

const int int_MAX = numeric_limits<int>::max();

struct RMQ {
	int n;
	vector <int> rangeMin;

	RMQ(const vector <int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector <int>& array, int left, int right, int node) {
		if (left == right) {
			return rangeMin[node] = array[left];
		}
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	// int_MAX
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left) {
			return int_MAX;
		}
		if (left <= nodeLeft && nodeRight <= right) {
			return rangeMin[node];
		}
		int mid = (left + right) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	//외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || nodeRight < index) {
			return rangeMin[node];
		}
		if (nodeLeft == nodeRight) {
			return rangeMin[node] = newValue;
		}
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(
			update(index, newValue, node * 2, nodeLeft, mid),
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight)
		);
	}

	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};