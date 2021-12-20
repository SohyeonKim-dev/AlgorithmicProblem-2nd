#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) {
	return ch - 'A';
}

struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;

	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}
	
	~TrieNode() {

	}
};