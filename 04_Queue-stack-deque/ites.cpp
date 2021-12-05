#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

/*

	�¶��� �˰��� vs �������� �˰���


*/

/*


	[����]


��ȯ�̴� �ܰ迡�� ���ƿ��� ���ĸ� �����ϴ� ������ ��Ը� ������Ʈ, ITES@home�� �����ϰ� �ֽ��ϴ�.
�ܰ迡�� ���ƿ��� ���Ĵ� ��ó���� ���� �� ���ڰ� [1,10000] ���� �ȿ� ���� �ڿ��� ������ �־����µ�,
�� ���İ� ���� �ܼ��� ���������� �ƴϸ� �ǹ� �ִ� ������ ������ �ִ� �������� �ľ��ϰ� �ͽ��ϴ�.
��ȯ�̴� ������ �κ� ���� �߿� ���� K�� ���� ���� ���ٴ� ���� ��ġë���ϴ�.
�κ� �����̶� ���ӵ� ������ �Ϻθ� ���մϴ�.

���� ��� ���� {1,4,2,1,4,3,1,6} ���� ���� 7 �� �κ� ������ ��� 5�� �ֽ��ϴ�.
{1,4,2} , {4,2,1} , {2,1,4}, {4,3}, {1,6} �� �κ� �������� ���� ���ĵ� �ȴٴ� �� �����սô�.

K�� �ܰ��ο��� �ǹ� �ִ� �����ϱ��?
��ȯ���� ������ Ȯ���ϱ� ����, ���� N�� ��ȣ ����� �־��� ��
���� K�� �κ� ������ �� ���� �ִ��� ����ϴ� ���α׷��� �ۼ��ϼ���.


*/


// ���� �ܼ��� �˰��� 

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



// ����ȭ�� �˰���

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






// �¶��� �˰��� and ���� ���ٵ� ���� ������ ���� 
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