#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
// 단순한 정수형 벡터 형식으로 힙 선언
vector <int> heap;





// 정수 원소를 갖는 힙에 새로운 원소 추가하기

void push_heap(vector <int>& heap, int newValue) {
	heap.push_back(newValue);
	int idx = heap.size() - 1;

	while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
		swap(heap[idx], heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}





// 정수 원소를 갖는 힙에서 최대 원소 삭제하기

void pop_heap(vector <int>& heap) {
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;

	while (true) {
		int left = here * 2 + 1;
		int right = here * 2 + 2;
		if (left >= heap.size()) {
			break;
		}
		int next = here;
		if (heap[next] < heap[left]) {
			next = left;
		}
		if (right < heap.size() && heap[next] < heap[right]) {
			next = right;
		}
		if (next == here) {
			break;
		}
		swap(heap[here], heap[next]);
		here = next;
	}
}

struct RNG {
	int seed;
	int a;
	int b;

	RNG(int _a, int _b) : a(_a), b(_b), seed(1983){}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};


/*

int runningMedian(int n, RNG rng) {
	Node* root = NULL;
	int ret = 0;

	for (int cnt = 1; cnt <= n; ++cnt) {
		root = insert(root, new Node(rng.next()));
		int median = kth(root, (cnt + 1) / 2)->key;
		ret = (ret + median) % 20090711;
	}
	return ret;
}

*/


int runningMedian(int n, RNG rng) {
	priority_queue <int, vector<int>, less<int> > maxHeap;
	priority_queue <int, vector<int>, greater<int> > minHeap;
	int ret = 0;

	for (int cnt = 1; cnt <= n; ++cnt) {
		if (maxHeap.size() == minHeap.size()) {
			maxHeap.push(rng.next());
		}
		else {
			minHeap.push(rng.next());
		}
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top();
			int b = minHeap.top();

			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}
