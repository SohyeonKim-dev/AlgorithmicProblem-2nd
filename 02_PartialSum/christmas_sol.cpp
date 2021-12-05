#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
[완전 탐색 알고리즘]

1. 한 조각만 해결한다.
2. 나머지는 재귀 호출로 해결
*/


/*

		[ 크리스마스 ]


크리스마스를 맞이하여 산타 할아버지는 전세계의 착한 어린이 K명에게 인형을 사주려고 한다. 
산타 할아버지는 인형을 구입하기 위해서 유명한 인형가게인 "놀이터"에 찾아갔다.
놀이터에는 N개의 인형 상자가 한 줄로 진열되어 있고, 각 인형 상자에는 한 개 이상의 인형이 들어 있다.
그리고 놀이터에서는 주문의 편의성을 위해 각 상자에 번호를 붙여 놓았고,
주문은 "H번 상자부터 T번 상자까지 다 주세요."라고만 할 수 있다. (H ≤ T)

산타 할아버지는 한 번 주문할 때마다, 주문한 상자에 있는 인형들을 모두 꺼내서
각각을 K명에게 정확히 같은 수만큼 나누어 주고, 남는 인형이 없도록 한다.

한 번 주문할 수 있다면, 가능한 주문 방법은 몇 가지인가?
여러 번 주문할 수 있다면, 주문이 겹치지 않게 최대 몇 번 주문할 수 있는가?
(주문이 겹친다는 것은 어떤 두 주문에 같은 번호의 인형 상자가 포함되는 것을 말한다.)

출처 : https://algospot.com/judge/problem/read/CHRISTMAS



- point : 아이들에게 인형을 모두 나누어주려면, 인형의 총 수가 K의 배수여야 한다. 
- pusm[-1] = 0 이라는 가정을 현실로 옮긴다. (부분 합을 사용할 때 자주 사용하는 기법)

*/



int waysToBuy(const vector <int> psum, int k) {
	const int MOD = 20211204;
	int ret = 0;

	vector <long long> count(k, 0);
	// psum[]의 각 값을 몇 번이나 보았는지 기록

	for (int i = 0; i < psum.size(); ++i) {
		count[psum[i]]++;
	}

	// 두 번 이상 본 적 있다면, 이중 두개를 선택하는 방법의 수를 더한다.
	for (int i = 0; i < k; ++i) {
		if (count[i] >= 2) {
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
		}
	}
	return ret;
}


/*
- 부분합 배열 psum과 k명의 어린이가 주어질 때, 
  겹치지 않게 몇 번이나 살 수 있는지 반환한다. 
- psum의 첫번째 원소 전에 0을 삽입했다고 가정한다. 
*/

int maxBuys(const vector <int>& psum, int k) {
	vector <int> ret(psum.size(), 0);
	// ret[i] = 첫~i번째 상자까지 고려했을 때 살 수 있는 최대 횟수

	vector <int> prev(k, -1);
	// prev[s] : psum[] 이 s였던 마지막 위치

	for (int i = 0; i < psum.size(); ++i) {
		if (i > 0) {
			ret[i] = ret[i - 1];
			// i번째 상자를 전혀 고려하지 않음
		}
		else {
			ret[i] = 0;
		}

		int loc = prev[psum[i]];
		if (loc != -1) {
			ret[i] = max(ret[i], ret[loc] + 1);
			// psum[i]를 전에도 본 적이 있다면
			// prev[psum[i]]+1 부터 여기까지 쭉 사본다. 
		}
		prev[psum[i]] = i;
		// prev에 현재 위치를 기록한다. 
	}
	return ret.back();
}