#pragma once
#include"PublicGrammarSource.h"
#include"PublicSource.h"
class GrammarAnalyzer {
private:
	Token* CurrentToken;
public:
	TreeNode* parse();			//�����﷨�������ĸ�
	TreeNode* ProgramHead();
	void match(string st);
	bool isID() {
		return true;
	}
};