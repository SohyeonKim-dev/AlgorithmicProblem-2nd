#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



/*
s�� ���λ絵 �ǰ�, ���̻絵 �Ǵ� ���ڿ����� ���̸� ��ȯ�Ѵ�.
���� pi�� �޾�, ������ �����ϴ� k�� �־�� ������ ret�� ��ȯ�Ѵ�.
*/

vector <int> getPrefixSuffix(const string& s) {
	vector <int> ret;
	vector <int> pi = getPartialMatch(s);
	int k = s.size();

	while (k > 0) {
		ret.push_back(k);
		k = pi[k - 1];
	}
	return ret;
}





// �κ� ��ġ ���ڿ��� ������ �ۼ��� �ڵ� Ȱ��

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