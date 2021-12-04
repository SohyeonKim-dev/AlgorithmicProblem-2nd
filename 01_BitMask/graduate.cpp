#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int MAXN = 10;
const int INF = 987654321;

int majorNum; // n
int neededSubjectNum; // k
int semesterNum; // m
int maxSubjectNum; // l
int prerequisite[MAXN];

int classes[10];
int cache[10][1 << MAXN];

int bitCount(int majorNum);

int graduate(int semester, int taken) {
	if (bitCount(taken) >= neededSubjectNum) {
		return 0;
	}

	if (semester == semesterNum) {
		return INF;
	}

	int& ret = cache[semester][taken];
	if (ret != -1) {
		return ret;
	}
	ret = INF;

	int canTake = (classes[semester] & ~taken);
	for (int i = 0; i < majorNum; ++i) {
		if ((canTake & (1 << i)) 
			&& (taken & prerequisite[i]) != prerequisite[i]) {
			canTake &= ~(1 << i);
		}
	}
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitCount(take) > 1) {
			continue;
		}
		ret = min(ret, graduate(semester + 1, taken | take ) + 1);
	}
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}