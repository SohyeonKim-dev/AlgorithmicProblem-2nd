#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;


/*



[ ���� �迭 vector�� resize ���� ]

������� ũ��� size �̴�. 
but, append �� ������ �̸� Ȯ���Ѵ�.
�̰��� �ٷ� capacity.
�ٵ� �� �뷮�� �� ����?
-> ���ο� �迭�� (M��ŭ Ȯ��) �������� �Ҵ�ް�
�� �迭�� ���� �迭�� ������ ��� ���� (by �ݺ���)
and �迭�� ���� �����͸� �ٲ�ġ�� �Ѵ�. 
: �ش� ������ '���Ҵ�'�̶�� �Ѵ�. 





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


[ ���� ]

1���⿡ ��� �������� ����Ǫ���� �θ����� ���￡�� ���� N - 1���� ���� ������ �Բ�
�ⱸ�� ���� ������ �������ߴٰ� �մϴ�.
���� ������� �θ��� �׺��ϴ��� ���� �ڻ����ڰ� �����߰�,
�������� N���� ������� ��� �������� �ѷ��� �� ������� �ڻ��ϱ�� �߽��ϴ�.
�� ����� �ڻ��ϸ�, �������� �� ������κ��� �ð� �������� K��° ��� �ִ� ����� �ڻ��ϴ� ���Դϴ�.

����Ǫ���� å�� ������ ����Ǫ���� �ٸ� ���� �ϳ����� ��Ƴ����� ��
�̵��� ������ �ٲ� �θ��� �׺��ؼ� ��Ƴ��Ҵٰ� �մϴ�.
������ �� �� �� �ϳ��� �Ǳ� ���ؼ��� ����Ǫ���� ù ��° ����κ��� �� �ڸ� ������ ���� �־�� �������?

��ó: https://algospot.com/judge/problem/read/JOSEPHUS


*/





void josephus(int n, int k) {
	list <int> survivors;
	for (int i = 0; i <= n; ++i) {
		survivors.push_back(i);
	}
	list<int>::iterator kill = survivors.begin();
	// �̹��� ���� ����� ��Ÿ���� ������


	while (n > 2) {
		// ù ��° ����� �ڻ��Ѵ�. 
		// erase�� ���� ������ ���� ���Ҹ� ��ȯ�Ѵ�.

		kill = survivors.erase(kill);
		if (kill == survivors.end()) {
			kill = survivors.begin();
		}
		--n;


		// �����͸� k-1 ���� ������� �ű��.
		for (int i = 0; i < k - 1; ++i) {
			++kill;
			if (kill == survivors.end()) {
				kill = survivors.begin();
				// ����Ʈ�� ������ ����, ó������ �ű��.
			}
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}
