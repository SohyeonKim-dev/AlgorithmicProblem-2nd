#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// 간단한 문자열 검색 알고리즘 
// H : 짚더미(haystack)
// N : 바늘(needle)

vector <int> nativeSearch(const string& H, const string& N) {
	vector <int> ret;

	// 짚더미의 부분 문자열로, 바늘이 출현하는 시작 위치들을 모두 반환한다.

	for (int begin = 0; begin + N.size() <= H.size(); ++begin) {
		bool matched = true;
		for (int i = 0; i < N.size(); ++i) {
			if (H[begin + i] != N[i]) {
				matched = false;
				break;
			}
		}
		if (matched == true) {
			ret.push_back(begin);
		}
	}
	return ret;
}