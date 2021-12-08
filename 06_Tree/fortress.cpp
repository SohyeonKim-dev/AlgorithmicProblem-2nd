#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



struct TreeNode {
	vector <TreeNode*> children;
};

// 지금까지 찾은 가장 긴 leaf-leaf 길이를 저장한다.
int longest;

int height(TreeNode* root) {
	vector <int> heights;
	// 각 자식을 루트로 하는 서브 트리의 높이를 계산한다.
	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i]));
	}

	if (heights.empty()) {
		return 0;
		// 자식이 없다면 0
	}

	sort(heights.begin(), heights.end());
	if (heights.size() >= 2) {
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
		// root를 최상위 노드로 하는 경로.
	}
	return heights.back() + 1;
	// 서브트리 높이에 1을 더하여 트리의 높이 계산
}


// 두 노드 사이에 가장 긴 경로를 계산한다.
int solve(TreeNode* root) {
	longest = 0;
	int h = height(root);
	return max(longest, h);
	// 트리의 최대 높이 vs leaf-leaf 길이 중 큰 것 선택
	// 트리 최대 높이가 잎잎 보다 길 수 도 있음!
}




int n;
int y[100];
int x[100];
int radius[100];


int sqr(int x) {
	return x * x;
}

int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

bool encloses(int a, int b) {
	return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}

bool isChild(int parent, int child) {
	if (!encloses(parent, child)) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child)) {
			return false;
		}
	}
	return true;
}


TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ++ch) {
		if (isChild(root, ch)) {
			ret->children.push_back(getTree(ch));
		}
	}
	return ret;
}