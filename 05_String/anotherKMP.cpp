#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


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








vector <int> kmpSearch2(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();
	vector <int> ret;
	vector <int> pi = getPartialMatch(N);

	int matched = 0;


	// 짚더미의 각 글자들을 순회한다.
	for (int i = 0; i < n; ++i) {
		while (matched > 0 && H[i] != N[matched]) {
			matched = pi[matched - 1];
			// 불일치할 경우 -> 현재 대응된 글자의 수를 pi[matched-1]로 줄인다. 
		}

		// 글자가 대응되는 경우
		if (H[i] == N[matched]) {
			++matched;
			if (matched == m) {
				// 끝!
				ret.push_back(i - m + 1);
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}