#pragma once
#include <iostream>
#include "PublicSource.h"
class LexicalAnalyzerByJPC {//词法分析器
private:
	string input;
	Token* TokenHead;//token头
	Token* TokenTail;//token尾
public:
	LexicalAnalyzerByJPC(string st) {
		input = st;
		TokenHead = NULL;
		TokenTail = NULL;
	}
	void insert_List(Token* token);
	char readOne(int& count);//从输入串读入一个字符
	void backOne(int& count, char& CurrentChar, char& NextChar);//回退一个字符
	void makeTokenList();//将源输入转化为token序列
	Token* getToken();//语法分析器调用，从token序列中返回一个token
};
