#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// 기존 코드 (kmp 알고리즘)

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



vector <int> kmpSearch(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();
	vector <int> ret;

	vector <int> pi = getPartialMatch(N);
	int begin = 0;
	int matched = 0;

	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				ret.push_back(begin);
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
	return ret;
}




// 환형 시프트 연산 
// circular Shift

int shifts(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

/*


[시계 방향으로 돌리기]

- shifts(a,b) -> a에서 반시계 방향으로 몇 칸을 돌려야 b를 얻는가?
- a에서 시계 방향으로 몇 칸을 돌려야 b를 얻는가? ---> shifts(b,a)
- a를 시계 방향으로 돌려서 b를 얻는 경우와
  b를 반시계 방향으로 돌려 a를 얻는 경우에 
  돌려야 하는 칸의 개수는 일치하기 때문이다.



*/





// [ 접미사 배열을 계산하는 단순한 알고리즘 ]
// 
// 정렬 알고리즘 활용 : 문자열의 길이가 n, [0, n-1] 범위의 정수 배열을 정렬
// 두 정수를 비교할 때 해당 위치에서 시작하는 접미사들을 비교한다. 


struct SuffixComparator {
	const string& s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator () (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		// substr 대신에 strcmp를 사용하면 임시 객체를 만드는 비용이 절약된다.
	}
};

vector <int> getSuffixArrayNaive(const string& s) {
	vector <int> perm;
	for (int i = 0; i < s.size(); ++i) {
		perm.push_back(i);
	}
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}