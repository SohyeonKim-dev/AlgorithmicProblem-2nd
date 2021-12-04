#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int MAXN = 10;
const int INF = 987654321;

int majorNum;					// n
int neededSubjectNum;			// k
int semesterNum;				// m
int maxSubjectNum;				// l


int prerequisite[MAXN];			// i��° ������ ���������� ���� (��Ʈ�� ����)
int classes[10];				// i��° �б⿡ �����Ǵ� ������ ����
int cache[10][1 << MAXN];		


// majorNum�� ������ ǥ������ ���� ��Ʈ�� ���� ��ȯ�Ѵ�.
int bitCount(int majorNum);



/*

- graduate �Լ� 
- �̹� �бⰡ sememster, ���ݱ��� ���� ������ ������ taken
- neededSubjectNum�� �̻��� ������ ��� �������� �� �б⳪ �� �־����?
- �Ұ��� �� ��� INF ��ȯ

*/


int graduate(int semester, int taken) {
	if (bitCount(taken) >= neededSubjectNum) {
		return 0;
		// �̹� neededSubjectNum �� �̻��� ������ ������
	}

	if (semester == semesterNum) {
		return INF;
		// ���� ��� : semesterNum �бⰡ ���� ���� ���
	}


	// �޸������̼� 
	int& ret = cache[semester][taken];
	if (ret != -1) {
		return ret;
	}
	ret = INF;


	// �̹� �б⿡ ���� �� �ִ� ����(cantake) �� ���� ���� ���� ������ ã�´�. 
	int canTake = (classes[semester] & ~taken);
	for (int i = 0; i < majorNum; ++i) {
		// ���������� �� ���� ���� ������ �ɷ�����.
		if ((canTake & (1 << i))  // i��°�� ���� ���� ���� ���Ͽ� 
			&& (taken & prerequisite[i]) != prerequisite[i]) {
			// i�� ������ ������ ���� �ʾ��� ��! 
			canTake &= ~(1 << i);
		}
	}


	// �� ������ ��� �κ� ������ ��ȸ�Ѵ�.
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitCount(take) > maxSubjectNum) {
			continue;
			// maxSubjectNum ���� ������ (���ϸ�) ���� �� �ִ�. 
		}
		ret = min(ret, graduate(semester + 1, taken | take ) + 1);
	}
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}