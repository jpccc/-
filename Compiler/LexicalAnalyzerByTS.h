#pragma once
#include <iostream>
#include"PublicSource.h"
using namespace std;
class LexicalAnalyzerByTS {//词法分析器
private:
	Token* TokenList;//token序列
public:
	LexicalAnalyzerByTS() {
		TokenList = NULL;
	}
	void insert_List(Token* token);
	static int srearch_ReservedWord(string st);
	static void makeTokenList(string input);//将源输入转化为token序列
	static Token getToken();//语法分析器调用，从token序列中返回一个token
	static void debugging();//调试程序
	void testId(string input);
};
