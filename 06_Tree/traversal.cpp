#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// [ Ʈ�� ��ȸ ���� ���� ������ �ذ��ϴ� ��� ȣ�� �ڵ� ]


vector <int> slice(const vector <int>& v, int a, int b) {
	return vector <int> (v.begin() + a, v.begin() + b);
}


// Ʈ���� ����/���� Ž�� ����� �־��� ��, ���� Ž�� ����� ����Ѵ�.
void printPostOrder(const vector <int>& preorder, const vector <int>& inorder) {
	const int N = preorder.size();
	// N : Ʈ���� ���Ե� �� ����� �� 

	if (preorder.empty()) {
		return;
	}

	const int root = preorder[0];
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	// �� Ʈ���� ���� ���� Ʈ���� ũ��� ����Ž������ ��Ʈ�� ��ġ�� ã�� �� �� �ִ�.

	const int R = N - 1 - L;
	// �� Ʈ���� ������ ���� Ʈ���� ũ��� N�� L�� ���Ͽ� �� �� �ִ�. 

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	// ��� ȣ��� Ʈ���� ��ȸ ����� ��� 

	cout << root << ' ';
}