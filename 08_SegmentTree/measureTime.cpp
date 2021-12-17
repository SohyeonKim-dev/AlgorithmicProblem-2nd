#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct FenWickTree {
	vector <int> tree;
	FenWickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};


// 삽입 정렬 시간 재기 문제를 펜윅 트리로 해결하기
long long countMoves(const vector <int>& A) {
	FenWickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}


// 이진 검색 (treap) 활용하여 해결하기 

/*
void deleteTree(Node* node) {
	if (node == NULL) {
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

long long countMoves2(const vector <int>& A) {
	Node* root = NULL;
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += i - countLessThan(root, A[i] + 1);
		root = insert(root, new Node(A[i]));
	}
	deleteTree(root);
	return ret;
}

*/


// 3. 병합 정렬을 활용한 해결도 가능하다. 