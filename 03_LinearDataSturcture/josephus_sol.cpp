#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;


/*



[ 동적 배열 vector의 resize 원리 ]

명시적인 크기는 size 이다. 
but, append 할 공간을 미리 확보한다.
이것이 바로 capacity.
근데 이 용량이 다 찬다?
-> 새로운 배열을 (M만큼 확장) 동적으로 할당받고
새 배열에 기존 배열의 내용을 모두 복사 (by 반복문)
and 배열에 대한 포인터를 바꿔치기 한다. 
: 해당 과정을 '재할당'이라고 한다. 





if (size == capacity) {
	int newCapacity = capacity + M;
	int* newArray = new int[newCapacity];

	for (int i = 0; i < size; ++i) {
		newArray[i] = array[i];
	}

	if (array) {
		delete[] array;
	}
	array = newArray;
	capacity = newCapacity;
}
array[size++] = newValue;


*/





/*


[ 문제 ]

1세기에 살던 역사학자 조세푸스는 로마와의 전쟁에서 패해 N - 1명의 동료 병사들과 함께
출구가 없는 동굴에 포위당했다고 합니다.
동료 병사들은 로마에 항복하느니 차라리 자살하자고 결의했고,
포위당한 N명의 사람들이 모두 원형으로 둘러선 뒤 순서대로 자살하기로 했습니다.
한 사람이 자살하면, 다음에는 그 사람으로부터 시계 방향으로 K번째 살아 있는 사람이 자살하는 것입니다.

조세푸스의 책에 따르면 조세푸스와 다른 병사 하나만이 살아남았을 때
이들은 마음을 바꿔 로마에 항복해서 살아남았다고 합니다.
마지막 두 명 중 하나가 되기 위해서는 조세푸스는 첫 번째 병사로부터 몇 자리 떨어진 곳에 있어야 했을까요?

출처: https://algospot.com/judge/problem/read/JOSEPHUS


*/





void josephus(int n, int k) {
	list <int> survivors;
	for (int i = 0; i <= n; ++i) {
		survivors.push_back(i);
	}
	list<int>::iterator kill = survivors.begin();
	// 이번에 죽을 사람을 나타내는 포인터


	while (n > 2) {
		// 첫 번째 사람이 자살한다. 
		// erase는 지운 원소의 다음 원소를 반환한다.

		kill = survivors.erase(kill);
		if (kill == survivors.end()) {
			kill = survivors.begin();
		}
		--n;


		// 포인터를 k-1 다음 사람으로 옮긴다.
		for (int i = 0; i < k - 1; ++i) {
			++kill;
			if (kill == survivors.end()) {
				kill = survivors.begin();
				// 리스트의 끝까지 가면, 처음으로 옮긴다.
			}
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}
