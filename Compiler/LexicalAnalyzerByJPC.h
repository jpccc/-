#pragma once
#include <iostream>
#include"PublicSource.h"
using namespace std;
class LexicalAnalyzerByJPC {//词法分析器
private:
	Token* TokenList;//token序列
public:
	LexicalAnalyzerByJPC() {
		TokenList = NULL;
	}
	void insert_List(Token* token);
	int srearch_ReservedWord(string st);
	void makeTokenList(string input);//将源输入转化为token序列
	Token* getToken();//语法分析器调用，从token序列中返回一个token
};
