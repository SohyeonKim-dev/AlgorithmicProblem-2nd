#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// [ 접미사 배열 : 문자열의 맥가이버 칼 ]
// 특정 문자열 s의 모든 접미사를 사전 순으로 정렬해둔 것




// 두 접미사 i와 j가 주어질 때,
// 둘 중 어느 쪽이 앞에 와야하는지 결정

struct SuffixComparator {
	const string& s;
	SuffixComparator(const string & s) : s(s) {}
	bool operator () (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		// s.substr() 대신 strcmp를 사용하면 임시 객체를 만드는 비용이 절약된다.
	}
};


// s의 접미사 배열을 계산
vector <int> getSuffixArrayNaive(const string& s) {
	vector <int> perm;
	for (int i = 0; i < s.size(); ++i) {
		perm.push_back(i);
	}
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	// 접미사를 비교하는 비교자를 이용하여 정렬! 
	return perm;
}





/*

	[ 접미사 배열을 만드는 맨버-마이어스의 알고리즘 ]

- 각 접미사들의 첫 t 글자를 기준으로 한 그룹 번호가 주어질 때,
  주어진 두 접미사를 첫 2t 글자를 기준으로 비교한다. 
- group은 길이가 0인 접미사도 포함한다. 

*/

struct Comparator {
	const vector <int>& group;
	int t;
	Comparator(const vector <int>& _group, int _t) : group(_group), t(_t) 
	{
		//group = _group;
		t = _t;
	}

	bool operator () (int a, int b) {
		if (group[a] != group[b]) {
			return group[a] < group[b];
			// 첫 글자가 다르다면 그룹으로만 비교 가능
		}
		return group[a + t] < group[b + t];
		// 같다면, 다음 그룹으로 넘어가 비교.
	}
};



// 접미사 배열을 계산하는 맨버와 마이어스의 알고리즘

vector <int> getSuffixArray(const string& s) {		// s의 접미사 배열을 계산한다.
	int n = s.size();
	int t = 1;
	// 첫 t글자 기준으로 group 분류함

	vector <int> group(n + 1);
	for (int i = 0; i < n; ++i) {
		group[i] = s[i];
	}
	group[n] = -1;


	// 결과적으로 접미사 배열이 될 반환값
	// 이 배열을 log(n)번 정렬함
	vector <int> perm(n);
	for (int i = 0; i < n; ++i) {
		perm[i] = i;
	}

	while (t < n) {
		Comparator compareUsing2T(group, t);
		// 첫 2t 글자를 기준으로 perm을 다시 정렬한다. 
		sort(perm.begin(), perm.end(), compareUsing2T);
		t *= 2;
		if (t >= n) {
			break;
		}

		vector <int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 0; i < n; ++i) {
			if (compareUsing2T(perm[i - 1], perm[i])) {
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			}
			else {
				newGroup[perm[i]] = newGroup[perm[i - 1]];
			}
		}
		group = newGroup;
	}
	return perm;
}




// ex) 원형 문자열
// 접미사 배열을 사용해 원형 문자열 문제를 해결하는 알고리즘의 구현
// 2개의 문자열을 이어 붙인다! ( ex) s + s )

string minShift(const string& s) {
	string s2 = s + s;
	vector <int> a = getSuffixArray(s2);
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] <= s.size()) {
			return s2.substr(a[i], s.size());
		}
	}
	return "__oops__";
}





// [ 접미사 배열을 활용하여 다른 부분 문자열의 수를 세는 알고리즘 ]
// 공통 접두사의 최대 길이를 계산한다.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i;
		++j;
		++k;
	}
	return k; // 공통 접두사의 최대 길이
}


// s의 서로 다른 부분 문자열의 수를 센다.
int countSubstrings(const string& s) {
	vector <int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		// cp 개는 중복이다!

		if (i > 0) {
			cp = commonPrefix(s, a[i - 1], a[i]);
			ret += n - a[i] - cp;
		}
	}
	return ret;
}




/*

	[ 문제 ]

대중 앞에서 연설이나 강의를 하는 사람들은 말 중간중간에
습관적으로 들어가는 말버릇들을 없애기 위해 많은 노력을 합니다. 
강의를 하는 사람이 한 마디 할 때마다 "음~" 혹은 "그래서요~" 같은 말을 반복하면 잘 신뢰가 가지 않기 때문이지요.

다음 학기에 처음으로 학부 강의를 맡게 된 정박사는 자신의 버릇을 고치기 위해 알고스팟 웅변 학원에 찾아왔습니다.
알고스팟 웅변 학원에서는 수강생들이 과거에 한 발표 자료들을 자동화된 프로그램으로 분석해
고쳐야 할 말버릇들을 정확히 짚어냅니다.

정박사가 지금까지 했던 발표들과 강의들에서 했던 말을 모두 음성 인식을 통해 대본으로 만들었습니다.
이 때 대본 중 K 번 이상 등장하는 부분 문자열을 "말버릇" 이라고 합시다.
우선 가장 티가 많이 나는 것부터 고치기 위해 가장 긴 말버릇을 찾으려 합니다.

대본이 주어질 때 가장 긴 말버릇의 길이를 찾는 프로그램을 작성하세요.

출처 : https://algospot.com/judge/problem/read/HABIT

*/



// 공통 접두사의 최대 길이!
int commonPrefix(const string& s, int i, int j);

// k 번 이상 출현하는 s의 부분 문자열 중에서 최대 길이를 찾는다. 
int longestFrequent(int k, const string& s) {
	vector <int> a = getSuffixArray(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); ++i) {
		ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
	}
	return ret;
}