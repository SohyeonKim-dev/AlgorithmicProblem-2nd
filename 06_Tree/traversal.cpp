#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// [ 트리 순회 순서 변경 문제를 해결하는 재귀 호출 코드 ]


vector <int> slice(const vector <int>& v, int a, int b) {
	return vector <int> (v.begin() + a, v.begin() + b);
}


// 트리의 전위/중위 탐색 결과가 주어질 때, 후위 탐색 결과를 출력한다.
void printPostOrder(const vector <int>& preorder, const vector <int>& inorder) {
	const int N = preorder.size();
	// N : 트리에 포함된 총 노드의 수 

	if (preorder.empty()) {
		return;
	}

	const int root = preorder[0];
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	// 이 트리의 왼쪽 서브 트리의 크기는 중위탐색에서 루트의 위치를 찾아 알 수 있다.

	const int R = N - 1 - L;
	// 이 트리의 오른쪽 서브 트리의 크기는 N과 L을 통하여 알 수 있다. 

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	// 재귀 호출로 트리의 순회 결과를 출력 

	cout << root << ' ';
}