#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// �κ� ��ġ ���̺� ���� �ڵ� Ȱ��

vector <int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1;
	int matched = 0;

	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				++begin;
			}
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}






// �縰��� ����� ������ �ذ��ϴ� kmp �˰����� ���� 
// a�� ���̻� and b�� ���λ��� ���ڿ��� �ִ� ���̸� ��ȯ�Ѵ�.

int maxOverlap(const string& a, const string& b) {
	int n = a.size();
	int m = b.size();

	vector<int> pi = getPartialMatch(b);

	int begin = 0;
	int matched = 0;

	while (begin < n) {
		if (matched < m && a[begin + matched] == b[matched]) {
			++matched;
			if (begin + matched == m) {
				return matched;
			}
		}
		else {
			if (matched == 0) {
				++begin;
			}
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}