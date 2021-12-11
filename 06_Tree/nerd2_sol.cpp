#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


/*

	[problem]

대 성황이었던 지난 알고스팟 연간 모의고사 이후 프로그래밍 대회의 열기는 날로 뜨거워져
올해는 10만명이 넘는 사람들이 참가 신청을 할 것으로 예상되고 있습니다.
그러나 채점관을 할 자원 봉사자는 예년과 똑같이 5명뿐이라, 이 사람들을 대회에 다 참가시킬 수는 없습니다.
따라서 올해에도 참가 신청을 한 사람 중 진정한 프로그래밍 너드들만을 대회에 참가할 수 있도록 받아 주기로 했습니다.

종만의 새로운 이론에 따르면, 어떤 사람의 너드 지수는 다음 두 가지 값에 의해 결정됩니다.

알고스팟 온라인 채점 시스템에서 푼 문제의 수 p
밤 새면서 지금까지 끓여먹은 라면 그릇 수 q
이 이론에 따르면 어떤 참가 신청자 a 의 문제 수 pa 와 그릇 수 qa 를
다른 참가 신청자 b 의 문제 수 pb 와 그릇 수 qb 에 각각 비교했을 때,
pa < pb, qa < qb 라면 참가 신청자 a 는 너드일 가능성이 없습니다.

조직위는 너드일 가능성이 있는 사람들만을 대회에 받아주기로 했습니다.

한 사람의 참가 가능 여부는 다른 사람들에 의해 결정되기 때문에,
대회에 참가할 수 있는 사람의 수는 새로운 사람이 참가 신청을 할 때마다 계속 바뀝니다.
예를 들어 다음과 같은 4명의 사람들이 순서대로 참가 신청을 했다고 합시다.

참가자	종만	재훈	효승	광규
문제 수	72	57	74	64
라면 그릇 수	50	67	55	60

종만과 재훈이 순서대로 대회 참가 신청을 하면 대회에 참가할 수 있는 사람의 수는 각각 1, 2 로 늘어나지만,
효승이는 문제 수도 라면 그릇 수도 종만보다 많으므로 효승이 참가 신청을 한 시점에서
종만은 더 이상 대회에 참가할 수 없습니다.
따라서 이 네 명이 참가 신청을 할 때마다 참가 가능자의 수는 1, 2, 2, 3으로 변합니다.

이렇게 각 사람이 참가 신청을 할 때마다 대회에 참가할 수 있는 사람들의 수가 어떻게 변하는지 계산하는 프로그램을 작성하세요.


	출처 : https://algospot.com/judge/problem/read/NERD2


*/


/*


1) MAP이란?

map은 각 노드가 key와 value 쌍으로 이루어진 트리로 중복을 허용하지 않음.

map은 first, second가 있는 pair 객체로 저장되는 데 first- key로 second- value로 저장

C++의 map의 내부 구현: 검색, 삽입, 삭제가 O(logn) 인 레드블랙트리로 구성됨


2) MAP 기본 형태

map <key, value> map1;


3) MAP 정렬

map은 key를 기준으로 정렬하며 오름차순으로 정렬합니다.

만약 내림차순으로 정렬하고 싶다면 : map <int, int, greater> map1;

(+ int데이터를 내림차순으로 정렬하고 싶을 경우, 데이터에 -(마이너스)를 붙여 삽입하여 처리)


출처: https://life-with-coding.tistory.com/305 


*/




// 현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다. 
// coords[x] = y

map <int, int> coords;


// 새로운 점 (x,y)이 기존의 다른 점들에 지배당하는지 확인 

bool isDominated(int x, int y) {
	map<int, int> ::iterator it = coords.lower_bound(x);

	// x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점 찾기!

	if (it == coords.end()) {
		return false;
	}
	return y < it->second;
}



// 지배되는 점들을 삭제하는 함수 

void removeDominated(int x, int y) {
	map<int, int> ::iterator it = coords.lower_bound(x);
	if (it == coords.begin()) {
		return;
	}
	--it;

	while (true) {
		if (it->second > y) {
			break;
		}
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int> ::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

int registered(int x, int y) {
	if (isDominated(x, y)) {
		return coords.size();
	}
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}