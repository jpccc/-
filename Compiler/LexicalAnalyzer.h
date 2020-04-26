#pragma once
#include<string>
#include <iostream>
using namespace std;
const int reserved_count = 21;
static const char* reserved_word[reserved_count] = { "char","int","var","program","integer","procedure","array","begin","while","if","then","else","endwh",
"end","read","of","record","fi","return","write","type" };
struct Token {
	int type;//类型 2:保留字
	string value;//内容
	Token* next;
};
class LexicalAnalyzer {//词法分析器
private:
	Token* TokenList;//token序列
public:
	LexicalAnalyzer() {
		TokenList = NULL;
	}
	void insert_List(Token* token);
	static int srearch_ReservedWord(string st);
	static void makeTokenList(string input);//将源输入转化为token序列
	static Token getToken();//语法分析器调用，从token序列中返回一个token
};

void LexicalAnalyzer::insert_List(Token* token) {
	Token* start = TokenList;
	if (TokenList == NULL) {
		TokenList = token
	}
	else
	{
		while ()
	}
}
int LexicalAnalyzer::srearch_ReservedWord(string st) {
	int exist = 0;
	for (int i = 0; i < reserved_count; i++) {
		if (st.compare(reserved_word[i]))
			exist = i + 1;
	}
	return exist;
}
void LexicalAnalyzer::makeTokenList(string input) {

	int count = 0;	//输入串遍历指针
	unsigned int iSize = input.size();

	string word = "";//即将要加入TokenList的单词
	char NextChar;//上次读取的字符
	char CurrentChar;//当前读取的字符

	int judge = 0;//选择执行哪一个分支
	int reserved_Location;//保留字在表中的位置

	while (count < iSize) {
		CurrentChar = input[count];
		NextChar = CurrentChar;
		count++;		//输入串指针移动

		switch (judge) {
		case 0:		//起始状态
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z'))
			{
				judge = 1;
				break;
			}
			if ('0' <= CurrentChar && CurrentChar <= '9')
			{
				judge = 2;
				break;
			}
			judge = 3;//其他，暂时测试
			if (CurrentChar = '#')//结束标志
			{
				judge = 10;	//	暂时设定
				break;
			}
			break;
		case 1:		//字母
			CurrentChar = input[count];		//后期加上判断，防止越界
			count++;		//输入串指针移动
			if (('a' <= CurrentChar && CurrentChar <= 'z') || ('A' <= CurrentChar && CurrentChar <= 'Z') || ('0' <= CurrentChar && CurrentChar <= '9'))
			{
				word = word + CurrentChar;//拼接
				NextChar = CurrentChar;
				break;
			}
			count--;			//不是标识符，Back
			CurrentChar = NextChar;
			reserved_Location = srearch_ReservedWord(word);
			if (reserved_Location == 0)				//保留字? 若返回0，表里找不到，则为标识符，
			{
				Token* reserved_word = new Token();
				reserved_word->type = 2;
				reserved_word->value = word;
				reserved_word->next = NULL;
			}

			break;
		case 2:		//数字

			break;
		}

		if (judge == 10)	//跳出while循环	
			break;
	}


}

Token LexicalAnalyzer::getToken()
{
	return Token();
}
	void makeTokenList(string input);//将源输入转化为token序列
	Token getToken();//语法分析器调用，从token序列中返回一个token
	void testId(string input);//尝试识别标识符
};