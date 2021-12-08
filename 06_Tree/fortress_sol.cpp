#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*

	[ 문제 ]

중세의 성과 요새들은 보안을 튼튼히 하면서도 더 넓은 영역을 보호하기 위해 여러 개의 성벽을 갖고 있었다고 하지요.
전세계에서 가장 편집증이 심한 영주가 지은 스트로고(Strawgoh) 요새는 이의 극치를 보여줍니다.
이 요새는 그림과 같이 커다란 원형 외벽 내에 여러 개의 원형 성벽이 겹겹이 지어진 형태로 구성되어 있는데,
어떤 성벽에도 문이 없어서 성벽을 지나가려면 사다리를 타고 성벽을 오르내려야 합니다.
요새 내에서도 한 곳에서 다른 곳으로 이동하는 데 시간이 너무 오래 걸린다는 원성이 자자해지자,
영주는 요새 내에서 왕래가 불편한 곳들을 연결하는 터널을 만들기로 했습니다.
계획을 세우기 위해 요새 내에서 서로 왕래하기 위해 가장 성벽을 많이 넘어야 하는 두 지점을 찾으려고 합니다.
예를 들어 위 그림의 경우, 별표로 표시된 두 지점 간을 이동하기 위해서는 다섯 번이나 성벽을 넘어야 하지요.

성벽들의 정보가 주어질 때 가장 성벽을 많이 넘어야 하는 두 지점 간을 이동하기 위해
몇 번이나 성벽을 넘어야 하는지 계산하는 프로그램을 작성하세요.

출처 : https://algospot.com/judge/problem/read/FORTRESS

*/





// [ 트리에서 가장 긴 경로 찾기 ]

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




// [실제 구현]

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
	// 성벽 a가 성벽 b를 포함하는지 확인한다.
}


//성벽 트리에서 parent가 child의 부모인지 확인한다.
// parent는 child를 직접 포함해야 한다.
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



// 주어진 번호의 성벽에 포함된 구역들을 표현하는 트리 생성
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ++ch) {
		if (isChild(root, ch)) {
			ret->children.push_back(getTree(ch));
		}
		// ch 성벽이 root 성벽에 직접적으로 포함되어 있다면
		// 트리를 만들고 자손 목록에 추가한다.
	}
	return ret;
}