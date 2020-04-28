#pragma once
#include"PublicGrammarSource.h"
#include"PublicSource.h"
class GrammarAnalyzer {
private:
	Token* CurrentToken;
public:
	TreeNode* parse();			//返回语法分析树的根
	TreeNode* ProgramHead();
	void match(string st);
	bool isID() {
		return true;
	}
};