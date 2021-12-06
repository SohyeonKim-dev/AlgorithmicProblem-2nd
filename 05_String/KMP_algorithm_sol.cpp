#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// Ŀ���� - �𸮽� - ���� (KMP) ���ڿ� �˻� �˰����� ����
// ���±��� ��ġ�߾��� �˻����� �κ� ���ڿ����� (���λ� = ���̻�)�� �ִ� ���̸� Ȱ��




// N���� �ڱ� �ڽŰ��� �κ� ��ġ ã���鼭 pi[] ���! 
// pi[i] : N[..i] �� ���̻絵 �ǰ�, ���λ絵 �Ǵ� ���ڿ��� �ִ� ����

vector <int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1; 
	int matched = 0;
	// begin = 0�̸� �ڱ� �ڽ��� ã�ƹ����ϱ� �ȵȴ�! 


	while (begin + matched < m) {
		// ���� ���ڰ� N�� ���� ������ �� ����
		// �κ� ��ġ�� ��� ����Ѵ�.
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
			// Maybe.. begin �ϳ� ���� �� ������..?
		}

		else {
			if (matched == 0) {
				++begin;
				// �´� ���ڰ� �ϳ��� ���ٸ� ������ ��ĭ �ű��
			}
			else {
				begin += matched - pi[matched - 1];
				// ���� ���� �ű��
				matched = pi[matched - 1];
				// �´� ���ڼ��� matched�� ���� 
			}
		}
	}
	return pi;
	// pi�� �� ���Ҵ� �ִ� �� ���� ����Ǳ� ������ max() ������ �ʿ� ����. 
	// �� ���� �״�� KMP �˰��򿡼� �޴´�! 
}





// ¤���� H�� �κ� ���ڿ��� �ٴ� N�� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�. 
vector <int> kmpSearch(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();
	vector <int> ret;


	// ���̻絵 �ǰ�, ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
	// �� ��ġ�� �κ��� KMP �˰����� �ٽ� ���̵���.
	vector <int> pi = getPartialMatch(N);

	int begin = 0;
	int matched = 0;

	while (begin <= n - m) {	// ���� n ������ �� �� �ʿ� �����ϱ�
		if (matched < m && H[begin + matched] == N[matched]) {
			// ¤���� H�� �ش� ���ڰ� �ٴ� N�� �ش� ���ڿ� ���ٸ�
			// matched �ϳ� �ø� : �´� ���ڼ��� �ӽ÷� �����صδ� ���!
			++matched;

			if (matched == m) {
				ret.push_back(begin);
				// ��� �κ� ���ڿ��� ��ġ�Ѵٸ� (�ٴ� ���̿� �������ٸ�)
				// ã�� �Ŵϱ� ���� �迭(����)�� ����!
			}
		}
		else {
			if (matched == 0) {
				++begin;
				// ���� ó��
			}
			else {
				// ���� ó�� ����ĭ���� ���� X
				// ��ġ�ϴ� �κ����� (���̻�) �Űܰ���! 
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}




