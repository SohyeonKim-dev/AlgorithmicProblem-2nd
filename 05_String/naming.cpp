#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



/*
s의 접두사도 되고, 접미사도 되는 문자열들의 길이를 반환한다.
벡터 pi를 받아, 조건을 만족하는 k를 넣어가며 생성한 ret을 반환한다.
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





// 부분 일치 문자열은 기존에 작성한 코드 활용

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