#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*

[ 비트 마스크 ]

- 연산자 우선순위기 낮다 -> 괄호를 적극적으로 사용하자 
- 부호로 인하여 버그 발생 가능 -> 되도록이면 부호 없는 수에 대해 사용
- 32 bit / 64 bit 오버플로우 주의 

*/



// 비트 마스크를 활용한 집합의 구현 

/*

- 20가지의 토핑 (0~19)
- 주문시 토핑의 첨/삭 가능
- 비트마스크를 활용하면 다양한 비트 연산을 이용해 
  집합 연산을 빠르고 간단하게 구현 가능하다. 

*/




// [ 공집합과 꽉 찬 집합 ]
// 공집합은 상수 0을 의미한다. 

int fullPizza = (1 << 20) - 1;
// 20개의 비트가 모두 켜진 수를 얻는다. 






// [ 원소의 포함 여부 확인 ]
int toppings;
int p;

/*

if (toppings & (1 << p)) {
	cout << "peperoni is in" << endl;
}

*/


/*


[ 원소의 삭제 ]

toppings &= ~(1 << p);

~(1 << p) => 해당 비트만 꺼지고 나머지는 다 켜진 숫자


*/ 


/*


[ 원소의 토글(toggle) ]


toppings ^= (1 << p);
-> XOR 연산이 켜진 비트를 끄고, 
   꺼진 비트를 키는 역할을 함


*/




// [집합의 크기 구하기]

int bitCount(int x) {
	if (x == 0) {
		return 0;
	}
	return (x % 2 + bitCount(x / 2));
	// 재귀 호출로 2로 치면서 구하기! 
	// 이진수니까. 
}




/*

[최소 원소 찾기]

int firstTopping = (toppings & -toppings);



[최소 원소 지우기]

toppings &= ( toppings - 1 );



[모든 부분 집합 순회하기]

for (int subset = pizza; subset; subset = ((subset - 1) & pizza)) {

	- subset 에서 1을 빼면, 켜졌던 최하위 비트가 꺼지고, 그 밑의 비트들은 전부 켜진다. 
	- 이에 대하여 pizza와의 교집합 -> pizza에 속하지 않는 비트들은 모두 꺼진다. 
	- 해당 연산을 반복하면, pizza의 모든 부분 집합을 방문할 수 있다. 


}


*/