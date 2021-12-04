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


int prerequisite[MAXN];			// i번째 과목의 선수과목의 집합 (비트형 정수)
int classes[10];				// i번째 학기에 개설되는 과목의 집합
int cache[10][1 << MAXN];		


// majorNum의 이진수 표현에서 켜진 비트의 수를 반환한다.
int bitCount(int majorNum);



/*

- graduate 함수 
- 이번 학기가 sememster, 지금까지 들은 과목의 집합이 taken
- neededSubjectNum개 이상의 과목을 모두 들으려면 몇 학기나 더 있어야함?
- 불가능 한 경우 INF 반환

*/


int graduate(int semester, int taken) {
	if (bitCount(taken) >= neededSubjectNum) {
		return 0;
		// 이미 neededSubjectNum 개 이상의 과목을 수강함
	}

	if (semester == semesterNum) {
		return INF;
		// 기저 사례 : semesterNum 학기가 전부 지난 경우
	}


	// 메모이제이션 
	int& ret = cache[semester][taken];
	if (ret != -1) {
		return ret;
	}
	ret = INF;


	// 이번 학기에 들을 수 있는 과목(cantake) 중 아직 듣지 않은 과목을 찾는다. 
	int canTake = (classes[semester] & ~taken);
	for (int i = 0; i < majorNum; ++i) {
		// 선수과목을 다 듣지 않은 과목을 걸러낸다.
		if ((canTake & (1 << i))  // i번째의 수강 가능 과목에 대하여 
			&& (taken & prerequisite[i]) != prerequisite[i]) {
			// i의 선수강 과목을 듣지 않았을 때! 
			canTake &= ~(1 << i);
		}
	}


	// 이 집합의 모든 부분 집합을 순회한다.
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitCount(take) > maxSubjectNum) {
			continue;
			// maxSubjectNum 과목 까지만 (이하만) 들을 수 있다. 
		}
		ret = min(ret, graduate(semester + 1, taken | take ) + 1);
	}
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}