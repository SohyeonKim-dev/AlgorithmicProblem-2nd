#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*

	[ ���� ]

�߼��� ���� ������� ������ ưư�� �ϸ鼭�� �� ���� ������ ��ȣ�ϱ� ���� ���� ���� ������ ���� �־��ٰ� ������.
�����迡�� ���� �������� ���� ���ְ� ���� ��Ʈ�ΰ�(Strawgoh) ����� ���� ��ġ�� �����ݴϴ�.
�� ����� �׸��� ���� Ŀ�ٶ� ���� �ܺ� ���� ���� ���� ���� ������ ����� ������ ���·� �����Ǿ� �ִµ�,
� �������� ���� ��� ������ ���������� ��ٸ��� Ÿ�� ������ ���������� �մϴ�.
��� �������� �� ������ �ٸ� ������ �̵��ϴ� �� �ð��� �ʹ� ���� �ɸ��ٴ� ������ ����������,
���ִ� ��� ������ �շ��� ������ ������ �����ϴ� �ͳ��� ������ �߽��ϴ�.
��ȹ�� ����� ���� ��� ������ ���� �շ��ϱ� ���� ���� ������ ���� �Ѿ�� �ϴ� �� ������ ã������ �մϴ�.
���� ��� �� �׸��� ���, ��ǥ�� ǥ�õ� �� ���� ���� �̵��ϱ� ���ؼ��� �ټ� ���̳� ������ �Ѿ�� ������.

�������� ������ �־��� �� ���� ������ ���� �Ѿ�� �ϴ� �� ���� ���� �̵��ϱ� ����
�� ���̳� ������ �Ѿ�� �ϴ��� ����ϴ� ���α׷��� �ۼ��ϼ���.

��ó : https://algospot.com/judge/problem/read/FORTRESS

*/





// [ Ʈ������ ���� �� ��� ã�� ]

struct TreeNode {
	vector <TreeNode*> children;
};

// ���ݱ��� ã�� ���� �� leaf-leaf ���̸� �����Ѵ�.
int longest;

int height(TreeNode* root) {
	vector <int> heights;
	// �� �ڽ��� ��Ʈ�� �ϴ� ���� Ʈ���� ���̸� ����Ѵ�.
	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i]));
	}

	if (heights.empty()) {
		return 0;
		// �ڽ��� ���ٸ� 0
	}

	sort(heights.begin(), heights.end());
	if (heights.size() >= 2) {
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
		// root�� �ֻ��� ���� �ϴ� ���.
	}
	return heights.back() + 1;
	// ����Ʈ�� ���̿� 1�� ���Ͽ� Ʈ���� ���� ���
}

// �� ��� ���̿� ���� �� ��θ� ����Ѵ�.
int solve(TreeNode* root) {
	longest = 0;
	int h = height(root);
	return max(longest, h);
	// Ʈ���� �ִ� ���� vs leaf-leaf ���� �� ū �� ����
	// Ʈ�� �ִ� ���̰� ���� ���� �� �� �� ����!
}




// [���� ����]

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
	// ���� a�� ���� b�� �����ϴ��� Ȯ���Ѵ�.
}


//���� Ʈ������ parent�� child�� �θ����� Ȯ���Ѵ�.
// parent�� child�� ���� �����ؾ� �Ѵ�.
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



// �־��� ��ȣ�� ������ ���Ե� �������� ǥ���ϴ� Ʈ�� ����
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ++ch) {
		if (isChild(root, ch)) {
			ret->children.push_back(getTree(ch));
		}
		// ch ������ root ������ ���������� ���ԵǾ� �ִٸ�
		// Ʈ���� ����� �ڼ� ��Ͽ� �߰��Ѵ�.
	}
	return ret;
}