#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// ���� �ڵ� (kmp �˰���)

vector <int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1;
	int matched = 0;

	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				++begin;
			}
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}



vector <int> kmpSearch(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();
	vector <int> ret;

	vector <int> pi = getPartialMatch(N);
	int begin = 0;
	int matched = 0;

	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) {
				ret.push_back(begin);
			}
		}
		else {
			if (matched == 0) {
				++begin;
			}
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}




// ȯ�� ����Ʈ ���� 
// circular Shift

int shifts(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

/*


[�ð� �������� ������]

- shifts(a,b) -> a���� �ݽð� �������� �� ĭ�� ������ b�� ��°�?
- a���� �ð� �������� �� ĭ�� ������ b�� ��°�? ---> shifts(b,a)
- a�� �ð� �������� ������ b�� ��� ����
  b�� �ݽð� �������� ���� a�� ��� ��쿡 
  ������ �ϴ� ĭ�� ������ ��ġ�ϱ� �����̴�.



*/





// [ ���̻� �迭�� ����ϴ� �ܼ��� �˰��� ]
// 
// ���� �˰��� Ȱ�� : ���ڿ��� ���̰� n, [0, n-1] ������ ���� �迭�� ����
// �� ������ ���� �� �ش� ��ġ���� �����ϴ� ���̻���� ���Ѵ�. 


struct SuffixComparator {
	const string& s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator () (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		// substr ��ſ� strcmp�� ����ϸ� �ӽ� ��ü�� ����� ����� ����ȴ�.
	}
};

vector <int> getSuffixArrayNaive(const string& s) {
	vector <int> perm;
	for (int i = 0; i < s.size(); ++i) {
		perm.push_back(i);
	}
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}