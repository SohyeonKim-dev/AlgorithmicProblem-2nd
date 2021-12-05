#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// ������ ���ڿ� �˻� �˰��� 
// H : ¤����(haystack)
// N : �ٴ�(needle)

vector <int> nativeSearch(const string& H, const string& N) {
	vector <int> ret;

	// ¤������ �κ� ���ڿ���, �ٴ��� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�.

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