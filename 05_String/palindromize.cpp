#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// 부분 일치 테이블 기존 코드 활용

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






// 펠린드롬 만들기 문제를 해결하는 kmp 알고리즘의 변형 
// a의 접미사 and b의 접두사인 문자열의 최대 길이를 반환한다.

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