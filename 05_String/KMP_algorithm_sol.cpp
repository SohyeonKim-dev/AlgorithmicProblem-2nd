#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// 커누스 - 모리스 - 프랫 (KMP) 문자열 검색 알고리즘의 구현
// 여태까지 일치했었던 검색어의 부분 문자열에서 (접두사 = 접미사)의 최대 길이를 활용




// N에서 자기 자신과의 부분 일치 찾으면서 pi[] 계산! 
// pi[i] : N[..i] 의 접미사도 되고, 접두사도 되는 문자열의 최대 길이

vector <int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1; 
	int matched = 0;
	// begin = 0이면 자기 자신을 찾아버리니까 안된다! 


	while (begin + matched < m) {
		// 비교할 문자가 N의 끝에 도달할 때 까지
		// 부분 일치를 모두 기록한다.
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
			// Maybe.. begin 하나 빼둔 것 때문에..?
		}

		else {
			if (matched == 0) {
				++begin;
				// 맞는 문자가 하나도 없다면 앞으로 한칸 옮기기
			}
			else {
				begin += matched - pi[matched - 1];
				// 시작 지점 옮기기
				matched = pi[matched - 1];
				// 맞는 글자수를 matched에 저장 
			}
		}
	}
	return pi;
	// pi의 각 원소는 최대 한 번만 변경되기 때문에 max() 연산이 필요 없다. 
	// 아 벡터 그대로 KMP 알고리즘에서 받는다! 
}





// 짚더미 H의 부분 문자열로 바늘 N이 출현하는 시작 위치들을 모두 반환한다. 
vector <int> kmpSearch(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();
	vector <int> ret;


	// 접미사도 되고, 접두사도 되는 문자열의 최대 길이
	// 이 겹치는 부분이 KMP 알고리즘의 핵심 아이디어다.
	vector <int> pi = getPartialMatch(N);

	int begin = 0;
	int matched = 0;

	while (begin <= n - m) {	// 굳이 n 끝까지 다 돌 필요 없으니깐
		if (matched < m && H[begin + matched] == N[matched]) {
			// 짚더미 H의 해당 글자가 바늘 N의 해당 글자와 같다면
			// matched 하나 늘림 : 맞는 글자수를 임시로 저장해두는 기능!
			++matched;

			if (matched == m) {
				ret.push_back(begin);
				// 모든 부분 문자열이 일치한다면 (바늘 길이와 같아진다면)
				// 찾은 거니깐 정답 배열(벡터)에 저장!
			}
		}
		else {
			if (matched == 0) {
				++begin;
				// 예외 처리
			}
			else {
				// 완전 처음 다음칸부터 시작 X
				// 일치하는 부분으로 (접미사) 옮겨간다! 
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}




