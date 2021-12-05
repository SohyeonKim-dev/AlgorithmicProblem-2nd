#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;


/*


		[ 문제 ]


Best White is a mathematics graduate student at T1 University.
Recently, he finished writing a paper and he decided to polish it.
As he started to read it from the beginning, he realized that some of the formulas have problems:
some of the brackets are mismatched! Since there are so many formulas in his paper,
he decided to check their validity with a computer program.

The following kinds of brackets are included in Best White’s paper.

Round brackets are opened by a ( and closed by a ).
Curly brackets are opened by a { and closed by a }.
Square brackets are opened by a [ and closed by a ].
A formula is said well-matched when the following conditions are met:

Every bracket has a corresponding pair. ( corresponds to ), [ corresponds to ], et cetera.
Every bracket pair is opened first, and closed later.
No two pairs "*cross*" each other. For example, [(]) is not well-matched.
Write a program to help Best White by checking if each of his formulas is well-matched.
To make the problem easier, everything other than brackets are removed from the formulas.


*/




bool wellMatched(const string& formula) {
	const string opening("({[");
	const string closing(")}]");

	stack <char> openStack;
	// 열린 괄호들을 순서대로 담는 스택


	for (int i = 0; i < formula.size(); ++i) {


		// 여는 괄호인지, 닫는 괄호인지 확인
		// 여는 괄호라면, 무조건 스택에 담는다. 

		if (opening.find(formula[i]) != -1) {
			openStack.push(formula[i]);
		}

		// 이 외의 경우 스택 맨 위의 문자와 맞춰본다. 

		else {
			if (openStack.empty()){
				return false;
				// 스택이 빈 경우, 실패
			}
			if (opening.find(openStack.top()) != closing.find(formula[i])) {
				return false;
				// 서로 짝이 맞지 않아도 (스택의 pop과) 실패
			}
			openStack.pop();
			// 짝이 맞을 때! pop 으로 빼준다. 
		}
	}
	return openStack.empty() == true ;
	// 닫히지 않은 괄호가 없어야 성공! 
}