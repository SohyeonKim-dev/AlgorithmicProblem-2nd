#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;


/*


		[ ���� ]


Best White is a mathematics graduate student at T1 University.
Recently, he finished writing a paper and he decided to polish it.
As he started to read it from the beginning, he realized that some of the formulas have problems:
some of the brackets are mismatched! Since there are so many formulas in his paper,
he decided to check their validity with a computer program.

The following kinds of brackets are included in Best White��s paper.

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
	// ���� ��ȣ���� ������� ��� ����


	for (int i = 0; i < formula.size(); ++i) {


		// ���� ��ȣ����, �ݴ� ��ȣ���� Ȯ��
		// ���� ��ȣ���, ������ ���ÿ� ��´�. 

		if (opening.find(formula[i]) != -1) {
			openStack.push(formula[i]);
		}

		// �� ���� ��� ���� �� ���� ���ڿ� ���纻��. 

		else {
			if (openStack.empty()){
				return false;
				// ������ �� ���, ����
			}
			if (opening.find(openStack.top()) != closing.find(formula[i])) {
				return false;
				// ���� ¦�� ���� �ʾƵ� (������ pop��) ����
			}
			openStack.pop();
			// ¦�� ���� ��! pop ���� ���ش�. 
		}
	}
	return openStack.empty() == true ;
	// ������ ���� ��ȣ�� ����� ����! 
}