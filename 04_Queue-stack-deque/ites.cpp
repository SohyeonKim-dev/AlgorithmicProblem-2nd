#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

/*

	온라인 알고리즘 vs 오프라인 알고리즘


*/

/*


	[문제]


수환이는 외계에서 날아오는 전파를 연구하는 범세계 대규모 프로젝트, ITES@home에 참가하고 있습니다.
외계에서 날아오는 전파는 전처리를 거쳐 각 숫자가 [1,10000] 범위 안에 들어가는 자연수 수열로 주어지는데,
이 전파가 과연 단순한 노이즈인지 아니면 의미 있는 패턴을 가지고 있는 것인지를 파악하고 싶습니다.
수환이는 전파의 부분 수열 중에 합이 K인 것이 유독 많다는 것을 눈치챘습니다.
부분 수열이란 연속된 수열의 일부를 말합니다.

예를 들어 수열 {1,4,2,1,4,3,1,6} 에서 합이 7 인 부분 수열은 모두 5개 있습니다.
{1,4,2} , {4,2,1} , {2,1,4}, {4,3}, {1,6} 이 부분 수열들은 서로 겹쳐도 된다는 데 유의합시다.

K가 외계인에게 의미 있는 숫자일까요?
수환이의 가설을 확인하기 위해, 길이 N인 신호 기록이 주어질 때
합이 K인 부분 수열이 몇 개나 있는지 계산하는 프로그램을 작성하세요.


*/


// 가장 단순한 알고리즘 

/*

int simple(const vector <int>& signals, int k) {
	int ret = 0;
	for (int head = 0; head < signals.size(); ++head) {
		int sum = 0;
		for (int tail = head; tail < signals.size(); ++tail) {
			sum += signals[tail];
			if (sum == k) {
				ret++;
			}
			if (sum >= k) {
				break;
			}
		}
	}
	return ret;
}

*/



// 최적화된 알고리즘

int optimize(const vector <int>& signals, int k) {
	int ret = 0;
	int tail = 0;
	int rangeSum = signals[0];

	for (int head = 0; head < signals.size(); ++head) {
		while (rangeSum < k && tail + 1 < signals.size()) {
			rangeSum += signals[++tail];
		}
		if (rangeSum == k) {
			ret++;
		}
		rangeSum -= signals[head];
	}
	return ret;
}






// 온라인 알고리즘 and 선형 ㅎ바동 난수 생성기 구현 
// Linear Congruential Random Number Generator

struct RNG {
	unsigned seed;
	RNG () : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

int countRanges(int k, int n) {
	RNG rng;
	queue <int> range;
	int ret = 0;
	int rangeSum = 0;

	for (int i = 0; i < n; i++) {
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}
	}

	if (rangeSum == k) {
		ret++;
	}
	return ret;
}