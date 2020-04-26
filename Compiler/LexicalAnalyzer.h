#pragma once
#include<string>
using namespace std;
class Token {
	int type;//类型
	string value;//内容
};
class LexicalAnalyzer {//词法分析器
private :
	Token TokenList[];//token序列
public:
	void makeTokenList(string input);//将源输入转化为token序列
	Token getToken();//语法分析器调用，从token序列中返回一个token
};