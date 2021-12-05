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


void josephus(int n, int k) {
	list <int> survivors;
	for (int i = 0; i <= n; ++i) {
		survivors.push_back(i);
	}
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		kill = survivors.erase(kill);
		if (kill == survivors.end()) {
			kill = survivors.begin();
		}
		--n;
		for (int i = 0; i < k - 1; ++i) {
			++kill;
			if (kill == survivors.end()) {
				kill = survivors.begin();
			}
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}
