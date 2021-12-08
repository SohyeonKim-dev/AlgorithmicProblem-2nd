#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// [ ���̻� �迭 : ���ڿ��� �ư��̹� Į ]
// Ư�� ���ڿ� s�� ��� ���̻縦 ���� ������ �����ص� ��




// �� ���̻� i�� j�� �־��� ��,
// �� �� ��� ���� �տ� �;��ϴ��� ����

struct SuffixComparator {
	const string& s;
	SuffixComparator(const string & s) : s(s) {}
	bool operator () (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		// s.substr() ��� strcmp�� ����ϸ� �ӽ� ��ü�� ����� ����� ����ȴ�.
	}
};


// s�� ���̻� �迭�� ���
vector <int> getSuffixArrayNaive(const string& s) {
	vector <int> perm;
	for (int i = 0; i < s.size(); ++i) {
		perm.push_back(i);
	}
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	// ���̻縦 ���ϴ� ���ڸ� �̿��Ͽ� ����! 
	return perm;
}





/*

	[ ���̻� �迭�� ����� �ǹ�-���̾�� �˰��� ]

- �� ���̻���� ù t ���ڸ� �������� �� �׷� ��ȣ�� �־��� ��,
  �־��� �� ���̻縦 ù 2t ���ڸ� �������� ���Ѵ�. 
- group�� ���̰� 0�� ���̻絵 �����Ѵ�. 

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
			// ù ���ڰ� �ٸ��ٸ� �׷����θ� �� ����
		}
		return group[a + t] < group[b + t];
		// ���ٸ�, ���� �׷����� �Ѿ ��.
	}
};



// ���̻� �迭�� ����ϴ� �ǹ��� ���̾�� �˰���

vector <int> getSuffixArray(const string& s) {		// s�� ���̻� �迭�� ����Ѵ�.
	int n = s.size();
	int t = 1;
	// ù t���� �������� group �з���

	vector <int> group(n + 1);
	for (int i = 0; i < n; ++i) {
		group[i] = s[i];
	}
	group[n] = -1;


	// ��������� ���̻� �迭�� �� ��ȯ��
	// �� �迭�� log(n)�� ������
	vector <int> perm(n);
	for (int i = 0; i < n; ++i) {
		perm[i] = i;
	}

	while (t < n) {
		Comparator compareUsing2T(group, t);
		// ù 2t ���ڸ� �������� perm�� �ٽ� �����Ѵ�. 
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




// ex) ���� ���ڿ�
// ���̻� �迭�� ����� ���� ���ڿ� ������ �ذ��ϴ� �˰����� ����
// 2���� ���ڿ��� �̾� ���δ�! ( ex) s + s )

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





// [ ���̻� �迭�� Ȱ���Ͽ� �ٸ� �κ� ���ڿ��� ���� ���� �˰��� ]
// ���� ���λ��� �ִ� ���̸� ����Ѵ�.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i;
		++j;
		++k;
	}
	return k; // ���� ���λ��� �ִ� ����
}


// s�� ���� �ٸ� �κ� ���ڿ��� ���� ����.
int countSubstrings(const string& s) {
	vector <int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		// cp ���� �ߺ��̴�!

		if (i > 0) {
			cp = commonPrefix(s, a[i - 1], a[i]);
			ret += n - a[i] - cp;
		}
	}
	return ret;
}




/*

	[ ���� ]

���� �տ��� �����̳� ���Ǹ� �ϴ� ������� �� �߰��߰���
���������� ���� ���������� ���ֱ� ���� ���� ����� �մϴ�. 
���Ǹ� �ϴ� ����� �� ���� �� ������ "��~" Ȥ�� "�׷�����~" ���� ���� �ݺ��ϸ� �� �ŷڰ� ���� �ʱ� ����������.

���� �б⿡ ó������ �к� ���Ǹ� �ð� �� ���ڻ�� �ڽ��� ������ ��ġ�� ���� �˰��� ���� �п��� ã�ƿԽ��ϴ�.
�˰��� ���� �п������� ���������� ���ſ� �� ��ǥ �ڷ���� �ڵ�ȭ�� ���α׷����� �м���
���ľ� �� ���������� ��Ȯ�� ¤����ϴ�.

���ڻ簡 ���ݱ��� �ߴ� ��ǥ��� ���ǵ鿡�� �ߴ� ���� ��� ���� �ν��� ���� �뺻���� ��������ϴ�.
�� �� �뺻 �� K �� �̻� �����ϴ� �κ� ���ڿ��� "������" �̶�� �սô�.
�켱 ���� Ƽ�� ���� ���� �ͺ��� ��ġ�� ���� ���� �� �������� ã���� �մϴ�.

�뺻�� �־��� �� ���� �� �������� ���̸� ã�� ���α׷��� �ۼ��ϼ���.

��ó : https://algospot.com/judge/problem/read/HABIT

*/



// ���� ���λ��� �ִ� ����!
int commonPrefix(const string& s, int i, int j);

// k �� �̻� �����ϴ� s�� �κ� ���ڿ� �߿��� �ִ� ���̸� ã�´�. 
int longestFrequent(int k, const string& s) {
	vector <int> a = getSuffixArray(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); ++i) {
		ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
	}
	return ret;
}